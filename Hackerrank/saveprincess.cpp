/*
*
* Hackerrank: Bot saves princess
* 13.9 points
*
*/
#include <iostream>
#include <vector>
using namespace std;
void displayPathtoPrincess(int n, vector <string> grid){
    //your logic here
    int m = grid[0].size();
    int x = 0, y = 0;
    bool isfind = false;
    for(int i = 0; i < n; ++ i){
        for(int j = 0; j < m; ++ j){
            if(grid[i][j] == 'm'){
                x = i;
                y = j;
                isfind = true;
                break;
            }
        }
        if(isfind)
            break;
    }
    
    if(grid[0][0] == 'p'){
        for(int i = 0; i < x; ++ i)
            puts("UP");
        for(int j = 0; j < y; ++ j)
            puts("LEFT");
    }else if(grid[0][m - 1] == 'p'){
        for(int i = 0; i < x; ++ i)
            puts("UP");
        for(int j = y + 1; j < m; ++ j)
            puts("RIGHT");
    }else if(grid[n - 1][0] == 'p'){
        for(int i = x + 1; i < n; ++ i)
            puts("DOWN");
        for(int j = 0; j < y; ++ j)
            puts("LEFT");
    }else{
        for(int i = x + 1; i < n; ++ i)
            puts("UP");
        for(int j = y + 1; j < m; ++ j)
            puts("RIGHT");
    }
}
int main(void) {

    int m;
    vector <string> grid;

    cin >> m;

    for(int i=0; i<m; i++) {
        string s; cin >> s;
        grid.push_back(s);
    }

    displayPathtoPrincess(m,grid);

    return 0;
}

