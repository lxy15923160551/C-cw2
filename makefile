main:main.o Game.o
    gcc -o main main.o Game.o -L SDL2-2.0.14\x86_64-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2

main.o:main.c Game.h
    gcc -c main.c -I SDL2-2.0.14\x86_64-w64-mingw32\include\SDL2

Game.o:Game.c Game.h
    gcc -c Game.c -I SDL2-2.0.14\x86_64-w64-mingw32\include\SDL2