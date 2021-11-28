#include <bits/stdc++.h>

using namespace std;

#define pii pair<long long,long long>

bool cmp(const pii& a,const pii& b){
    if (a.second > b.second){
        return true;
    }
    return false;
}

vector <long long> sum_p;

vector <long long> position(vector <long long> arr){
    map <long long,long long> mp;
    long long t = 0;
    for (auto v : arr){
        mp[t] = v; 
        t++;
    } 
    vector <pii> vec(mp.begin(),mp.end());
    sort(vec.begin(),vec.end(),cmp);
    vector <long long> res;
    res.push_back(0);
    bool flag = true;
    long long init = 1;
    for (int i = 0; i < vec.size(); ++i){
        if (flag == true){
            flag = false;
            mp[vec[i].first] = init;
        }
        else {
            flag = true;
            mp[vec[i].first] = -init;
            init++;
        }
    }
    long long sum = 0;
    for (int i = 0; i < arr.size(); ++i){
        res.push_back(mp[i]);
        sum += 2 * abs(mp[i]) * arr[i];
    }
    sum_p.push_back(sum);
    return res;
}

int main(){
    long long t;
    cin >> t;
    vector <vector<long long>> res;
    while (t--){
        long long n;
        cin >> n;
        vector <long long> arr;
        long long temp;
        for (long long i = 0; i < n; ++i){
            cin >> temp;
            arr.push_back(temp);
        }
        res.push_back(position(arr));
    }
    for (int i = 0; i < res.size(); ++i){
        cout << sum_p[i] << endl;
        for (int j = 0; j < res[i].size(); ++j){
            cout << res[i][j];
            if (j != res[i].size() - 1){
                cout << " ";
            }
        }
        if (i != res.size() - 1){
            cout << endl;
        }
    }
    return 0;
}