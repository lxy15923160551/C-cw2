#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "SDL.h"
#include "Game.h"

int grid[1000][1000];
int grid1[1000][1000];

void CreateWorld(int length, int width)
{
    for (int i = 0; i < width + 1; i++)
    {
        for (int j = 0; j < length + 1; j++)
        {
            grid[i][j] = 0;
        }
    }
}

void ShowTheWorld(int length, int width, SDL_Window *win, int Slength, int Swidth, int size)
{
    int a = 0;
    int b = 0;
    int SIZE = size;

    SDL_Renderer *renderer;
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //白色
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //紅色
    for (int i = 1; i < width + 1; i++)
    {
        for (int j = 1; j < length + 1; j++)
        {
            if (grid[i][j] == 1)
            {
                struct SDL_Rect rect = {a, b, size, size};
                SDL_RenderFillRect(renderer, &rect);
                a += size;
            }
            else
            {
                a += size;
            }
        }
        a = 0;
        b += size;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //黑色
    for (int i = 0; i < length; i++)
    {
        SDL_RenderDrawLine(renderer, SIZE, 0, SIZE, Swidth);
        SIZE += size;
    }
    SIZE = 0;
    for (int i = 0; i < length; i++)
    {
        SDL_RenderDrawLine(renderer, 0, SIZE, Slength, SIZE);
        SIZE += size;
    }
    SDL_RenderPresent(renderer);
    MakeMove(length, width);
}

void show(int length, int width, SDL_Window *win, int Slength, int Swidth, int size, int delay)
{
    int a = 0;
    int b = 0;

    SDL_Surface *screen = SDL_GetWindowSurface(win);
    SDL_Rect r = {0, 0, Slength, Swidth};
    SDL_FillRect(screen, &r, 0xffffffff);

    for (int i = 1; i < width + 1; i++)
    {
        for (int j = 1; j < length + 1; j++)
        {
            if (grid[i][j] == 1)
            {
                struct SDL_Rect rect = {a, b, size, size};
                SDL_FillRect(screen, &rect, 0xffff0000);
                a = a + size;
            }
            else
            {
                a = a + size;
            }
        }
        a = 0;
        b = b + size;
    }

    SDL_UpdateWindowSurface(win);
    SDL_Delay(1000 * delay);

    MakeMove(length, width);
}

void show1(int length, int width, SDL_Window *win, int Slength, int Swidth, int size)
{
    int a = 0;
    int b = 0;

    SDL_Surface *screen = SDL_GetWindowSurface(win);
    SDL_Rect r = {0, 0, Slength, Swidth};
    SDL_FillRect(screen, &r, 0xffffffff);

    for (int i = 1; i < width + 1; i++)
    {
        for (int j = 1; j < length + 1; j++)
        {
            if (grid[i][j] == 1)
            {
                struct SDL_Rect rect = {a, b, size, size};
                SDL_FillRect(screen, &rect, 0xffff0000);
                a = a + size;
            }
            else
            {
                a = a + size;
            }
        }
        a = 0;
        b = b + size;
    }
    SDL_UpdateWindowSurface(win);

    MakeMove(length, width);
}

void MakeMove(int length, int width)
{
    for (int i = 1; i < width + 1; i++)
    {
        for (int j = 1; j < length + 1; j++)
        {
            grid1[i][j] = grid[i][j];
        }
    }
}

int NumAround(int i, int j)
{
    int num = 0;
    if (grid1[i - 1][j - 1] == 1)
    {
        num++;
    }
    if (grid1[i][j - 1] == 1)
    {
        num++;
    }
    if (grid1[i - 1][j] == 1)
    {
        num++;
    }
    if (grid1[i + 1][j + 1] == 1)
    {
        num++;
    }
    if (grid1[i + 1][j] == 1)
    {
        num++;
    }
    if (grid1[i][j + 1] == 1)
    {
        num++;
    }
    if (grid1[i + 1][j - 1] == 1)
    {
        num++;
    }
    if (grid1[i - 1][j + 1] == 1)
    {
        num++;
    }
    return num;
}

void Operate(int length, int width)
{
    for (int i = 1; i < width + 1; i++)
    {
        for (int j = 1; j < length + 1; j++)
        {
            if (grid[i][j] == 1) //��ϸ��
            {
                if (NumAround(i, j) == 0 || NumAround(i, j) == 1)
                {
                    grid[i][j] = 0; //0��1�� ��
                }
                else if (NumAround(i, j) == 2 || NumAround(i, j) == 3)
                {
                    grid[i][j] = 1; //2��3�� ��
                }
                else
                {
                    grid[i][j] = 0; //����3�� ��
                }
            }
            else if (grid[i][j] == 0 && NumAround(i, j) == 3) //��ϸ��
            {
                grid[i][j] = 1;
            }
            else
            {
                grid[i][j] = 0;
            }
        }
    }
}

void eventloop() //事件循环
{
    while (1)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                break;
            }
        }
    }
}

int CheckState(int length, int width, int size)
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
        case SDL_MOUSEBUTTONDOWN: //点击鼠标左键
            x = event.motion.x;
            y = event.motion.y;
            for (int i = 1; i < width + 1; i++)
            {
                for (int j = 1; j < length + 1; j++)
                {
                    if (x >= j1 && x <= j2 && y >= i1 && y <= i2)
                    {
                        grid[i][j] = 1;
                        return 0;
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
            return 1; // 退回主菜單
        }
    }
}
