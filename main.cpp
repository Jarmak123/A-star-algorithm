#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;

void wczytaj_grid(vector<vector<int>>& grid){
    ifstream MyFile("./grid.txt");
    grid.resize(20, vector<int>(20));
    for(int i=0; i<20;i++){
        for(int j=0; j<20; j++)
        {
            MyFile >> grid[i][j];
        }
    }
}

float heurystyka(int x_akt, int y_akt, int x_cel, int y_cel)
{
    return sqrt(pow((x_akt-x_cel),2)+pow((y_akt-y_cel),2));
}

void wyswietl_grid(vector<vector<int>>& tab){
    for (int i=0; i<20; i++)
    {
        for (int j=0; j<20; j++)
        {
            cout << tab[i][j] << " ";
        }
        cout << endl;
    }
}

// void czy_w_zakresie(int x_akt, int y_akt, vector<vector<int>>& grid, int cena_kroki, ){
//     int dx[] = {-1, 1, 0, 0};
//     int dy[] = {0, 0, -1, 1};
//     //góra dól lewo prawo

//     if (x_akt >= 0 && x_akt < grid.size() && y_akt >= 0 && y_akt < grid[x_akt].size()) {
//         int fpoz = cena_kroki + heurystyka(tablica_zamnieta.back()[0],tablica_zamnieta.back()[1],x_cel,y_cel)
//     }
// }

//kolejnosc ruchów to góra, dół lewo prawo
int main() {
    vector<vector<int>> grid; 
    wczytaj_grid(grid);
    wyswietl_grid(grid);

    int x_start=0;
    int y_start=0;
    int x_cel;
    cout << "Podaj x_cel <zakres od 0-19> :";
    cin >> x_cel;
    int y_cel; 
    cout << "Podaj y_cel <zakres od 0-19> :";
    cin >> y_cel;

    if(x_cel > 19 || x_cel < 0 || y_cel > 19 || y_cel < 0)
    {
        cout << "Błędne wartości celów";
        return 0;
    }

    vector<vector<int>> tablica_zamnieta;
    vector<vector<int>> tablica_otwarta;
    tablica_zamnieta.push_back({x_start,y_start});
    cout << "Cel: X=" << x_cel << " Y=" << y_cel << endl;
    int cena_kroki=0;
    int x_akt = x_start;
    int y_akt = y_start;

    while(1){
        cena_kroki++;
        int kx[] = {-1, 1, 0, 0};
        int ky[] = {0, 0, -1, 1};
        
        for(int i=0; i<4; i++){
            int nx = x_akt + kx[i];
            int ny = y_akt + ky[i];

            if (x_akt >= 0 && x_akt < grid.size() && grid[x_akt][y_akt]!=5 && y_akt >= 0 && y_akt < grid[x_akt].size()) 
            {
                int fpoz = cena_kroki + heurystyka(tablica_zamnieta.back()[0],tablica_zamnieta.back()[1],x_cel,y_cel);
            }
        }
    }

    return 0;
}