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
        int update_grid(int x);
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
        void set_grid(gridcell* grid[]);
};

#endif