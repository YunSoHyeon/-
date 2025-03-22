#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

vector<int> preprocessing(string pattern){
    int j = -1;
    vector<int> pre(pattern.size(), 0);
    pre[0] = -1;
    for(int i = 1; i < pattern.size(); i++){
        while(j >= 0 && pattern[i] != pattern[j + 1])
            j = pre[j];
        if(pattern[i] == pattern[j + 1])
            j++;
        pre[i] = j;
    }
    return pre;
}

int KMP(string pattern, string text){
    vector<int> pre = preprocessing(pattern);
    int j = -1;
    int cmp = 0;
    for(int i = 0; i < text.size(); i++){
        while(j >= 0 && text[i] != pattern[j + 1]){
            j = pre[j];
            cmp++;
        }
        cmp++;
        if(text[i] == pattern[j + 1])
            j++;
        if(j == pattern.size() - 1) 
            return cmp;
    }
    return cmp;
}

vector<int> computeSkip(string pattern){
    vector<int> skip(256, -1);
    for(int i = 0; i < pattern.size(); i++)
        skip[pattern[i]] = i;

    return skip;
}

int BM(string pattern, string text){
    vector<int> skip = computeSkip(pattern);
    int i = 0, cmp = 0;
    
    while(i <= text.size() - pattern.size()){
        int j = pattern.size() - 1;
        int k = i + pattern.size() - 1;
        while(j >= 0 && pattern[j] == text[k]){
            j--; k--;
            cmp++;
        }
        if(j == -1) return cmp;
        cmp++;
        i = i + max(1, j - skip[text[i + j]]);
    }
    return cmp;
}

int RK(string pattern, string text){
    int q = 101;
    int d = 2;
    int h = 1;
    int cmp = 0;
    int j;
    
    int textHash = 0, patternHash = 0;
    for(int i = 0; i < pattern.size(); i++){
        textHash = (d * textHash + text[i]) % q;
        patternHash = (d * patternHash + pattern[i]) % q;
    }

    for(int i = 0; i < pattern.size() - 1; i++)
        h = (h * d) % q;
    
    for (int i = 0; i <= text.size() - pattern.size(); i++) {
        cmp++;
        if (textHash == patternHash) {
            bool flag = true;
            for (int j = 0; j < pattern.size(); j++) {
                cmp++;
                if (text[i + j] != pattern[j]) {
                    flag = false;
                    break;
                }
            }
            if (flag) return cmp; // 패턴이 일치하는 경우
        }
        if (i < text.size() - pattern.size()) {
            textHash = (d * (textHash - text[i] * h) + text[i + pattern.size()]) % q;
            if (textHash < 0) textHash += q; // 음수 방지
        }
    }

    return cmp;
}

struct Compare {
    bool operator()(const pair<int, string>& p1, const pair<int, string>& p2) {
        return p1.first > p2.first;
    }
};

int main(void){
    int pCount, tCount;
    string pattern, text;

    cin >> pCount;
    for(int i = 0; i < pCount; i++){
        string tmp;
        cin >> tmp;
        pattern += tmp;
    }
    
    cin >> tCount;
    for(int i = 0; i < tCount; i++){
        string tmp;
        cin >> tmp;
        text += tmp;
    }


    vector<int> setCount(3);
    setCount[0] = KMP(pattern, text);
    setCount[1] = BM(pattern, text);
    setCount[2] = RK(pattern, text);
    
    priority_queue<pair<int, string>, vector<pair<int, string>>, Compare> pq;
    pq.push(make_pair(setCount[0],"KMP")); 
    pq.push(make_pair(setCount[1], "BM")); 
    pq.push(make_pair(setCount[2], "RK"));
    
    set<int> result(setCount.begin(), setCount.end());
    // for(int i = 0; i < 3; i++){
    //     cout << setCount[i] << " ";
    // }
    // cout << endl;
    if(result.size() == 1) 
        cout << "0 0 0" << "\n";
    else if(result.size() == 2){
        int tmp1 = pq.top().first;
        string tmp1Type = pq.top().second;
        pq.pop();
        int tmp2 = pq.top().first;
        pq.pop();

        if(tmp1 == tmp2)    
            cout << "0 0 " << pq.top().second;
        else
            cout << tmp1Type << " 0 0";
    }
    else{
        while (!pq.empty()) {
            cout << pq.top().second << " ";
            pq.pop();
        }
    }



    return 0;
}