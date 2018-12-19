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
        void update_grid();
        void print_grid();
        //friend func
        friend std::ostream& operator<< (std::ostream &, grid &);
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
        //setters
        void set_rows(int x);
        void set_columns(int y);
};

#endif