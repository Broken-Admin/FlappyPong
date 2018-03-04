g++ -c -std=c++11 PongVerticle.cpp
g++ PongVerticle.o -std=c++11 -o PongVerticle -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio