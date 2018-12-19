#ifndef grid_H_
#define grid_H_
#include "gridcell.h"

#include <iostream>

class grid
{
    private:
        gridcell** gridcells;
        int rows, columns;
    public:
        //constructors
        grid();
        grid(gridcell* grids[], int rows1, int columns1);
        //destructor
        ~grid();
        //copy function
        grid(const grid&);
        
        void generate_initial_state(int L);
        void update_neighbourhood();
        // void update_grid(int x);
        void print_grid();
        //friend func
        friend std::ostream& operator<< (std::ostream &, grid &);
        int update_grid(int x)
        {
            char **temp;
            int gen = 0;
            temp = new char*[rows];
            for (int i = 0; i < rows; i ++)
                temp[i] = new char[columns];
            for (int i = 0; i < rows; i ++)
            {
                for (int j = 0; j < columns; j ++)
                {
                    temp[i][j] = gridcells[i][j].get_state();
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
            if (check_validity(temp))
            {
                while (x > 0)
                {
                    for (int i = 0; i < rows; i ++)
                    {
                        for (int j = 0; j < columns; j ++)
                        {
                            // std::cout << i << j << gridcells[i][j].count_live_neighbors() << "\n";
                            if ((gridcells[i][j].count_live_neighbors() < 2 || gridcells[i][j].count_live_neighbors() > 3) && (gridcells[i][j].get_state() == '+'))
                                temp[i][j] = 'o';
                            else if ((gridcells[i][j].count_live_neighbors()) == 3 && gridcells[i][j].get_state() == 'o')
                                temp[i][j] = '+';
                            else
                                temp[i][j] = gridcells[i][j].get_state();
                        }
                    }
                    if (this->check_validity(temp))
                    {
                        // std::cout << gen << "\n";
                        gen++;
                        for (int i = 0; i < rows; i ++)
                        {
                            for (int j = 0; j < columns; j ++)
                            {
                                gridcells[i][j].set_state(temp[i][j]);
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
            for (int i = 0; i < rows; i ++)
                delete[] temp[i];
            delete[] temp;
            return gen;
        }
        //getters
        gridcell** get_grid()
        {
            return gridcells;
        }
        int get_rows()
        {
            return rows;
        }
        int get_columns()
        {
            return columns;
        }
        int check_validity(char* temp[])
        {
            for (int i = 0; i < rows; i ++)
            {
                for (int j = 0; j < columns; j ++)
                {
                    if (i == 0 || j == 0 || i == rows-1 || j == columns-1)
                    {
                        if (temp[i][j] != 'o')
                        {
                            return 0;
                        }
                    }
                }
            }
            return 1;
        }
        //setters
        void set_rows(int x);
        void set_columns(int y);
};

#endif