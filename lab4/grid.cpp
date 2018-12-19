#include "grid.h"
#include <ctime>
#include <cstdlib>

grid::grid(){}
grid::grid(int rows1, int columns1, char state1, int x1, int y1)
{
    rows = rows1;
    columns = columns1;
    gridcells = new gridcell*[rows];
    for (int i = 0; i < rows ; i ++)
        gridcells[i] = new gridcell[columns];
    grid_state = state1;
    grid_x = x1;
    grid_y = y1;
}

grid::~grid()
{
    for (int i = 0; i < rows; i ++)
    {
        delete[] gridcells[i];
    }
    delete[] gridcells;
    rows = 0;
    columns = 0;
    grid_x = 0;
    grid_y = 0;
}
grid::grid(const grid& grid1)
{
    rows = grid1.rows;
    columns = grid1.columns;
    gridcells = new gridcell*[rows];
    for (int i = 0; i < rows; i ++)
    {
        gridcells[i] = new gridcell[columns];
    }
    for (int i = 0; i < rows; i ++)
    {
        for (int j = 0; j < columns; j ++)
        {
            gridcells[i][j] = grid1.gridcells[i][j];
        }
    }
    grid_x = grid1.grid_x;
    grid_y = grid1.grid_y;
    grid_state = grid1.grid_state;
    for (int i = 0; i < 8; i ++)
    {
        grid_neighbourhood[i] = grid1.grid_neighbourhood[i];
    }

}
void grid::set_rows(int x)
{
    rows = x;
}
void grid::set_columns(int y)
{
    columns = y;
}
// void grid::generate_initial_state(int L)
// {
//     int sum = 0;
//     srand(time(0));
//     int k;
//     for (int i = 0; i < rows; i ++)
//     {
//         for (int j = 0; j < columns; j ++)
//         {
//             if (i == 0 || i == rows-1 || j == 0 || j == columns-1){
//                 gridcells[i][j] = gridcell(i, j, 'o');
//                 }
//             else
//             {
//                 if (sum < L)
//                 {
                    
//                     k = rand()%2;
//                     if (k == 1){
//                         sum += 1;
//                         gridcells[i][j] = gridcell(i, j, '+');}
//                     else
//                     {
//                         gridcells[i][j] = gridcell(i, j, 'o');
//                     }
//                 }
//                 else
//                 {
//                     gridcells[i][j] = gridcell(i, j, 'o');
//                 }
//             }
//         }
//     }
// }

grid& grid::operator= (const grid & grid1)
{
    // do the copy
    rows = grid1.rows;
	columns = grid1.columns;
	gridcells = new gridcell*[rows] ;
    for (int i = 0 ; i < rows ; i++) {
        gridcells[i] = new gridcell[columns] ;
		for(int j=0;j<columns;j++) {
			gridcells[i][j] = grid1.gridcells[i][j];
			gridcells[i][j].set_x(i);
			gridcells[i][j].set_y(j);
		}
	}
	grid_x = grid1.grid_x;
	grid_y = grid1.grid_y;
	for(int i=0;i<8;i++){
		grid_neighbourhood[i] = grid1.grid_neighbourhood[i];
	}
	grid_state = grid1.grid_state;
    // return the existing object so we can chain this operator
    return *this;
}
void grid::generate_initial_state_live()
{
    // printf("in gen init stte live\n");
    int live = (int)(0.55*rows*columns)/*+rand()%(int(0.45*rows*columns))*/;
    
    int temp = 0;
    for (int i = 0; i < rows; i ++)
    {
        for (int j = 0; j < columns; j ++)
        {
            
            gridcells[i][j] = gridcell(i, j, 'o');
        }
    }
    srand(time(0));
    while (temp <= live)
    {
        // printf("temp = %d\n",temp);
        // printf("live = %d\n",live);
        int a = 1+rand()%(rows-2);
        int b = 1+rand()%(columns-2);
        if (gridcells[a][b].get_state() == 'o')
        {
            gridcells[a][b].set_state('+');
            temp++;
        }
    }
}

void grid::generate_initial_state_dead()
{
    int live = (int)(0.45*rows*columns)-rand()%int(0.45*rows*columns);
    int temp = 0;
    for (int i = 0; i < rows; i ++)
    {
        for (int j = 0; j < columns; j ++)
        {
            gridcells[i][j] = gridcell(i, j, 'o');
        }
    }
    srand(time(0));
    while (temp < live)
    {
        int a = 1+rand()%(rows-2);
        int b = 1+rand()%(columns-2);
        if (gridcells[a][b].get_state() == 'o')
        {
            gridcells[a][b].set_state('+');
            temp++;
        }
    }
}
void grid::generate_state_live()
{
    int live = int(0.55*rows*columns)/*+rand()%int(0.5*rows*columns)*/;
    int temp = 0;
    for (int i = 0; i < rows; i ++)
    {
        for (int j = 0; j < columns; j ++)
        {
            
            gridcells[i][j] = gridcell(i, j, 'o');
        }
    }
    srand(time(0));
    while (temp <= live)
    {
        int a = 1+rand()%(rows-2);
        int b = 1+rand()%(columns-2);
        if (gridcells[a][b].get_state() == 'o')
        {
            gridcells[a][b].set_state('+');
            temp++;
        }
    }
}

