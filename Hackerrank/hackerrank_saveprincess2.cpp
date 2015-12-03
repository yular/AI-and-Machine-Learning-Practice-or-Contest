/*
*
* Tag: DFS
* Time: O(n^2)
* Space: O(n^2)
*/
#include <iostream>
#include <vector>
using namespace std;
void nextMove(int n, int r, int c, vector <string> grid){
    //your logic here
    int xp = 0, yp = 0;
    bool isfind = false;
    for(int i = 0; i < n; ++ i){
        for(int j = 0; j < n; ++ j){
            if(grid[i][j] == 'p'){
                xp = i;
                yp = j;
                isfind = true;
                break;
            }
        }
        if(isfind)
            break;
    }
    if(xp < r)
        puts("UP");
    else{
        if(xp == r){
          if(yp < c)
              puts("LEFT");
          else
              puts("RIGHT");
        }else{
            puts("DOWN");
        }
    }
}
int main(void) {

    int n, r, c;
    vector <string> grid;

    cin >> n;
    cin >> r;
    cin >> c;

    for(int i=0; i<n; i++) {
        string s; cin >> s;
        grid.push_back(s);
    }

    nextMove(n, r, c, grid);
    return 0;
}
