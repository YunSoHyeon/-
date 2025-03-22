#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {-1, 0, 1, 0};

int m, n;
vector<vector<int>> map(200, vector<int>(200, 1));
vector<vector<bool>> visited(200, vector<bool>(200, false));
pair<int, int> src;
pair<int, int> dst;

typedef struct vertex{
    int x, y;
    int f, g, h;
}Vertex;

struct cmp{
    bool operator()(const Vertex& a, const Vertex& b){
        if(a.f > b.f) return true;
        else if(a.f == b.f){
            if(a.g < b.g) return true;
            else return false;
        }
        else return false;
    }
};

int getManhattan(pair<int, int> cur){
    return (abs(cur.first - src.first) + abs(cur.second - src.second)) * 3;
}

int getEuclidean(pair<int, int> cur){
    return (trunc(sqrt(pow(cur.first - dst.first, 2) + pow(cur.second - dst.second, 2)))) * 3;
}

void aStarAlgorithm(){
    priority_queue<Vertex, vector<Vertex>, cmp> pq;
    Vertex start;
    start.x = src.first;
    start.y = src.second;
    
    pq.push(start);
    visited[start.x][start.y] = true;

    while(!pq.empty()){
        int curX = pq.top().x;
        int curY = pq.top().y;

        visited[curX][curY] = true;
        pq.pop();

        Vertex newVertex;
        for(int i = 0 ; i < 4; i++){
            int nextX = curX + dx[i];
            int nextY = curY + dy[i];
            if(nextX >= 0 && nextX < m && nextY >= 0 && nextY < n) {
                if(nextX == dst.first && nextY == dst.second) {
                    cout << getManhattan(make_pair(curX, curY)) + getEuclidean(make_pair(curX, curY)) << "\n";
                    return;
                }
                if(map[nextX][nextY] == 1 && !visited[nextX][nextY]){
                    newVertex.x = nextX; 
                    newVertex.y = nextY;
                    newVertex.g = getManhattan(make_pair(nextX, nextY));
                    newVertex.h = getEuclidean(make_pair(nextX, nextY));
                    newVertex.f = newVertex.g + newVertex.h;
                    visited[nextX][nextY] = true;
                    pq.push(newVertex);
                }
            }
        }


    }
}

int main(){
    int zero;
    int a, b, c;

    cin >> m >> n;

    cin >> zero;
    for(int i = 0; i < zero; i++){
        cin >> a >> b >> c;
        map[b][c] = 0;
    }

    for(int i = 0; i < 2; i++){
        char code;
        cin >> code >> a >> b;
        if(code == 's')
            src = make_pair(a, b);
        else if(code == 't')
            dst = make_pair(a, b);
    }

    string code;
    int ob;
    cin >> code >> ob;
    for(int i = 0; i < ob; i++){
        int p1x, p1y, p2x, p2y;
        cin >> p1x >> p1y >> p2x >> p2y;
        int col = abs(p1x - p2x) + 1;
        int row = abs(p1y - p2y) + 1;
        
        for(int j = min(p1x, p2x); j < min(p1x, p2x) + col; j++){
            for(int k = min(p1y, p2y); k < min(p1y, p2y) + row; k++){
                map[j][k] = 0;
            }
        }
    }
    aStarAlgorithm();

    return 0;
}