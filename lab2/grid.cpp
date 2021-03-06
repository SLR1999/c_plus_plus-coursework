#include "grid.h"
#include <ctime>
#include <cstdlib>

grid::grid(){}
grid::grid(gridcell* grids[], int rows1, int columns1)
{
    gridcells = grids;
    rows = rows1;
    columns = columns1;
}

grid::~grid()
{
    for (int i = 0; i < rows; i ++)
    {
        delete[] gridcells[i];
    }
    delete[] gridcells;
    rows = 0;
    columns = 0;
}
grid::grid(const grid& grid1)
{
    rows = grid1.rows;
    columns = grid1.columns;
    gridcells = new gridcell*[rows];
    for (int i = 0; i < rows; i ++)
    {
        gridcells[i] = new gridcell[columns];
    }
    for (int i = 0; i < rows; i ++)
    {
        for (int j = 0; j < columns; j ++)
        {
            gridcells[i][j] = grid1.gridcells[i][j];
        }
    }

}
void grid::set_rows(int x)
{
    rows = x;
}
void grid::set_columns(int y)
{
    columns = y;
}
void grid::generate_initial_state(int L)
{
    int sum = 0;
    srand(time(0));
    int k;
    for (int i = 0; i < rows; i ++)
    {
        for (int j = 0; j < columns; j ++)
        {
            if (i == 0 || i == rows-1 || j == 0 || j == columns-1){
                gridcells[i][j] = gridcell(i, j, '0');
                }
            else
            {
                if (sum < L)
                {
                    
                    k = rand()%2;
                    if (k == 1){
                        sum += 1;
                        gridcells[i][j] = gridcell(i, j, '1');}
                    else
                    {
                        gridcells[i][j] = gridcell(i, j, '0');
                    }
                }
                else
                {
                    gridcells[i][j] = gridcell(i, j, '0');
                }
            }
        }
    }
}
void grid::update_neighbourhood()
{
    int i, j;
    for (i = 0; i < rows; i ++)
    {
        for (j = 0; j < columns; j ++)
        {
            if (j == columns-1)
                gridcells[i][j].set_neighbourhood(0, '0');
            else 
                gridcells[i][j].set_neighbourhood(0, gridcells[i][j+1].get_state());  
            if (i == 0 || j == columns-1)
                gridcells[i][j].set_neighbourhood(1, '0');
            else
                gridcells[i][j].set_neighbourhood(1,gridcells[i-1][j+1].get_state()); 
            if (i == 0)
                gridcells[i][j].set_neighbourhood(2, '0');
            else
                gridcells[i][j].set_neighbourhood(2, gridcells[i-1][j].get_state());    
            if (i == 0 || j == 0)
                gridcells[i][j].set_neighbourhood(3, '0');
            else
                gridcells[i][j].set_neighbourhood(3, gridcells[i-1][j-1].get_state());     
            if (j == 0)
                gridcells[i][j].set_neighbourhood(4, '0');
            else
                gridcells[i][j].set_neighbourhood(4, gridcells[i][j-1].get_state());
            if (i == rows-1 || j == 0)
                gridcells[i][j].set_neighbourhood(5, '0');
            else
                gridcells[i][j].set_neighbourhood(5, gridcells[i+1][j-1].get_state());     
            if (i == rows-1)
                gridcells[i][j].set_neighbourhood(6, '0');
            else
                gridcells[i][j].set_neighbourhood(6, gridcells[i+1][j].get_state());
            if (i == rows-1 || j == columns-1)
                gridcells[i][j].set_neighbourhood(7, '0');
            else
                gridcells[i][j].set_neighbourhood(7, gridcells[i+1][j+1].get_state());
                
        }
    }
}
void grid::update_grid()
{
    char temp[rows+1][columns+1];
    int i, j;
    for (i = 0; i < rows; i ++)
    {
        for (j = 0; j < columns; j ++)
        {
            if ((gridcells[i][j].count_live_neighbors() < 2 || gridcells[i][j].count_live_neighbors() > 3) && (gridcells[i][j].get_state() == '1'))
                temp[i][j] = '0';
            else if ((gridcells[i][j].count_live_neighbors()) == 3 && gridcells[i][j].get_state() == '0')
                temp[i][j] = '1';
            else
                temp[i][j] = gridcells[i][j].get_state();
        }
    }
    for (i = 0; i < rows; i ++)
    {
        for (j = 0; j < columns; j ++)
        {
            gridcells[i][j].set_state(temp[i][j]);
        }
    }
}
void grid::print_grid()
{
    for (int i = 0; i < rows; i ++)
    {
        for (int j = 0; j < columns; j ++)
        {
            if (gridcells[i][j].get_state() == '0')
                printf ("%c ", gridcells[i][j].get_state());
            else
                printf ("%c ", gridcells[i][j].get_state());
        }
        printf ("\n");
    }
}

std::ostream& operator << (std::ostream& out, grid& grid_1)
{
    for (int i = 0; i < grid_1.rows; i ++)
    {
        for (int j = 0; j < grid_1.columns; j ++)
        {
            if (grid_1.gridcells[i][j].get_state() == '0')
                out << 'o' << " ";
            else
                out << '+' << " ";
        }
        out << std::endl;
    }
    return out;
}