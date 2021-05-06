#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "SDL.h"

void CreateWorld(int length, int width);

void ShowTheWorld(int length, int width, SDL_Window *win, int Slength, int Swidth, int size);

void show(int length, int width, SDL_Window *win, int Slength, int Swidth, int size, int delay);

void show1(int length, int width, SDL_Window *win, int Slength, int Swidth, int size);

void MakeMove(int length, int width);

int NumAround(int i, int j);

void Operate(int length, int width);

void eventloop();

int CheckState(int length, int width, int size);