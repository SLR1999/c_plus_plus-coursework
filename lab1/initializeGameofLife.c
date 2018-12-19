#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

struct gridcell
{
    int x, y;
    char state;
    char neighbourhood[8];
};
void print_grid(int x, int y, struct gridcell** grid)
{
    int i, j;
    for (i = 0; i < x; i ++)
    {
        for (j = 0; j < y; j ++)
        {
            if (grid[i][j].state == '0')
                printf ("%c ", 'o');
            else
                printf ("%c ", '+');
        }
        printf ("\n");
    }
}
void generate_initial_state(int x, int y, int L, struct gridcell** grid)
{
    int i,j;
    int sum = 0;
    int k;
    srand(time(0));
    for (i = 0; i < x; i ++)
    {
        for (j = 0; j < y; j ++)
        {
            if (i == 0 || i == x-1 || j == 0 || j == y-1){
                grid[i][j].x = i;
                grid[i][j].y = j;
                grid[i][j].state = '0';}
            else
            {
                if (sum < L)
                {
                    
                    k = rand()%2;
                    if (k == 1){
                        sum += 1;
                        grid[i][j].state = '1';
                        grid[i][j].x = i;
                        grid[i][j].y = j;}
                    else
                    {
                        grid[i][j].state = '0';
                        grid[i][j].x = i;
                        grid[i][j].y = j;
                    }
                }
                else
                {
                    grid[i][j].state = '0';
                    grid[i][j].x = i;
                    grid[i][j].y = j;
                }
            }
        }
    }
}
void update_neighbourhood(int x, int y, struct gridcell** grid)
{
    int i, j;
    for (i = 0; i < x; i ++)
    {
        for (j = 0; j < y; j ++)
        {
            if (j == y-1)
                grid[i][j].neighbourhood[0] = '0';
            else 
                grid[i][j].neighbourhood[0] = grid[i][j+1].state;  
            if (i == 0 || j == y-1)
                grid[i][j].neighbourhood[1] = '0';
            else
                grid[i][j].neighbourhood[1] = grid[i-1][j+1].state; 
            if (i == 0)
                grid[i][j].neighbourhood[2] = '0';
            else
                grid[i][j].neighbourhood[2] = grid[i-1][j].state;    
            if (i == 0 || j == 0)
                grid[i][j].neighbourhood[3] = '0';
            else
                grid[i][j].neighbourhood[3] = grid[i-1][j-1].state;     
            if (j == 0)
                grid[i][j].neighbourhood[4] = '0';
            else
                grid[i][j].neighbourhood[4] = grid[i][j-1].state;
            if (i == x-1 || j == 0)
                grid[i][j].neighbourhood[5] = '0';
            else
                grid[i][j].neighbourhood[5] = grid[i+1][j-1].state;     
            if (i == x-1)
                grid[i][j].neighbourhood[6] = '0';
            else
                grid[i][j].neighbourhood[6] = grid[i+1][j].state;
            if (i == x-1 || j == y-1)
                grid[i][j].neighbourhood[7] = '0';
            else
                grid[i][j].neighbourhood[7] = grid[i+1][j+1].state;
                
        }
    }
}

int count_live_neighbors(struct gridcell cell)
{
    int i, sum = 0;
    for (i = 0; i < 8; i ++)
    {
        if (cell.neighbourhood[i] == '1')
            sum += 1;
    }
    return sum;
}

void update_grid(int x, int y,  struct gridcell** grid)
{
    char temp[x+1][y+1];
    int i, j;
    for (i = 0; i < x; i ++)
    {
        for (j = 0; j < y; j ++)
        {
            if ((count_live_neighbors(grid[i][j]) < 2 || count_live_neighbors(grid[i][j]) > 3) && grid[i][j].state == '1')
                temp[i][j] = '0';
            else if (count_live_neighbors(grid[i][j]) == 3 && grid[i][j].state == '0')
                temp[i][j] = '1';
            else
                temp[i][j] = grid[i][j].state;
        }
    }
    for (i = 0; i < x; i ++)
    {
        for (j = 0; j < y; j ++)
        {
            grid[i][j].state = temp[i][j];
        }
    }
}

int main()
{
    int x, y, l, i, j, k;
    scanf ("%d %d %d", &x, &y, &l);
    if ((x*y)-(2*x)-(2*y)+4 >= l)
    {
        struct gridcell* grid[x]; 
        for (i = 0; i < x; i ++) 
            grid[i] = (struct gridcell*)malloc(y * sizeof(struct gridcell));
        generate_initial_state(x, y, l, grid);
        // print_grid(x, y, grid);
        // printf ("\n");
        update_neighbourhood(x, y, grid);
        // update_grid(x, y, grid);
        // print_grid(x, y, grid);
        // printf ("\n");
        // update_neighbourhood(x, y, grid);
        int sum = 0;
        // printf ("\n");
        for (i = 0; i < x; i ++)
        {
            for (j = 0; j < y; j ++)
            {
                // printf ("%d ", count_live_neighbors(grid[i][j]));
                sum += count_live_neighbors(grid[i][j]);
            }
        }
        printf("%d\n", sum);
    }
    else
        printf ("0");
}