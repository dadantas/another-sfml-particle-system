all: compile link open

compile:
	g++ -I inc -c src/QuickSortVis.cpp -o obj/QuickSortVis.o
	g++ -I inc -c src/main.cpp -o obj/main.o
link:
	g++ obj/main.o -o main -L lib -l sfml-graphics -l sfml-window -l sfml-system

open:
	main.exe	

quickSort:
	g++ -I inc -c src/QuickSortVis.cpp -o obj/QuickSortVis.o
	g++ obj/QuickSortVis.o -o QuickSortVis -L lib -l sfml-graphics -l sfml-audio -l sfml-window -l sfml-system
	QuickSortVis.exe