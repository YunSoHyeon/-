#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<pair<int, int>> city[21];

vector<int> dijkstra(int start, int N){
    vector<int> timeOfPollution(N, 1e9);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    timeOfPollution[start] = 0;
    pq.push({ 0, start });

    while(!pq.empty()){
        int curTime = pq.top().first;
        int curCity = pq.top().second;
        
        pq.pop();

        if(timeOfPollution[curCity] < curTime) continue;
        
        for(int i = 0; i < city[curCity].size(); i++){
            int nextCity = city[curCity][i].first;
            int nextTime = curTime + city[curCity][i].second;

            if(nextTime < timeOfPollution[nextCity]){
                timeOfPollution[nextCity] = nextTime;
                pq.push({ nextTime, nextCity });
            }
        }
    }
    return timeOfPollution;
}

int main(){
    int N, c1, c2;
    int num1, num2, time;
    cin >> N >> c1 >> c2;

    for(int i = 0; i < N - 1; i++){
        cin >> num1 >> num2 >> time;
        city[num1].push_back( {num2, time });
        city[num2].push_back( {num1, time });
    }
    
    vector<int> pltTime1 = dijkstra(c1, N + 1);
    vector<int> pltTime2 = dijkstra(c2, N + 1);

    vector<pair<int, int>> result;

    for(int i = 1; i < pltTime1.size(); i++){
        if(i == c1 || i == c2) continue;
        pltTime1[i] = min(pltTime1[i], pltTime2[i]);
        result.push_back({ pltTime1[i], i });
    }

    sort(result.begin(), result.end());
    for(int i = 0; i < result.size(); i++)
        cout << result[i].second << "\n";

    return 0;
}