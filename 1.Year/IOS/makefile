
#**********************************#
#*          Jozef Drab             #
#*           FIT VUT               #
#*           proj2.c               #
#*          24.4.2017              #
#*_________________________________#

CFLAGS=-std=gnu99 -Wall -Wextra -Werror -pedantic

proj2: proj2.c
	gcc $(CFLAGS) -o proj2 proj2.c -pthread

clean:
	rm -f *.o proj2
pack:
	zip xdrabj00.zip proj2.c Makefile
