all: compile link open

compile:
	g++ -I inc -c src/main.cpp -o obj/main.o
link:
	g++ obj/main.o -o main -L lib -l sfml-graphics -l sfml-window -l sfml-system
open:
	main.exe	

