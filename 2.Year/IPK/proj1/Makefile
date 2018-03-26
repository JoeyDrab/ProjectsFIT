Cpp=g++
FLAGS = -Wall -Wextra -std=c++11 -O2 -lpthread

SSRC = server.cpp
CSRC = client.cpp
SBIN = ipk-server
CBIN = ipk-client

all:
	$(Cpp) $(FLAGS) -o $(SBIN) $(SSRC)
	$(Cpp) $(FLAGS) -o $(CBIN) $(CSRC)

clean:
	rm -f $(SBIN)
	rm -f $(CBIN)
