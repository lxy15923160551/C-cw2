#include <stdio.h>
#include <stdlib.h>

int grid[1000][1000]; //定义一个大小为  的数组
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

void ShowTheWorld(int length, int width)
{
    for (int i = 1; i < width + 1; i++)
    {
        for (int j = 1; j < length + 1; j++)
        {
            printf("%i", grid[i][j]);
        }
        printf("\n");
    }
    MakeMove(length, width);
}

void cell() //pdf内测试程序的细胞
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
            if (grid[i][j] == 1) //活细胞
            {
                if (NumAround(i, j) == 0 || NumAround(i, j) == 1)
                {
                    grid[i][j] = 0; //0或1个 死
                }
                else if (NumAround(i, j) == 2 || NumAround(i, j) == 3)
                {
                    grid[i][j] = 1; //2或3个 活
                }
                else
                {
                    grid[i][j] = 0; //超过3个 死
                }
            }
            else if (grid[i][j] == 0 && NumAround(i, j) == 3) //死细胞
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

int main()
{
    char a;
    int gridsize = 5;
    int length;
    int width;

    printf("Whether to read data from a local file(y/n)");
    scanf("%c", &a);
    while (a != 'y' && a != 'n')
    {
        printf("Whether to read data from a local file(y/n)");
        scanf("%c", &a);
    }
    if (a == 'y') //读取本地数据
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

        CreateWorld(length, width);
        cell();

        ShowTheWorld(length, width);
        printf("\n");
        for (int i = 0; i < 9; i++)
        {
            Operate(length, width);
            ShowTheWorld(length, width);
            printf("\n");
        }
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
}
