#include <iostream>
#include <fstream>
using namespace std;

void wczytaj_grid(int grid[20][20]){
    ifstream MyFile("./grid.txt");
    for(int i=0; i<20;i++){
        for(int j=0; j<20; j++)
        {
            MyFile >> grid[i][j];
        }
    }
}

void wyswietl_grid(int tab[20][20]){
    for (int i=0; i<20; i++)
    {
        for (int j=0; j<20; j++)
        {
            cout << tab[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int grid[20][20];
    wczytaj_grid(grid);
    wyswietl_grid(grid);

    return 0;
}