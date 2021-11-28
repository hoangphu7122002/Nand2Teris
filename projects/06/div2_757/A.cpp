#include <bits/stdc++.h>

using namespace std;

int max_chocolate(vector <int> vec,int l,int r,int k){
    int count = 0;
    int sum = 0;
    sort(vec.begin(),vec.end());
    for (auto v : vec){
        if (v < l){
            continue;
        }
        if (v > r){
            break;
        }
        count += 1;
        sum += v;
        if (sum > k){
            count -= 1;
            break;
        }        
    }
    return count;
}

int main(){
    int t;
    cin >> t;
    
    vector <int> res;
    while(t--){
        int n,l,r,k;
        cin >> n >> l >> r >> k;
        vector <int> vec;
        int temp;
        for (int i = 0; i  < n; ++i){
            cin >> temp;
            vec.push_back(temp);
        }
        res.push_back(max_chocolate(vec,l,r,k));
    }
    for (int i = 0; i < res.size(); ++i){
        cout << res[i];
        if (i != res.size() - 1){
            cout << endl;
        }
    }
    
    
    return 0;
}