#include <stdio.h>
#include <stdlib.h>

int grid[10][10]; //定义一个大小为  的数组
int grid1[10][10];

void CreateWorld(int gridsize)
{
    for (int i = 0; i < gridsize + 1; i++)
    {
        for (int j = 0; j < gridsize + 1; j++)
        {
            grid[i][j] = 0;
        }
    }
}

void ShowTheWorld(int gridsize)
{
    for (int i = 1; i < gridsize + 1; i++)
    {
        for (int j = 1; j < gridsize + 1; j++)
        {
            printf("%i", grid[i][j]);
        }
        printf("\n");
    }
    MakeMove(gridsize);
}

void cell() //pdf内测试程序的细胞
{
    grid[3][3] = 1;
    grid[4][3] = 1;
    grid[2][3] = 1;
    grid[3][1] = 1;
    grid[4][2] = 1;
}

void MakeMove(int gridsize)
{
    for (int i = 1; i < gridsize + 1; i++)
    {
        for (int j = 1; j < gridsize + 1; j++)
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

void Operate(int gridsize)
{
    for (int i = 1; i < gridsize + 1; i++)
    {
        for (int j = 1; j < gridsize + 1; j++)
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
    
    printf("read or not");
    scanf("%c", &a);
    if (a == 'y')
    {
    FILE *fo=fopen("game.bin","rb");
    for (int i = 1; i < gridsize + 1; i++)
    {
        for (int j = 1; j < gridsize + 1; j++)
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
        CreateWorld(gridsize);
        cell();

        ShowTheWorld(gridsize);
        printf("\n");
        for (int i = 0; i < 9; i++)
        {
            Operate(gridsize);
            ShowTheWorld(gridsize);
            printf("\n");
        }
    }
    FILE *fp=fopen("game.bin","wb");
    for (int i = 1; i < gridsize + 1; i++)
    {
        for (int j = 1; j < gridsize + 1; j++)
        {
            fwrite(&grid[i][j], sizeof(int), 1, fp);
        }
    }
    fclose(fp);

}
