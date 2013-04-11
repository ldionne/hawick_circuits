CXX=g++
WFLAGS=-Wall -Wextra -pedantic
INCLUDES=-I `pwd`

all:
	$(CXX) $(WFLAGS) $(INCLUDES) -o hawick_circuits hawick_circuits.cpp

clean:
	if [ -e hawick_circuits ]; then rm hawick_circuits; fi
