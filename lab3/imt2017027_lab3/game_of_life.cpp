#include <fstream>
#include <iostream>
#include <cmath>
#include <string.h>
#include "gridcell.h"
#include "grid.h"

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
    // int rows = x[0]-'0';
    // int columns = x[2]-'0';
    // int gen = x[4]-'0';
    // cout << rows << " "<< columns << "  " << gen << "\n";
    if ((gen!=0) || (!rows || !columns))
    {
        // cout << "invalid" << "\n";
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
            // cout << i << " ";
            // cout << x << "\n";
            int a = 0;
            for (int j = 0; j < columns; j ++)
            {
                // cout << "val" << x[a] << " ";
                gridcells[i][j].set_state(x[a]);
                a += 2;
            }
        }
        getline (inFile, x);
        if (x != "eof"){
            // cout << "invalid" << "\n";
            outFile << 0 << " " << 0 << " " << 0 << "\n";
            outFile << "eof" << "\n";
            outFile.close();
            }
        else
        {
            grid grids(gridcells, rows, columns);
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
                cout << rows << " " << columns << " " << gen << "\n";
                grids.print_grid();
                outFile << rows << " " << columns << " " << gen << "\n";
                outFile << grids;
            }
            // grids.update_neighbourhood();
        }
    }
    inFile.close();
    return 0;
}