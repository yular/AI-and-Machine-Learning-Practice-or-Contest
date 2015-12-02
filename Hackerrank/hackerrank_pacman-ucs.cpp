/*
*
* Tag: BFS
* Time: O(n^2)
* Space: O(n^2)
*/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <utility>
#include <queue>
#include <algorithm>
using namespace std;
int dir[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
int mp[510][510];
vector<pair<int, int> > ans;

void bfs( int r, int c, int pacman_r, int pacman_c, int food_r, int food_c, vector <string> &grid){
    for(int i = 0; i < 510; ++ i){
        for(int j = 0; j < 510; ++ j)
            mp[i][j] = -2;
    }
    queue<pair<int,int> > q;
    q.push(make_pair(pacman_r, pacman_c));
    mp[pacman_r][pacman_c] = -1;
    grid[pacman_r][pacman_c] = '%';
    while(!q.empty()){
        pair<int, int> tmp = q.front();
        q.pop();
        //printf("%d %d\n",tmp.first, tmp.second);
        if(tmp.first == food_r && tmp.second == food_c)
            break;
        for(int i = 0; i < 4; ++ i){
            int x = tmp.first + dir[i][0], y = tmp.second + dir[i][1];
            if(x >= 0 && x < r && y >= 0 && y < c && grid[x][y] != '%'){
                q.push(make_pair(x, y));
                mp[x][y] = i;
                grid[x][y] = '%';
            }
        }
    }
    int x = food_r, y = food_c;
    while(mp[x][y] != -1){
        ans.push_back(make_pair(x, y));
        if(mp[x][y] == 0){
            ++ x;
        }else if(mp[x][y] == 1){
            ++ y;
        }else if(mp[x][y] == 2){
            -- y;
        }else if(mp[x][y] == 3){
            -- x;
        }
    }
    ans.push_back(make_pair(pacman_r, pacman_c));
}

int main(void) {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    int r,c, pacman_r, pacman_c, food_r, food_c;
    
    cin >> pacman_r >> pacman_c;
    cin >> food_r >> food_c;
    cin >> r >> c;
    vector <string> grid;

    for(int i=0; i<r; i++) {
        string s; cin >> s;
        grid.push_back(s);
    }

    bfs( r, c, pacman_r, pacman_c, food_r, food_c, grid);
    
    printf("%d\n",ans.size() - 1);
    for(int i = ans.size() - 1; i >= 0; -- i)
        printf("%d %d\n",ans[i].first, ans[i].second);
    return 0;
}
