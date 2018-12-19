#include <fstream>
#include <iostream>
#include <cmath>
#include <string.h>
#include "gridcell.h"
#include "grid.h"
#include "maze_grid.h"
#include "mazectric_grid.h"
#include "high_grid.h"

using namespace std;

int main(int argc, char *argv[])
{
    ifstream inFile;
    ofstream outFile;
    outFile.open("out.txt");
    inFile.open(argv[1]);
    if (!inFile)
    {
        cout << "unable to open file" << "\n";
        exit(1);
    }
    int variant = argv[3][0]-'0';
    string x;
    getline (inFile, x); 
	string delimiter = " ";
	size_t pos = 0;
	string token;
	int rows,columns,gen;
	int count = 0;
	while (count < 3) {
		pos = x.find(delimiter);
		token = x.substr(0, pos);
		if(count == 0) rows = stoi(token);
		else if(count == 1) columns = stoi(token);
		else gen = stoi(token);
		count++;
		x.erase(0, pos + delimiter.length());
	}
    if ((gen!=0) || (!rows || !columns))
    {
        outFile << 0 << " " << 0 << " " << 0 << "\n";
        outFile << "eof" << "\n";
        outFile.close();
    }
    else
    {
        gridcell** gridcells;
        gridcells = new gridcell*[rows];
        for (int i = 0; i < rows; i ++)
            gridcells[i] = new gridcell[columns];
        for (int i = 0; i < rows ; i++)
        {
            getline (inFile, x);
            int a = 0;
            for (int j = 0; j < columns; j ++)
            {
                gridcells[i][j].set_state(x[a]);
                a += 2;
            }
        }
        getline (inFile, x);
        if (x != "eof"){
            outFile << 0 << " " << 0 << " " << 0 << "\n";
            outFile << "eof" << "\n";
            outFile.close();
            }
        else
        {
            if (variant == 1)
            {
                high_grid grids(gridcells, rows, columns);
                // cout << "check0" << endl;
                // cout << grids << endl;
                // cout << "check1" << endl;
                // for (int x = 0; x < 10; x ++)
                // {
                //     for (int y = 0; y < 10; y ++)
                //     {
                //         cout << grids.get_grid()[x][y] << " ";
                //     }
                //     cout << endl;
                // }
                // cout << grids << endl;
                grids.update_neighbourhood();
                // cout << "check2" << endl;
                int gen = grids.update_grid(argv[2][0]-'0');
                // cout << gen << endl;
                if (gen == 0)
                {
                    // cout << "invalid" << "\n";
                    outFile << 0 << " " << 0 << " " << 0 << "\n";
                    outFile << "eof" << "\n";
                    outFile.close();
                }
                else
                {
                    // cout << rows << " " << columns << " " << gen << "\n";
                    // cout << "output" << endl;
                    // cout << grids;
                    // cout << "output after print" << endl;
                    outFile << rows << " " << columns << " " << gen << "\n";
                    outFile << grids;
                }
            }
            else if (variant == 2)
            {
                mazectric_grid grids(gridcells, rows, columns);
                grids.update_neighbourhood();
                int gen = grids.update_grid(argv[2][0]-'0');
                if (gen == 0)
                {
                    // cout << "invalid" << "\n";
                    outFile << 0 << " " << 0 << " " << 0 << "\n";
                    outFile << "eof" << "\n";
                    outFile.close();
                }
                else
                {
                    // cout << rows << " " << columns << " " << gen << "\n";
                    // cout << grids;
                    outFile << rows << " " << columns << " " << gen << "\n";
                    outFile << grids;
                }
            }
            else
            {
                maze_grid grids(gridcells, rows, columns);
                grids.update_neighbourhood();
                int gen = grids.update_grid(argv[2][0]-'0');
                if (gen == 0)
                {
                    // cout << "invalid" << "\n";
                    outFile << 0 << " " << 0 << " " << 0 << "\n";
                    outFile << "eof" << "\n";
                    outFile.close();
                }
                else
                {
                    // cout << rows << " " << columns << " " << gen << "\n";
                    // cout << grids;
                    outFile << rows << " " << columns << " " << gen << "\n";
                    outFile << grids;
                }
            }
        }
    }
    inFile.close();
    return 0;
}