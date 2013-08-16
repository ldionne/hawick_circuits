CXX=g++
WFLAGS=-Wall -Wextra -pedantic
INCLUDES=-I `pwd`

all: external_test_suite

clean:
	if [ -e hawick_circuits ]; then rm hawick_circuits; fi
	if [ -e test_hawick_circuits ]; then rm test_hawick_circuits; fi

external_test_suite:
	$(CXX) $(WFLAGS) $(INCLUDES) -o hawick_circuits hawick_circuits.cpp

test:
	$(CXX) $(WFLAGS) $(INCLUDES) -o test_hawick_circuits libs/graph/test/hawick_circuits.cpp
