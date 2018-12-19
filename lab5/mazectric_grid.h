#ifndef mazectric_grid_H_
#define mazectric_grid_H_
#include "gridcell.h"
#include "grid.h"

#include <iostream>

class mazectric_grid : public grid
{
    public:
        //constructors
        mazectric_grid();
        mazectric_grid(gridcell* grids[], int rows1, int columns1);
        mazectric_grid(const mazectric_grid&);
        int update_grid(int x);
};

#endif

