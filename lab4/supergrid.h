#ifndef supergrid_H_
#define supergrid_H_
#include "grid.h"

#include <iostream>

class supergrid
{
    private:
        grid** grids;
        int rows_supergrid, columns_supergrid, rows_grid, columns_grid;
    public:
        //constructors
        supergrid();
        supergrid(int rows1, int columns1, int rows, int columns2);
        //destructor
        ~supergrid();
        //copy function
        supergrid(const supergrid&);
        
        void generate_initial_state_supergrid();
        void update_neighbourhood_supergrid();
        void update_grid_supergrid(int x);
        // void update_grid(int x);
        void print_grid_supergrid();
        //friend func
        friend std::ostream& operator<< (std::ostream &, supergrid &);
        
        //getters
        grid** get_supergrid()
        {
            return grids;
        }
        int get_rows_supergrid()
        {
            return rows_supergrid;
        }
        int get_columns_supergrid()
        {
            return columns_supergrid;
        }
        int get_rows_grid()
        {
            return rows_grid;
        }
        int get_columns_grid()
        {
            return columns_grid;
        }
        int check_validity_supergrid(char* temp[])
        {
            for (int i = 0; i < rows_supergrid; i ++)
            {
                for (int j = 0; j < columns_supergrid; j ++)
                {
                    if (i == 0 || j == 0 || i == rows_supergrid-1 || j == columns_supergrid-1)
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
        void set_rows_supergrid(int x);
        void set_columns_supergrid(int y);
        void set_rows_grid(int x);
        void set_columns_grid(int y);
};

#endif