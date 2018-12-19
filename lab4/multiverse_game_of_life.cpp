#include <iostream>
#include <cmath>
#include "gridcell.h"
#include "grid.h"
#include "supergrid.h"

using namespace std;
int main(int argc, char** argv)
{
    int nr = stoi(argv[1]);
    int nc = stoi(argv[2]);
    int r = stoi(argv[3]);
    int c = stoi(argv[4]);
    int k = stoi(argv[5]);
    int s = stoi(argv[6]);
    if (0.55*nr*nc <= (nr*nc)-(2*nr)-(2*(nc-2))){
    // printf ("check0");
    supergrid s_grid(nr, nc, r, c);
    // printf ("\n\n\n");
    // printf ("check1");
    s_grid.generate_initial_state_supergrid();
    // cout << s_grid;
    // printf ("check2");
    for (int i = 0; i < s; i ++)
    {
        s_grid.update_grid_supergrid(k);
        // cout << s_grid;
        // printf ("\n\n\n");
        // printf ("check3");
        s_grid.update_neighbourhood_supergrid();
        // printf ("check4");
    }
    cout << s_grid;
    printf ("eof");
    }
    else
    {
        printf ("eof");
    }
}