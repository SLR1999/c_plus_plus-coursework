#include <iostream>
#include <cmath>
#include "grid.h"
#include "gridcell.h"

using namespace std;
int main()
{
    int x, y, l;
    // scanf ("%d %d %d", &x, &y, &l);
    cin >> x >> y >> l;
    gridcell** gridcells;
    if ((x*y)-(2*x)-(2*y)+4 >= l)
    {
        gridcells = new gridcell*[x];
        for (int i = 0; i < x; i ++)
        {
            gridcells[i] = new gridcell[y];
        }
        
        grid grids(gridcells, x, y);
        grids.generate_initial_state(l);
        // grids.print_grid();
        // cout << grids;
        grids.update_neighbourhood();
        // grids.update_grid();
        // cout << grids;
        // grids.update_neighbourhood();
        int sum = 0;
        for (int i = 0; i < x; i ++)
        {
            for (int j = 0; j < y; j ++)
            {
                // printf ("%d ", grids.get_grid()[i][j].count_live_neighbors());
                sum += grids.get_grid()[i][j].count_live_neighbors();
            }
            // printf ("\n");
        }
        cout << sum << endl;
    }
    else
        cout << 0 << endl;
}