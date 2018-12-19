#ifndef grid_H_
#define grid_H_
#include "gridcell.h"

#include <iostream>

class grid
{
    private:
        gridcell** gridcells;
        int rows, columns, grid_x, grid_y;
        char grid_state;
        char grid_neighbourhood[8];
    public:
        //constructors
        grid();
        grid(int rows1, int columns1, char state1, int x1, int y1);
        //destructor
        ~grid();
        //copy function
        grid(const grid&);
        
        void generate_initial_state_live();
        void generate_initial_state_dead();
        void generate_state_live();
        void generate_state_dead();
        void update_neighbourhood();
        void update_grid(int x);
        // void update_grid(int x);
        void print_grid();
        grid& operator= (const grid &);
        //friend func
        friend std::ostream& operator<< (std::ostream &, grid &);
        int count_live_neighbors_grid()
        {
            int sum = 0;
            for (int i = 0; i < 8; i ++)
            {
                
                if (grid_neighbourhood[i] == '+')
                    sum += 1;
            }
            return sum;
        }
        int count_live_cells()
        {
            int sum = 0;
            // std::cout << *this;
            for (int i = 0; i < rows; i ++)
            {
                for (int j = 0; j< columns; j ++)
                {
                    if (gridcells[i][j].get_state() == '+')
                        sum += 1;
                }
            }
            // printf ("sum = %d\n", sum);
            if (sum >= 0.55*rows*columns)
                return 1;
            else 
                return 0;
        }
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
        int get_x_grid()
        {
            return grid_x;
        }
        int get_y_grid()
        {
            return grid_y;
        }
        char get_state_grid()
        {
            return grid_state;
        }
        char* get_neighbourhood_grid()
        {
            return grid_neighbourhood;
        }
        //setters
        void set_x_grid(int x1);
        void set_y_grid(int y1);
        void set_state_grid(char state1);
        void set_neighbourhood_grid(int i, char s);
        void set_rows(int x);
        void set_grid(gridcell** cells);
        void set_columns(int y);
};

#endif