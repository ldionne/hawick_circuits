CXX=g++
WFLAGS=-Wall -Wextra -pedantic
INCLUDES=-I `pwd`

all:
	$(CXX) $(WFLAGS) $(INCLUDES) -o hawick_circuits test_hawick_circuits.cpp

clean:
	rm -f hawick_circuits
