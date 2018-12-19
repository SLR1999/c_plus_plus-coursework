#include "maze_grid.h"
#include <ctime>
#include <cstdlib>

maze_grid::maze_grid(){}
maze_grid::maze_grid(gridcell* grids[], int rows1, int columns1):mazectric_grid(grids, rows1, columns1)
{
    // mazectric_grid(grids, rows1, columns1);
}
int maze_grid::update_grid(int x)
{
    char **temp;
    int gen = 0;
    temp = new char*[this->get_rows()];
    for (int i = 0; i < this->get_rows(); i ++)
        temp[i] = new char[this->get_columns()];
    for (int i = 0; i < this->get_rows(); i ++)
    {
        for (int j = 0; j < this->get_columns(); j ++)
        {
            temp[i][j] = this->get_grid()[i][j].get_state();
        }
    }
    this->update_neighbourhood();
    // for (int i = 0; i < this->get_rows(); i ++)
    // {
    //     for (int j = 0; j < this->get_columns(); j ++)
    //     {
    //         printf ("%c ", temp[i][j]);
    //     }
    //     printf ("\n");
    // }
    // std::cout << "validity" << check_validity(temp) << "\n";
    if (check_validity(temp))
    {
        while (x > 0)
        {
            for (int i = 0; i < this->get_rows(); i ++)
            {
                for (int j = 0; j < this->get_columns(); j ++)
                {
                    // std::cout << i << j << this->get_grid()[i][j].count_live_neighbors() << "\n";
                    if ((this->get_grid()[i][j].count_live_neighbors() < 1 || this->get_grid()[i][j].count_live_neighbors() > 5) && (this->get_grid()[i][j].get_state() == '+'))
                        temp[i][j] = 'o';
                    else if (((this->get_grid()[i][j].count_live_neighbors() == 3) )&& this->get_grid()[i][j].get_state() == 'o')
                        temp[i][j] = '+';
                    else
                        temp[i][j] = this->get_grid()[i][j].get_state();
                }
            }
            if (this->check_validity(temp))
            {
                gen++;
                // std::cout << gen << "\n";
                for (int i = 0; i < this->get_rows(); i ++)
                {
                    for (int j = 0; j < this->get_columns(); j ++)
                    {
                        this->get_grid()[i][j].set_state(temp[i][j]);
                    }
                }
                // this->print_grid();
                this->update_neighbourhood();
            }
            else
            {
                // std::cout << "invalid" << "\n";
                break;
            }
            x--;
        }
    }
    for (int i = 0; i < this->get_rows(); i ++)
        delete[] temp[i];
    delete[] temp;
    return gen;
}
