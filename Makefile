all: flappy

flappy:
	g++ -c -std=c++11 index.cpp
	g++ index.o -std=c++11 -o flappy -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

clean:
	rm flappy
	rm *.o