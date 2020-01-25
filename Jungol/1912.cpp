#include <iostream>
#include <vector>
#include <algorithm>
#define MAXROOM 500001
using namespace std;
 
int N, M, r1, r2;
 
int visited[MAXROOM];
vector<int> sol;
vector<int> rooms[MAXROOM];
 
 
void dfs(int start) {
    int cur_room = start;
    sol.push_back(cur_room);
    if (sol.size() == N) return;
    visited[cur_room] = 1;
 
    for (int i = 0; i < rooms[cur_room].size(); i++) {
        if (visited[rooms[cur_room][i]] == 0 && sol.size() != N) {
            dfs(rooms[cur_room][i]);
        }
    }
 
}
 
int main() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        cin >> r1 >> r2;
        rooms[r1].push_back(r2);
        rooms[r2].push_back(r1);
    }
    for (int i = 0; i < M; i++) {
        sort(rooms[i].begin(), rooms[i].end());
    }
    dfs(1);
    for (int i = 0; i < sol.size(); i++) {
        cout << sol[i] << " ";
    }
    cout << endl;
 
}
