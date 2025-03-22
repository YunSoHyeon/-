#include <iostream>
#include <vector>
#include <numeric>

using namespace std;
int k;
int mp, mf, ms, mv;
int cost = 2147483647;

struct nutrient {
    int p, f, s, v, c; 
};
vector<nutrient> ingredients(51);
vector<int> current; 
vector<int> result; 
int nutrientCur;

void getHealthy(int i, int p, int f, int s, int v, int c){
    if(i == k + 1)
        return;

    if(p >= mp && f >= mf && s >= ms && v >= mv){
        int nutrientSum = p + f + s + v;

        if(c < cost){
            cost = c;
            nutrientCur = nutrientSum;
            result = current;
        }
        else if(c == cost && nutrientSum > nutrientCur){
            nutrientSum = nutrientCur;
            result = current;
        }
        else if(c == cost && nutrientSum == nutrientCur && result > current)
            result = current;

        return;
    }
    
    getHealthy(i + 1, p, f, s, v, c);
    
    current.push_back(i);
    getHealthy(i + 1, p + ingredients[i].p, f + ingredients[i].f, s + ingredients[i].s, v + ingredients[i].v, c + ingredients[i].c);
    current.pop_back();
}

int main(){
    cin >> k;
    cin >> mp >> mf >> ms >> mv;
    
    for(int i = 0; i < k; i++)
        cin >> ingredients[i].p >> ingredients[i].f >> ingredients[i].s >> ingredients[i].v >> ingredients[i].c;
    
    getHealthy(0, 0, 0, 0, 0, 0);

    if(cost == 2147483647)
        cout << 0;
    
    else
        for(int i = 0; i < result.size(); i++)
            cout << result[i] + 1 << " ";
    
    return 0;
}