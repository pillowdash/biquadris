CXX =  g++-14 -std=c++20 -fmodules-ts
CXXFLAGS = -Wall -g
HEADERFLAGS = -c -x c++-system-header

SOURCES = $(wildcard *.cc)
OBJECTS = $(SOURCES:.cc=.o)

HEADERS = iostream fstream memory vector stdexcept string cstdlib
EXEC = biquadris

all: $(EXEC)

$(EXEC): $(SOURCES) $(MODDIR)
	${CXX} ${CXXFLAGS} -c $(SOURCES)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)

$(MODDIR):
	$(CXX) $(HEADERFLAGS) $(HEADERS)

.PHONY: clean 
clean:
	rm -rf gcm.cache
	rm *.o
	rm -f $(EXEC)