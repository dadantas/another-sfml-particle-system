CXX = g++
CXXFLAGS = -I include -Wall -std=c++17
SFMLFLAGS = $(shell pkg-config --libs --cflags sfml-graphics)
OBJ = obj/main.o obj/QuickSortVis.o

all: main QuickSortVis

main: obj/main.o
	$(CXX) $^ -o $@ $(SFMLFLAGS)

QuickSortVis: obj/QuickSortVis.o
	$(CXX) $^ -o $@ $(SFMLFLAGS)

obj/%.o: src/%.cpp
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf obj main QuickSortVis
