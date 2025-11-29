CXX = g++-14
CXXFLAGS = -std=c++20 -fmodules-ts -Wall -g
LDFLAGS = -lX11
EXEC = biquadris
OBJECTS = main.o game.o game-impl.o board.o board-impl.o viewver.o viewver-impl.o level.o level-impl.o block.o block-impl.o observer.o observer-impl.o window.o window-impl.o

SYSTEM_HEADERS = iostream vector string memory stdexcept cstdlib fstream

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC) $(LDFLAGS)

observer.o:
	$(CXX) $(CXXFLAGS) -c -x c++-system-header iostream
	$(CXX) $(CXXFLAGS) -c -x c++-system-header vector
	$(CXX) $(CXXFLAGS) -c -x c++-system-header string
	$(CXX) $(CXXFLAGS) -c -x c++-system-header memory
	$(CXX) $(CXXFLAGS) -c -x c++-system-header stdexcept
	$(CXX) $(CXXFLAGS) -c -x c++-system-header cstdlib
	$(CXX) $(CXXFLAGS) -c -x c++-system-header fstream
	$(CXX) $(CXXFLAGS) observer.cc -c

observer-impl.o: observer.o
	$(CXX) $(CXXFLAGS) observer-impl.cc -c

window.o: observer.o
	$(CXX) $(CXXFLAGS) window.cc -c

window-impl.o: window.o
	$(CXX) $(CXXFLAGS) window-impl.cc -c

block.o: observer.o
	$(CXX) $(CXXFLAGS) block.cc -c

block-impl.o: block.o
	$(CXX) $(CXXFLAGS) block-impl.cc -c

level.o: block.o
	$(CXX) $(CXXFLAGS) Level.cc -c

level-impl.o: level.o
	$(CXX) $(CXXFLAGS) Level-impl.cc -c

board.o: block.o observer.o level.o
	$(CXX) $(CXXFLAGS) Board.cc -c

board-impl.o: board.o
	$(CXX) $(CXXFLAGS) board-impl.cc -c

viewver.o: window.o board.o level.o block.o
	$(CXX) $(CXXFLAGS) Viewver.cc -c

viewver-impl.o: viewver.o
	$(CXX) $(CXXFLAGS) Viewver-impl.cc -c

game.o: board.o level.o viewver.o
	$(CXX) $(CXXFLAGS) game.cc -c

game-impl.o: game.o
	$(CXX) $(CXXFLAGS) game-impl.cc -c

main.o: game.o board.o level.o viewver.o
	$(CXX) $(CXXFLAGS) main.cc -c

.PHONY: clean

clean:
	rm -rf *.o $(EXEC) gcm.cache
