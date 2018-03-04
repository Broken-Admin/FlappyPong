g++ -c -std=c++11 PongMultiplayer.cpp
g++ PongMultiplayer.o -std=c++11 -o PongMP -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio