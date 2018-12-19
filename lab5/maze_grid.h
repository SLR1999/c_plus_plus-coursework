#ifndef maze_grid_H_
#define maze_grid_H_
#include "gridcell.h"
#include "mazectric_grid.h"

#include <iostream>

class maze_grid : public mazectric_grid
{
    public:
        //constructors
        maze_grid();
        maze_grid(gridcell* grids[], int rows1, int columns1);
        int update_grid(int x);
};

#endif

