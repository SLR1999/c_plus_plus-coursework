#include "gridcell.h"

gridcell::gridcell(){}
gridcell::gridcell(int x1, int y1, char state1)
{
    x = x1;
    y = y1;
    state = state1;
}
gridcell::~gridcell()
{
    x = 0;
    y = 0;
    state = '0';
}
gridcell::gridcell(const gridcell& grid_cell)
{
    x = grid_cell.x;
    y = grid_cell.y;
    state = grid_cell.state;
    for (int i = 0; i < 8; i ++)
    {
        neighbourhood[i] = grid_cell.neighbourhood[i];
    }
}
void gridcell::set_x(int x1)
{
    x = x1;
}
void gridcell::set_y(int y1)
{
    y = y1;
}
void gridcell::set_state(char state1)
{
    state = state1;
}
void gridcell::set_neighbourhood(int i, char s)
{
    neighbourhood[i] = s;
}
std::ostream& operator<< (std::ostream & out, gridcell & cell)
{
    if (cell.get_state() == 'o')
        out << 'o' << " ";
    else
        out << '+' << " ";
    return out;
}
