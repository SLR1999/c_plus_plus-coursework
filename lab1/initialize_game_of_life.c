#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct gridcell
{
    int x, y;
    int state;
    int neighbourhood[8];
};
void print_grid(int x, int y, struct gridcell** grid)
{
    int i, j;
    for (i = 0; i < x; i ++)
    {
        for (j = 0; j < y; j ++)
        {
            if (grid[i][j].state == 0)
                printf ("%d ", grid[i][j].state);
            else
                printf ("%d ", grid[i][j].state);
        }
        printf ("\n");
    }
}
void generate_initial_state(int x, int y, int L, struct gridcell** grid)
{
    int i,j;
    int sum = 0;
    int k;
    for (i = 0; i < x; i ++)
    {
        for (j = 0; j < y; j ++)
        {
            if (i == 0 || i == x-1 || j == 0 || j == y-1){
                grid[i][j].x = i;
                grid[i][j].y = j;
                grid[i][j].state = 0;}
            else
            {
                if (sum < L)
                {
                    k = 1;
                    if (k == 1){
                        sum += 1;
                        grid[i][j].state = 1;
                        printf ("yo %d\n", grid[i][j].state);
                        grid[i][j].x = i;
                        grid[i][j].y = j;}
                    else
                    {
                        grid[i][j].state == 0;
                        grid[i][j].x = i;
                        grid[i][j].y = j;
                    }
                }
                else
                {
                    grid[i][j].state == 0;
                    grid[i][j].x = i;
                    grid[i][j].y = j;
                }
            }
            // printf ("hola");
            // print_grid(x, y, grid);
        }
    }
}
void update_neighbourhood(int x, int y, int L, struct gridcell** grid)
{
    int i, j;
    for (i = 0; i < x; i ++)
    {
        for (j = 0; j < y; j ++)
        {
            if (j == y-1)
                grid[i][j].neighbourhood[0] = 0;
            else 
                grid[i][j].neighbourhood[0] = grid[i][j+1].state;  
            if (i == 0 || j == y-1)
                grid[i][j].neighbourhood[1] = 0;
            else
                grid[i][j].neighbourhood[1] = grid[i-1][j+1].state; 
            if (i == 0)
                grid[i][j].neighbourhood[2] = 0;
            else
                grid[i][j].neighbourhood[2] = grid[i-1][j].state;    
            if (i == 0 || j == 0)
                grid[i][j].neighbourhood[3] = 0;
            else
                grid[i][j].neighbourhood[3] = grid[i-1][j-1].state;     
            if (j == 0)
                grid[i][j].neighbourhood[4] = 0;
            else
                grid[i][j].neighbourhood[4] = grid[i][j-1].state;
            if (i == x-1 || j == 0)
                grid[i][j].neighbourhood[5] = 0;
            else
                grid[i][j].neighbourhood[5] = grid[i+1][j-1].state;     
            if (i == x-1)
                grid[i][j].neighbourhood[6] = 0;
            else
                grid[i][j].neighbourhood[6] = grid[i+1][j].state;
            if (i == x-1 || j == y-1)
                grid[i][j].neighbourhood[7] = 0;
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
        // printf ("%c\n", cell.neighbourhood[i]);
        if (cell.neighbourhood[i] == 1)
            sum += 1;
    }
    return sum;
}
void update_each_cell_neighborhood(int x, int y, struct gridcell cell, struct gridcell** grid)
{
    if ((count_live_neighbors(cell) < 2 || count_live_neighbors(cell) > 3) && cell.state == 1)
    {
        cell.state = 0;
        if (cell.y < y-1)
            grid[cell.x][(cell.y)+1].neighbourhood[4] = 0;
        if (cell.x > 0 && cell.y < y-1)
            grid[(cell.x)-1][(cell.y)+1].neighbourhood[5] = 0;
        if (cell.x > 0)
            grid[(cell.x)-1][cell.y].neighbourhood[6] = 0;
        if (cell.x > 0 && cell.y > 0)
            grid[(cell.x)-1][(cell.y)-1].neighbourhood[7] = 0;
        if (cell.y > 0)
            grid[cell.x][(cell.y)-1].neighbourhood[0] = 0;
        if (cell.y > 0 && cell.x < x-1)
            grid[(cell.x)-1][(cell.y)-1].neighbourhood[1] = 0;
        if (cell.x < x-1)
            grid[(cell.x)+1][cell.y].neighbourhood[2] = 0;
        if (cell.x < x-1 && cell.y < y-1)
            grid[(cell.x)+1][(cell.y)+1].neighbourhood[3] = 0;
    }
    if (count_live_neighbors(cell) == 3 && cell.state == 0)
    {
        cell.state = 1;
        if (cell.y < y-1)
            grid[cell.x][(cell.y)+1].neighbourhood[4] = 1;
        if (cell.x > 0 && cell.y < y-1)
            grid[(cell.x)-1][(cell.y)+1].neighbourhood[5] = 1;
        if (cell.x > 0)
            grid[(cell.x)-1][cell.y].neighbourhood[6] = 1;
        if (cell.x > 0 && cell.y > 0)
            grid[(cell.x)-1][(cell.y)-1].neighbourhood[7] = 1;
        if (cell.y > 0)
            grid[cell.x][(cell.y)-1].neighbourhood[0] = 1;
        if (cell.y > 0 && cell.x < x-1)
            grid[(cell.x)-1][(cell.y)-1].neighbourhood[1] = 1;
        if (cell.x < x-1)
            grid[(cell.x)+1][cell.y].neighbourhood[2] = 1;
        if (cell.x < x-1 && cell.y < y-1)
            grid[(cell.x)+1][(cell.y)+1].neighbourhood[3] = 1;
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
        // print_grid(x, y, grid);
        generate_initial_state(x, y, l, grid);
        print_grid(x, y, grid);
        printf ("\n");
        update_neighbourhood(x, y, l, grid);
        for (i = 0; i < x; i ++)
        {
            for (j = 0; j < y; j ++)
            {
                for (k = 0; k < 8; k ++)
                {
                    printf ("%d ", grid[i][j].neighbourhood[k]);
                }
                printf ("\n");
            }
        }
        // print_grid(x, y, grid);
        // printf ("\n");
        int temp;
        for (i = 0; i < x; i ++)
        {
            for (j = 0; j < y; j ++)
            {
                update_each_cell_neighborhood(x, y, grid[i][j], grid);
                // printf ("\n");
            }
        }
        // print_grid(x, y, grid);
        printf ("\n");
        for (i = 0; i < x; i ++)
        {
            for (j = 0; j < y; j ++)
            {
                printf ("%d ", count_live_neighbors(grid[i][j]));
            }
            printf ("\n");
        }
    }
    else
        printf ("invalid input");
}