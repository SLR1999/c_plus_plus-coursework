#include "supergrid.h"
#include <ctime>
#include <cstdlib>

supergrid::supergrid(){}
supergrid::supergrid(int rows1, int columns1, int rows2, int columns2)
{
    srand(time(0));
    // printf ("check_supergrid");
    rows_supergrid = rows1;
    columns_supergrid = columns1;
    rows_grid = rows2;
    columns_grid = columns2;
    grids = new grid*[rows_supergrid];
    for (int i = 0; i < rows_supergrid; i ++)
    {
        grids[i] = new grid[columns_supergrid];
        for (int j = 0; j < columns_supergrid; j ++)
        {
            grids[i][j] = grid(rows_grid, columns_grid, 'o', i, j);
        }
    }
}
//doublecheck
supergrid::~supergrid()
{
    for (int i = 0; i < rows_supergrid; i ++)
    {
        delete[] grids[i];
    }
    delete[] grids;
    rows_supergrid = 0;
    columns_supergrid = 0;
    rows_grid = 0;
    columns_grid = 0;
}
supergrid::supergrid(const supergrid& grid1)
{
    rows_supergrid = grid1.rows_supergrid;
    columns_supergrid = grid1.columns_supergrid;
    rows_grid = grid1.rows_grid;
    columns_grid = grid1.columns_grid;
    grids = new grid*[rows_supergrid];
    for (int i = 0; i < rows_supergrid; i ++)
    {
        grids[i] = new grid[columns_supergrid];
    }
    for (int i = 0; i < rows_supergrid; i ++)
    {
        for (int j = 0; j < columns_supergrid; j ++)
        {
            grids[i][j] = grid1.grids[i][j];
        }
    }

}
void supergrid::set_rows_supergrid(int x)
{
    rows_supergrid = x;
}
void supergrid::set_columns_supergrid(int y)
{
    columns_supergrid = y;
}
void supergrid::set_rows_grid(int x)
{
    rows_grid = x;
}
void supergrid::set_columns_grid(int y)
{
    columns_grid = y;
}
void supergrid::generate_initial_state_supergrid()
{
    // std::cout << "in generate initial state of supergrid" << std::endl;
    int sum = 0;
    int k;
    for (int i = 0; i < rows_supergrid; i ++)
    {
        for (int j = 0; j < columns_supergrid; j ++)
        {
            // printf("meow\n");
            if (i == 0 || i == rows_supergrid-1 || j == 0 || j == columns_supergrid-1)
            {
                // printf("corner cell\n");
                grids[i][j] = grid(rows_grid, columns_grid, 'o', i, j);
                grids[i][j].generate_initial_state_dead();
            }
            else 
            {
                // printf("not corner cell\n");
                if (i % 2 != 0)
                {
                    if (j % 2 == 0)
                    {
                        grids[i][j] = grid(rows_grid, columns_grid, 'o', i, j);
                        grids[i][j].generate_initial_state_dead();
                    }
                    else
                    {
                        grids[i][j] = grid(rows_grid, columns_grid, '+', i, j);
                        grids[i][j].generate_initial_state_live();
                    }
                }
                else
                {
                    if (j % 2 != 0)
                    {
                        grids[i][j] = grid(rows_grid, columns_grid, 'o', i, j);
                        grids[i][j].generate_initial_state_dead();
                    }
                    else
                    {
                        grids[i][j] = grid(rows_grid, columns_grid, '+', i, j);
                        grids[i][j].generate_initial_state_live();
                    }
                }
            }
        }
    }
    // printf("yo\n");
}
void supergrid::update_neighbourhood_supergrid()
{
    int i, j;
    for (i = 0; i < rows_supergrid; i ++)
    {
        for (j = 0; j < columns_supergrid; j ++)
        {
            if (j == columns_supergrid-1)
                grids[i][j].set_neighbourhood_grid(0, 'o');
            else 
                grids[i][j].set_neighbourhood_grid(0, grids[i][j+1].get_state_grid());  
            if (i == 0 || j == columns_supergrid-1)
                grids[i][j].set_neighbourhood_grid(1, 'o');
            else
                grids[i][j].set_neighbourhood_grid(1,grids[i-1][j+1].get_state_grid()); 
            if (i == 0)
                grids[i][j].set_neighbourhood_grid(2, 'o');
            else
                grids[i][j].set_neighbourhood_grid(2, grids[i-1][j].get_state_grid());    
            if (i == 0 || j == 0)
                grids[i][j].set_neighbourhood_grid(3, 'o');
            else
                grids[i][j].set_neighbourhood_grid(3, grids[i-1][j-1].get_state_grid());     
            if (j == 0)
                grids[i][j].set_neighbourhood_grid(4, 'o');
            else
                grids[i][j].set_neighbourhood_grid(4, grids[i][j-1].get_state_grid());
            if (i == rows_supergrid-1 || j == 0)
                grids[i][j].set_neighbourhood_grid(5, 'o');
            else
                grids[i][j].set_neighbourhood_grid(5, grids[i+1][j-1].get_state_grid());     
            if (i == rows_supergrid-1)
                grids[i][j].set_neighbourhood_grid(6, 'o');
            else
                grids[i][j].set_neighbourhood_grid(6, grids[i+1][j].get_state_grid());
            if (i == rows_supergrid-1 || j == columns_supergrid-1)
                grids[i][j].set_neighbourhood_grid(7, 'o');
            else
                grids[i][j].set_neighbourhood_grid(7, grids[i+1][j+1].get_state_grid());
                
        }
    }
}
void supergrid::print_grid_supergrid()
{
    for (int i = 0; i < rows_supergrid; i ++)
    {
        for (int j = 0; j < columns_supergrid; j ++)
        {
            if (grids[i][j].get_state_grid() == 'o')
                printf ("%c ", grids[i][j].get_state_grid());
            else
                printf ("%c ", grids[i][j].get_state_grid());
        }
        printf ("\n");
    }
}
void supergrid::update_grid_supergrid(int x)
{
    for (int i = 0; i < rows_supergrid; i ++)
    {
        for (int j = 0; j < columns_supergrid; j ++)
        {
            grids[i][j].update_grid(x);
        }
    }
    char **temp;
    temp = new char*[rows_supergrid];
    for (int i = 0; i < rows_supergrid; i ++)
        temp[i] = new char[columns_supergrid];
    for (int i = 0; i < rows_supergrid; i ++)
    {
        for (int j = 0; j < columns_supergrid; j ++)
        {
            temp[i][j] = grids[i][j].get_state_grid();
        }
    }
    // for (int i = 0; i < rows; i ++)
    // {
    //     for (int j = 0; j < columns; j ++)
    //     {
    //         printf ("%c ", temp[i][j]);
    //     }
    //     printf ("\n");
    // }
    // std::cout << "validity" << check_validity(temp) << "\n";
    if (check_validity_supergrid(temp))
    {
        for (int i = 0; i < rows_supergrid; i ++)
        {
            for (int j = 0; j < columns_supergrid; j ++)
            {
                // std::cout << i << j << gridcells[i][j].count_live_neighbors() << "\n";
                if ((grids[i][j].count_live_neighbors_grid() < 2 || grids[i][j].count_live_neighbors_grid() > 3) && (grids[i][j].get_state_grid() == '+'))
                    temp[i][j] = 'o';
                else if ((grids[i][j].count_live_neighbors_grid()) == 3 && grids[i][j].get_state_grid() == 'o')
                    temp[i][j] = '+';
                else
                    temp[i][j] = grids[i][j].get_state_grid();
            }
        }
        if (this->check_validity_supergrid(temp))
        {
            // std::cout << gen << "\n";
            for (int i = 0; i < rows_supergrid; i ++)
            {
                for (int j = 0; j < columns_supergrid; j ++)
                {
                    if (grids[i][j].get_state_grid() == 'o')
                    {
                        if (temp[i][j] == '+')
                        {
                            grids[i][j].set_state_grid(temp[i][j]);
                            grids[i][j].generate_state_live();
                        }
                    }
                    else
                    {
                        if (temp[i][j] == 'o')
                        {
                            grids[i][j].set_state_grid(temp[i][j]);
                            grids[i][j].generate_state_dead();
                        }
                    }
                }
            }
            // this->print_grid();
            this->update_neighbourhood_supergrid();
        }
    }
    for (int i = 0; i < rows_supergrid; i ++)
        delete[] temp[i];
    delete[] temp;
}

std::ostream& operator << (std::ostream& out, supergrid& grid_1)
{
    // for (int i = 0; i < grid_1.rows_supergrid; i ++)
    // {
    //     for (int j = 0; j < grid_1.columns_supergrid; j ++)
    //     {
    //         if (grid_1.grids[i][j].get_state_grid() == 'o')
    //             out << 'o' << " ";
    //         else
    //             out << '+' << " ";
    //     }
    //     out << std::endl;
    // }
    for(int i = 0; i< grid_1.rows_supergrid; i ++){
		for(int l = 0;l < grid_1.rows_grid; l ++){
			for(int j = 0;j < grid_1.columns_supergrid;j ++){
				for(int k = 0;k < grid_1.columns_grid; k ++){
					if(grid_1.grids[i][j].get_grid()[l][k].get_state()=='o') 
                        out << "o";
					else 
                        out << "+";
				}	
				out << " ";
			}
			out << std::endl;
		}
		out << std::endl;
	}
	out << "------------------------------------------" << std::endl;
    return out;
}