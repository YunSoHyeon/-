#include <iostream>
#include <algorithm>

using namespace std;

int main(void) {
    int P, N, M, T;
    int start, end, noise;

    cin >> P >> N;
    cin >> M;

    int schedule[N + 1];
    int sum[N + 1];
    
    fill_n(schedule, N + 1, P);
    fill_n(sum, N + 1, 0);

    for(int i = 0; i < M; i++){
        cin >> T;
        for(int j = 0; j < T; j++){
            cin >> start >> end >> noise;
            for(int k = 1; k <= end - start; k++)
                schedule[start + k] += noise;
        }
    }

    for(int i = 1; i <= N; i++){
        if(sum[i - 1] + schedule[i] > schedule[i])
            sum[i] = sum[i - 1] + schedule[i];
        else   
            sum[i] = schedule[i];
    }

    int maxValue = sum[0];
    for(int i = 1; i <= N; i++)  
        if(sum[i] > maxValue) maxValue = sum[i];

    cout << maxValue;
    return 0;
}