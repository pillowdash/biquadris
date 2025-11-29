CXX = g++-14
CXXFLAGS = -std=c++20 -fmodules-ts -Wall -g
LDFLAGS = -lX11
EXEC = biquadris

SYSTEM_MODULES = iostream vector string memory stdexcept cstdlib fstream

OBJECTS = main.o game.o game-impl.o board.o board-impl.o viewver.o viewver-impl.o level.o level-impl.o block.o block-impl.o observer.o observer-impl.o window.o window-impl.o

all: $(EXEC)

$(SYSTEM_MODULES):
	$(CXX) $(CXXFLAGS) -c -x c++-system-header $@

$(OBJECTS): $(SYSTEM_MODULES)

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC) $(LDFLAGS)

observer.o: observer.cc
	$(CXX) $(CXXFLAGS) -c observer.cc -o $@

observer-impl.o: observer-impl.cc observer.o
	$(CXX) $(CXXFLAGS) -c observer-impl.cc -o $@

window.o: window.cc
	$(CXX) $(CXXFLAGS) -c window.cc -o $@

window-impl.o: window-impl.cc window.o
	$(CXX) $(CXXFLAGS) -c window-impl.cc -o $@

block.o: block.cc observer.o
	$(CXX) $(CXXFLAGS) -c block.cc -o $@

block-impl.o: block-impl.cc block.o
	$(CXX) $(CXXFLAGS) -c block-impl.cc -o $@

level.o: Level.cc block.o
	$(CXX) $(CXXFLAGS) -c Level.cc -o $@

level-impl.o: Level-impl.cc level.o
	$(CXX) $(CXXFLAGS) -c Level-impl.cc -o $@

board.o: Board.cc block.o observer.o level.o
	$(CXX) $(CXXFLAGS) -c Board.cc -o $@

board-impl.o: board-impl.cc board.o
	$(CXX) $(CXXFLAGS) -c board-impl.cc -o $@

viewver.o: Viewver.cc window.o board.o level.o block.o
	$(CXX) $(CXXFLAGS) -c Viewver.cc -o $@

viewver-impl.o: Viewver-impl.cc viewver.o
	$(CXX) $(CXXFLAGS) -c Viewver-impl.cc -o $@

game.o: game.cc board.o level.o viewver.o
	$(CXX) $(CXXFLAGS) -c game.cc -o $@

game-impl.o: game-impl.cc game.o
	$(CXX) $(CXXFLAGS) -c game-impl.cc -o $@

main.o: main.cc game.o board.o level.o viewver.o
	$(CXX) $(CXXFLAGS) -c main.cc -o $@

.PHONY: clean

clean:
	rm -rf *.o $(EXEC) gcm.cache