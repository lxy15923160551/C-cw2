#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define WIDTH 100
#define HEIGHT 100

int grid[1000][1000]; //����һ����СΪ  ������
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

void ShowTheWorld(int length, int width, SDL_Window *win)
{
    int a = 0;
    int b = 0;

    SDL_Surface *screen = SDL_GetWindowSurface(win);
    SDL_Rect r = {0, 0, 500, 500};
    SDL_FillRect(screen, &r, 0xffffffff);

    //SDL_Renderer *white = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    //SDL_SetRenderDrawColor(white, 0xFF, 0xFF, 0xFF, 0xFF);
    //SDL_RenderFillRect(white, &r);

    //SDL_Renderer *red = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    //SDL_SetRenderDrawColor(red, 0xFF, 0xFF, 0x00, 0x00);
    for (int i = 1; i < width + 1; i++)
    {
        for (int j = 1; j < length + 1; j++)
        {
            if (grid[i][j] == 1)
            {
                struct SDL_Rect rect = {a, b, WIDTH, HEIGHT};
                SDL_FillRect(screen, &rect, 0xffff0000);
                a = a + WIDTH;
            }
            else
            {
                a = a + WIDTH;
            }
        }
        a = 0;
        b = b + HEIGHT;
    }
    SDL_UpdateWindowSurface(win);
    SDL_Delay(2000);

    MakeMove(length, width);
}

void cell() //pdf�ڲ��Գ����ϸ��
{
    grid[3][3] = 1;
    grid[4][3] = 1;
    grid[2][3] = 1;
    grid[3][1] = 1;
    grid[4][2] = 1;
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

int main(int argc, char *argv[])
{
    char a;
    int length;
    int width;

    printf("Whether to read data from a local file(y/n)");
    scanf("%c", &a);
    while (a != 'y' && a != 'n')
    {
        printf("Whether to read data from a local file(y/n)");
        scanf("%c", &a);
    }
    if (a == 'y') //��ȡ��������
    {
        FILE *fo = fopen("game.bin", "rb");
        fread(&length, sizeof(int), 1, fo);
        fread(&width, sizeof(int), 1, fo);
        for (int i = 1; i < width + 1; i++)
        {
            for (int j = 1; j < length + 1; j++)
            {
                fread(&grid[i][j], sizeof(int), 1, fo);
                printf("%i", grid[i][j]);
            }
            printf("\n");
        }
        fclose(fo);
    }
    else
    {
        printf("Please enter the length.");
        scanf("%i", &length);
        printf("Please enter the width.");
        scanf("%i", &width);

        if (SDL_Init(SDL_INIT_VIDEO)) //错误判断
        {
            SDL_Log("Can not init video,%s", SDL_GetError());
            return 1;
        }
        SDL_Window *win = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_SHOWN);
        if (win == NULL) //错误判断
        {
            SDL_Log("Can not create window,%s", SDL_GetError());
            return 1;
        }

        CreateWorld(length, width);
        cell();
        while (1)
        {
            ShowTheWorld(length, width, win);
            Operate(length, width);

            SDL_Event event;
            if (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    break;
                }
            }
        }
        SDL_DestroyWindow(win); //退出窗口
    }
    FILE *fp = fopen("game.bin", "wb");
    fwrite(&length, sizeof(int), 1, fp);
    fwrite(&width, sizeof(int), 1, fp);
    for (int i = 1; i < width + 1; i++)
    {
        for (int j = 1; j < length + 1; j++)
        {
            fwrite(&grid[i][j], sizeof(int), 1, fp);
        }
    }
    fclose(fp);
    return 0;
}