void grid::generate_state_dead()
{
    // printf("in dead\n");
    int live = (int)(0.45*rows*columns)-rand()%int(0.5*rows*columns);
    int temp = 0;
    for (int i = 0; i < rows; i ++)
    {
        for (int j = 0; j < columns; j ++)
        {
            gridcells[i][j] = gridcell(i, j, 'o');
        }
    }
    srand(time(0));
    while (temp < live)
    {
        // printf("temp = %d\n",temp);
        int a = 1+rand()%(rows-2);
        int b = 1+rand()%(columns-2);
        if (gridcells[a][b].get_state() == 'o')
        {
            gridcells[a][b].set_state('+');
            temp++;
        }
    }
}
void grid::update_neighbourhood()
{
    int i, j;
    for (i = 0; i < rows; i ++)
    {
        for (j = 0; j < columns; j ++)
        {
            if (j == columns-1)
                gridcells[i][j].set_neighbourhood(0, 'o');
            else 
                gridcells[i][j].set_neighbourhood(0, gridcells[i][j+1].get_state());  
            if (i == 0 || j == columns-1)
                gridcells[i][j].set_neighbourhood(1, 'o');
            else
                gridcells[i][j].set_neighbourhood(1,gridcells[i-1][j+1].get_state()); 
            if (i == 0)
                gridcells[i][j].set_neighbourhood(2, 'o');
            else
                gridcells[i][j].set_neighbourhood(2, gridcells[i-1][j].get_state());    
            if (i == 0 || j == 0)
                gridcells[i][j].set_neighbourhood(3, 'o');
            else
                gridcells[i][j].set_neighbourhood(3, gridcells[i-1][j-1].get_state());     
            if (j == 0)
                gridcells[i][j].set_neighbourhood(4, 'o');
            else
                gridcells[i][j].set_neighbourhood(4, gridcells[i][j-1].get_state());
            if (i == rows-1 || j == 0)
                gridcells[i][j].set_neighbourhood(5, 'o');
            else
                gridcells[i][j].set_neighbourhood(5, gridcells[i+1][j-1].get_state());     
            if (i == rows-1)
                gridcells[i][j].set_neighbourhood(6, 'o');
            else
                gridcells[i][j].set_neighbourhood(6, gridcells[i+1][j].get_state());
            if (i == rows-1 || j == columns-1)
                gridcells[i][j].set_neighbourhood(7, 'o');
            else
                gridcells[i][j].set_neighbourhood(7, gridcells[i+1][j+1].get_state());
                
        }
    }
}

void grid::update_grid(int x)
{
    char **temp;
    this->update_neighbourhood();
    temp = new char*[rows];
    for (int i = 0; i < rows; i ++)
        temp[i] = new char[columns];
    for (int i = 0; i < rows; i ++)
    {
        for (int j = 0; j < columns; j ++)
        {
            // std::cout << "grids" << gridcells[i][j].get_state() << std::endl;
            temp[i][j] = gridcells[i][j].get_state();
            // std::cout << "temp" << temp[i][j] << std::endl;
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
                    // printf ("lol %c\n", temp[i][j]);
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
            if (this->check_validity(temp))
            {
                for (int i = 0; i < rows; i ++)
                {
                    for (int j = 0; j < columns; j ++)
                    {
                        // std::cout << temp[i][j] << std::endl;
                        gridcells[i][j].set_state(temp[i][j]);
                    }
                }
                if (this->count_live_cells())
                    this->set_state_grid('+');
                else
                    this->set_state_grid('o');
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
}
void grid::print_grid()
{
    for (int i = 0; i < rows; i ++)
    {
        for (int j = 0; j < columns; j ++)
        {
            if (gridcells[i][j].get_state() == 'o')
                printf ("%c ", gridcells[i][j].get_state());
            else
                printf ("%c ", gridcells[i][j].get_state());
        }
        printf ("\n");
    }
}

void grid::set_x_grid(int x1)
{
    grid_x = x1;
}
void grid::set_y_grid(int y1)
{
    grid_y = y1;
}
void grid::set_state_grid(char state1)
{
    grid_state = state1;
}
void grid::set_neighbourhood_grid(int i, char s)
{
    grid_neighbourhood[i] = s;
}
void grid::set_grid(gridcell** cell)
{
    gridcells = cell;
} 

std::ostream& operator << (std::ostream& out, grid& grid_1)
{
    for (int i = 0; i < grid_1.rows; i ++)
    {
        for (int j = 0; j < grid_1.columns; j ++)
        {
            if (grid_1.gridcells[i][j].get_state() == 'o')
                out << 'o' << " ";
            else
                out << '+' << " ";
        }
        out << std::endl;
    }
    return out;
}