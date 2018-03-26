# IFJ2017
# <xkasta02> Matej Kastak

# podla zadania ma kazdy zdrojovy subor obsahovat zakomentovany nazov
# projektu + loginy a mena ludi co sa(asi na tom konkretnom subore)
# podielali

SHELL = /bin/sh

# flagy pouzite pri preklade
CCFLAGS=-Wall -Wextra --pedantic

# podla zadania, meno binarneho suboru nehra rolu a opravovaci skript
# ho dokaze najst sam
RES_BIN=ifj-bin
# nazov odovzdavaneho suboru(podla loginu veduceho)
RES_FILE=xkasta02.tgz
# priecinok, v ktorom budu vykonanen testy skriptu is_it_ok.sh
TEST_SCRIPT_DIR=../validator-dir

# kniznica google test
GTEST=libgtest.a
GTEST_DIR=test/googletest/googletest
GTEST_INCLUDE=-isystem test/googletest/googletest/include

C_FILES=$(wildcard *.c)
O_FILES=$(patsubst %.c, %.o, $(C_FILES))
H_FILES=$(wildcard *.h)

# dependencie jednotlivych testov
TEST_LEX   =lex.o test/test_lex.cpp
TEST_SYNTAX=test/test_syntax.o syntax.o lex.o
TEST_ERROR =test/test_error.o syntax.o lex.o err.o

# make bez ciela prelozi projekt
all : debug
	@echo $(C_FILES)
	@echo $(O_FILES)
	@echo $(H_FILES)

$(RES_BIN) : $(O_FILES)
	$(CC) $(CCFLAGS) $^ -o $(RES_BIN)

# pripravy testy pre syntakticku analyzu
test-lex : $(TEST_LEX) $(GTEST)
	$(CXX) $(GTEST_INCLUDE) -pthread $^ -o $@
	./$@

%.o : %.c %.h
	$(CC) -c $(CCFLAGS) $<

%.o : %.c
	$(CC) -c $(CCFLAGS) $<

%.o : %.cpp %.h
	$(CXX) -c $(CCFLAGS) $<

$(GTEST):
	$(CXX) $(GTEST_INCLUDE) -Itest/googletest/googletest -pthread -c test/googletest/googletest/src/gtest-all.cc
	$(AR) -rv $@ gtest-all.o

debug: CCFLAGS+=-g -DDEBUG
debug: $(RES_BIN)

.PHONY : run clean dist-clean pack format test
test : $(O_FILES) $(GTEST) proj_test.o
	$(CXX) $(GTEST_INCLUDE) -isystem googletest/googletest/include -pthread $(O_FILES) $(GTEST) -o $@

run : $(RES_BIN)
	./$(RES_BIN)

# vycisti repozitar
clean :
	rm -rf $(RES_BIN) $(RES_FILE) $(TEST_SCRIPT_DIR) $(GTEST) test-lex $(O_FILES)

distclean : clean
	rm -rf *.orig
#-git clean -dn
# necham tu -n namiesto -f, bezpecnejsie

# vytvori subor pripraveny na odovzdanie a nasledne ho skontroluje
# pomocou skriptu is_it_ok.sh
pack : clean
	tar -vczf xkasta02.tgz *.c Makefile ../rozdeleni *.h
# TODO(xkasta02): pridat do archivu dokumentaciu
	mkdir -p $(TEST_SCRIPT_DIR)
	../zadanie/is_it_ok.sh $(RES_FILE) ../test-dir

# naformatuje zdrojove subory aby bol styl kodu konzistentny
format :
	astyle --indent=tab --style=java --break-blocks --pad-oper --align-pointer=middle --align-reference=middle --max-code-length=80 *.c *.h
