#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int n, m;
int cnt;
int node;

vector<vector<int>> adj;
vector<int> colorInfo(248);

bool promising(int i){
    node++;
    int j = 0;

    while(i > j){
        if(adj[i][j]&& colorInfo[i] == colorInfo[j])
            return false;
        j++;
    }
    return true;
}

void coloring(int i){
    if(i == n) {
        set<int> colors(colorInfo.begin(), colorInfo.end());
        if (colors.size() == m + 1) {
            cnt++;
        }
    }
    
    else{
        for(int color = 1; color <= m; color++){
            colorInfo[i] = color;
            if(promising(i))
                coloring(i+1);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m;
    adj = vector<vector<int>>(n, vector<int>(n));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> adj[i][j];
    
    coloring(0);
    if(cnt == 0) cout << "no \n";
    else cout << cnt << "\n" << node;
    return 0;
}