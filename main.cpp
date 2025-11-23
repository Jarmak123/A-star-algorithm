#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;

struct Node {
    int x, y;
    float cena_kroku;
    float koszt_ogolny;
};

void wczytaj_grid(vector<vector<float>>& grid){
    ifstream MyFile("./grid.txt");
    grid.resize(20, vector<float>(20));
    for(int i=0; i<20;i++){
        for(int j=0; j<20; j++){
            MyFile >> grid[i][j];
        }
    }
}

float heurystyka(int x_akt, int y_akt, int x_cel, int y_cel)
{
    return round(sqrt(pow((x_akt-x_cel),2)+pow((y_akt-y_cel),2))*100)/100;
}

void wyswietl_grid(vector<vector<float>>& tab){
    for (int i=0; i<20; i++){
        for (int j=0; j<20; j++){
            cout << setw(7) << fixed << setprecision(2) << tab[i][j] << " ";
        }
        cout << endl;
    }
}

bool czy_w_zamknietej(vector<vector<int>>& tablica_zamnieta, int x, int y){
    for (int i=0; i<tablica_zamnieta.size();i++)
    {
        if(tablica_zamnieta[i][0]==x && tablica_zamnieta[i][1]==y)
        {
            return true;
        }
    }
    return false;
}

bool czy_w_otwartej(vector<Node>& otwarta, int x, int y){
    for (int i=0; i<otwarta.size(); i++)
        if(otwarta[i].x==x && otwarta[i].y==y) return true;
    return false;
}

void dodanie_do_tab_otwartej(int x_akt, int y_akt,int cena_akt,int x_cel, int y_cel,vector<vector<float>>& grid,vector<vector<int>>& zamknieta,vector<Node>& otwarta)
{
    int kx[4]={-1,1,0,0};
    int ky[4]={0,0,-1,1};

    for(int i=0;i<4;i++){
        int nx = x_akt + kx[i];
        int ny = y_akt + ky[i];

        if(nx<0 || nx>=20 || ny<0 || ny>=20) continue;
        if(grid[nx][ny] == 5) continue;
        if(czy_w_zamknietej(zamknieta, nx, ny)) continue;

        if(!czy_w_otwartej(otwarta, nx, ny)){
            Node nowy;
            nowy.x = nx;
            nowy.y = ny;
            nowy.cena_kroku = cena_akt;
            nowy.koszt_ogolny = heurystyka(nx, ny, x_cel, y_cel) + nowy.cena_kroku;
            otwarta.push_back(nowy);
        }
    }
}

int main() {
    vector<vector<float>> grid;
    vector<vector<float>> grid_droga; 
    wczytaj_grid(grid);
    wczytaj_grid(grid_droga);
    
    int x_start=0, y_start=0;
    int x_cel, y_cel;

    cout << "Podaj x_cel <0-19>: ";
    cin >> x_cel;
    cout << "Podaj y_cel <0-19>: ";
    cin >> y_cel;

    if(x_cel<0 || x_cel>19 || y_cel<0 || y_cel>19){
        cout << "Bledne wartosci!" << endl;
        return 0;
    }

    vector<vector<int>> zamknieta;
    vector<Node> otwarta;

    int x_akt=x_start;
    int y_akt=y_start;
    float cena=0;

    zamknieta.push_back({x_akt,y_akt});

    while(true){
        cena+=1;
        dodanie_do_tab_otwartej(x_akt,y_akt,cena,x_cel,y_cel, grid, zamknieta, otwarta);

        int naj = 0;
        for(int i=0;i<otwarta.size();i++)
        {
            if(otwarta[i].koszt_ogolny <= otwarta[naj].koszt_ogolny)
            naj=i;
        }

        Node akt = otwarta[naj];

        x_akt = akt.x;
        y_akt = akt.y;
        
        zamknieta.push_back({x_akt,y_akt});

        grid[x_akt][y_akt] = akt.koszt_ogolny;
        
        if(x_akt == x_cel && y_akt == y_cel)
        {
            cout << "znaleziono drogę" << endl;
            break;
        }
    }

    //uzupełnienie grid_droga aby pokazać drogę przez wstawnianie liczby 99 w odpowienie miejsca
    for(int i=0; i<zamknieta.size(); i++)
    {
        grid_droga[zamknieta[i][0]][zamknieta[i][1]]=99;
    }
    cout << "Mapa:" << endl;
    wyswietl_grid(grid);
    cout << "Droga:" << endl;
    wyswietl_grid(grid_droga);
    return 0;
}
