#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 2147483647

using namespace std;

struct Location { int a, b, c, d; };

struct Coordinate { int x, y, dist; };

struct Output {
    vector<int> order;
    int dist = MAX;
};

vector<Location> path;
vector<int> order;

Coordinate current = {500, 500, 0};
Output answer;

int n;

int manhattan(int p, int q, int u, int v) {
    return abs(p - u) + abs(q - v);
}

void backTracking(int count) {
    if (count > 2) return;
    if (order.size() == n * 2) {
        if (current.dist < answer.dist) {
            answer.dist = current.dist;
            answer.order = order;
        }
        else if(current.dist == answer.dist && order < answer.order)
            answer.order = order;
        return;
    }

    for (int i = 0; i < n; i++) {
        auto it = find(order.begin(), order.end(), (i + 1));
        if (it == order.end()) {
            int move = manhattan(current.x, current.y, path[i].a, path[i].b);
            
            Coordinate original = current;

            current.x = path[i].a;
            current.y = path[i].b;
            current.dist += move;

            order.push_back(i + 1);
            backTracking(count + 1);
            
            order.pop_back();
            current = original;
        } 
        else{
            auto it = find(order.begin(), order.end(), -(i + 1));
            if (it == order.end()) {
               int move = manhattan(current.x, current.y, path[i].c, path[i].d);
            
                Coordinate original = current;

                current.x = path[i].c;
                current.y = path[i].d;
                current.dist += move;

                order.push_back(-(i + 1));
                backTracking(count - 1);

                order.pop_back();
                current = original;
            }
        }
    }
}

int main() {
    cin >> n;
    
    path.resize(n);

    for (int i = 0; i < n; i++) {
        int p, q, u, v;
        cin >> p >> q >> u >> v;
        path[i] = {p, q, u, v};
    }

    backTracking(0);

    for (int i : answer.order)
        cout << i << " ";
    cout << "\n";
    cout << answer.dist;

    return 0;
}
