#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "SDL.h"

//Define the state of each cell
void CreateWorld(int length, int width);

//Print out the cell world in the window
void ShowTheWorld(int length, int width, SDL_Window *win, int Slength, int Swidth, int size);

//Print out the cell world in the window, complete the operation of resurrection and death
void show(int length, int width, SDL_Window *win, int Slength, int Swidth, int size, int delay);

//Print out the cell world in the window and demonstrate the process of cell division
void show1(int length, int width, SDL_Window *win, int Slength, int Swidth, int size);

//Save the manipulated array to another temporary array
void MakeMove(int length, int width);

//Determine the number of cells in stock around the cell
int NumAround(int i, int j);

//Perform logical operations
void Operate(int length, int width);

//Exit window
void eventloop();

//Determine the viability of the clicked cell
int CheckState(int length, int width, int size);

//Determine whether cell division is over
int checkstop(int length, int width);
