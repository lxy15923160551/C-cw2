#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "SDL.h"
#include "Game.h"

int grid[1000][1000];
int grid1[1000][1000];

int main(int argc, char *argv[])
{
    char a;
    char b;
    //The length and width of the input
    int length;
    int width;
    //Grid size
    int size;
    //screen size
    int Slength;
    int Swidth;

    int delay;

    printf("Whether to read data from a local file(y/n):");
    scanf("%s", &a);
    while (a != 'y' && a != 'n')
    {
        printf("Sorry, the option you entered was invalid, please try again.");
        scanf("%s", &a);
    }

    if (a == 'y') 
    {
        FILE *fo = fopen("game.bin", "rb");
        fread(&length, sizeof(int), 1, fo);
        fread(&width, sizeof(int), 1, fo);
        fread(&Slength, sizeof(int), 1, fo);
        fread(&Swidth, sizeof(int), 1, fo);
        fread(&size, sizeof(int), 1, fo);
        fread(&delay, sizeof(int), 1, fo);
        for (int i = 1; i < width + 1; i++)
        {
            for (int j = 1; j < length + 1; j++)
            {
                fread(&grid[i][j], sizeof(int), 1, fo);
            }
        }
        fclose(fo);
        if (SDL_Init(SDL_INIT_VIDEO)) //misjudgement
        {
            SDL_Log("Can not init video,%s", SDL_GetError());
            return 1;
        }
        SDL_Window *win = SDL_CreateWindow("The game of life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Slength, Swidth, SDL_WINDOW_SHOWN);
        if (win == NULL) //misjudgement
        {
            SDL_Log("Can not create window,%s", SDL_GetError());
            return 1;
        }
        while (1)
        {
            if (checkstop(length, width) == 0)
            {
                show(length, width, win, Slength, Swidth, size, delay);
                Operate(length, width);
            }
            else if (checkstop(length, width) == 1)
            {
                goto aaaa;
            }
        }
    aaaa:
        eventloop();
        SDL_DestroyWindow(win); //Out of the window
    }
    else
    {
        printf("Please enter the length:");
        scanf("%i", &length);
        while (length <= 0 || length >= 1000)
        {
            printf("Please enter the length which should be more than 0 and less than 1000.");
            scanf("%i", &length);
        }
        printf("Please enter the width:");
        scanf("%i", &width);
        while (width <= 0 || width >= 1000)
        {
            printf("Please enter the width which should be more than 0 and less than 1000.");
            scanf("%i", &width);
        }
        printf("Please enter the delay when the cell divides(0-10s):");
        scanf("%i", &delay);
        while (length <= 0 || length >= 1000)
        {
            printf("Please enter the number which should be more than 0 and less than 10.");
            scanf("%i", &delay);
        }
        //Determine the square and screen size
        if (length >= width)
        {
            if (length > 0 && length <= 10)
            {
                Slength = length * 100;
                Swidth = width * 100;
                size = 100;
            }
            else if (length > 10 && length <= 1000)
            {
                Slength = 1000;
                Swidth = 1000;
                size = 1000 / length;
            }
        }
        else
        {
            if (width > 0 && width <= 10)
            {
                Slength = length * 100;
                Swidth = width * 100;
                size = 100;
            }
            else if (width > 10 && width <= 1000)
            {
                Slength = 1000;
                Swidth = 1000;
                size = 1000 / width;
            }
        }

        if (SDL_Init(SDL_INIT_VIDEO)) //misjudgement 
        {
            SDL_Log("Can not init video,%s", SDL_GetError());
            return 1;
        }
        SDL_Window *win = SDL_CreateWindow("Initialization", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Slength, Swidth, SDL_WINDOW_SHOWN);
        if (win == NULL) //misjudgement 
        {
            SDL_Log("Can not create window,%s", SDL_GetError());
            return 1;
        }
        printf("Game initialization rule:\n");
        printf("1.Click on the blank to resurrect cells\n");
        printf("2.Close the window to end initialization\n");
        printf("3.Click on the resurrected cell to make it die\n");
        //initialization
        CreateWorld(length, width);
        ShowTheWorld(length, width, win, Slength, Swidth, size);
        while (1)
        {
            int x, y;
            int i1 = 0;
            int i2 = size;
            int j1 = 0;
            int j2 = size;
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_MOUSEBUTTONDOWN: //Click the left mouse button
                    x = event.motion.x;
                    y = event.motion.y;
                    for (int i = 1; i < width + 1; i++)
                    {
                        for (int j = 1; j < length + 1; j++)
                        {
                            if (x >= j1 && x <= j2 && y >= i1 && y <= i2)
                            {
                                if (grid[i][j] == 1)
                                {
                                    grid[i][j] = 0;
                                }
                                else if (grid[i][j] == 0)
                                {
                                    grid[i][j] = 1;
                                }
                                goto bbb;
                            }
                            else
                            {
                                j1 += size;
                                j2 += size;
                            }
                        }
                        j1 = 0;
                        j2 = size;
                        i1 += size;
                        i2 += size;
                    }
                case SDL_QUIT:
                    goto aaa; // Return to Main Menu
                }
            }
        bbb:
            show1(length, width, win, Slength, Swidth, size);
        }
    aaa:
        SDL_DestroyWindow(win); //Out of the window

        printf("Whether to start the game(y/n)");
        scanf("%s", &b);
        while (b != 'y' && b != 'n')
        {
            printf("Sorry, the option you entered was invalid, please try again.");
            scanf("%s", &b);
        }
        if (b == 'y')
        {
            SDL_Window *win1 = SDL_CreateWindow("The game of life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Slength, Swidth, SDL_WINDOW_SHOWN);
            if (win1 == NULL) //misjudgement
            {
                SDL_Log("Can not create window,%s", SDL_GetError());
                return 1;
            }
            
            //Logic

            show(length, width, win1, Slength, Swidth, size, delay);
            Operate(length, width);
            while (1)
            {
                if (checkstop(length, width) == 0)
                {
                    show(length, width, win1, Slength, Swidth, size, delay);
                    Operate(length, width);
                }
                else if (checkstop(length, width) == 1)
                {
                    goto aa;
                }
            }
        aa:
            eventloop();
            SDL_DestroyWindow(win1); //Out of the window
        }
    }

    FILE *fp = fopen("game.bin", "wb");
    fwrite(&length, sizeof(int), 1, fp);
    fwrite(&width, sizeof(int), 1, fp);
    fwrite(&Slength, sizeof(int), 1, fp);
    fwrite(&Swidth, sizeof(int), 1, fp);
    fwrite(&size, sizeof(int), 1, fp);
    fwrite(&delay, sizeof(int), 1, fp);
    for (int i = 1; i < width + 1; i++)
    {
        for (int j = 1; j < length + 1; j++)
        {
            fwrite(&grid[i][j], sizeof(int), 1, fp);
        }
    }
    fclose(fp);
    printf("The game information is already stored");
    return 0;
}
