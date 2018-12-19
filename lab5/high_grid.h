#ifndef high_grid_H_
#define high_grid_H_
#include "gridcell.h"
#include "grid.h"

#include <iostream>

class high_grid : public grid
{
    public:
        //constructors
        high_grid();
        high_grid(gridcell* grids[], int rows1, int columns1);
        high_grid(const high_grid&);
        int update_grid(int x);
};

#endif

