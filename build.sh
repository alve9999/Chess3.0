#!/bin/bash
src=Chess3.0/src
g++ -o chess Chess3.0/Chess3.0.cpp $src/Ai.cpp $src/Bit.cpp $src/Board.cpp $src/Graphics.cpp $src/Hash.cpp $src/Magic.cpp $src/Moves.cpp -lsfml-graphics -lsfml-window -lsfml-system
