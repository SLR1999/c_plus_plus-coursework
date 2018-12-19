#ifndef gridcell_H_
#define gridcell_H_

#include <iostream>

class gridcell
{
    private:
        int x, y;
        char state;
        char neighbourhood[8];
    public:
        gridcell();
        gridcell(int x1, int y1, char state1);
        ~gridcell();
        gridcell(const gridcell&);
        int count_live_neighbors()
        {
            int sum = 0;
            for (int i = 0; i < 8; i ++)
            {
                
                if (neighbourhood[i] == '+')
                    sum += 1;
            }
            return sum;
        }
        //setters
        void set_x(int x1);
        void set_y(int y1);
        void set_state(char state1);
        void set_neighbourhood(int i, char s);
        //friend func
        friend std::ostream& operator<< (std::ostream &, gridcell &);
        //setters
        int get_x()
        {
            return x;
        }
        int get_y()
        {
            return y;
        }
        char get_state()
        {
            return state;
        }
        char* get_neighbourhood()
        {
            return neighbourhood;
        }
};

#endif