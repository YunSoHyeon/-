#include <iostream>
using namespace std;

bool check(string str){
    for(int i = 0; i < str.size() / 2; i++){
        if(str[i] != str[str.size() - (i + 1)]) {
            return false;
        }
    }
    return true;
}


int subPalin(string sub){
    bool flag1 = false; bool flag2 = false;
    int res1, res2;
    int chk1 = 0; int chk2 = 0;
    int left = 0; int right = sub.size() - 1;
    for(int i = 0; i < sub.size(); i++){
        if(left == right){
            break;
        }
        else if(sub[left] == sub[right]){
            left++;
            right--;
        }
        else{
            left++;
            if(check(sub.substr(left, right - left + 1))){
                chk1++;
            }
            else{
                res1 = sub.size()- 1;
                flag1 = true;
                break;
            }
        }
    }
    // cout << "reust1 " << res1 << endl;
    // cout << "ch1 " << chk1 << endl;
    left = 0; right = sub.size() - 1;
    for(int i = 0; i < sub.size(); i++){
        if(left == right){
            break;
        }
        else if(sub[left] == sub[right]){
            left++;
            right--;
        }
        else{
            right--;
            if(check(sub.substr(left, right - left + 1))){
                chk2++;
            }
            else{
                res2 = sub.size()- 1;
                flag2 = true;
                break;
            }
        }
    }
    if(flag1 && flag2) return res1;
    // cout << "res2 " << res2 << endl;
    // cout << "ch2 " << chk2 << endl;
    return max(chk1, chk2);
    // return min(result1, result2);
}
int isPalindrom(string str){
    if(str[0] != str[str.size() - 1]) return 0;
    
    else if(check(str)) return str.size();

    int result = str.size();
    for(int i = 0; i < str.size(); i++){
        if(str[i] != str[str.size() - (i + 1)]){
            result = str.size() - subPalin(str.substr(i, str.size()-(i + 1) - i + 1));
            break;
        }
    }
    return result;
}
int main(void){
    int n;
    cin >> n;

    for(int i = 0; i < n; i++){
        string str;
        cin >> str;
        cout << isPalindrom(str) << "\n";
    }

    return 0;
}