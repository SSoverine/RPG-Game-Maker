build:	
	g++ -std=c++20 -Isrc/Include -Lsrc/lib -g main.cpp ./headers/game.cpp ./headers/story.cpp ./headers/cutscene.cpp ./headers/movechar.cpp ./headers/choices.cpp ./headers/dialog.cpp ./headers/character.cpp ./headers/Musics.cpp -lSDL2main -lSDL2 -lgif -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o main

run:
	./main
