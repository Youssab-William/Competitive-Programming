/*
        bruteforce over the potential X's 
        good observation : x will be  = the maximum number in the set - one of the last n+1 nuber after sorting 
        try them by removing v[i] and v[i]+X if we could remove N pairs we found a solution
*/
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >>n;
    vector<int>v;
    int x;
    for(int i = 0 ; i< 2*n ; i++)
    {
        cin >> x ;
        v.push_back(x);
    }
    sort(v.begin() , v.end());
    x = v[2*n-1];
    map<int,int>mp;
    int y;
    int sz;
    vector<int>ans;
    for(int i = n-1 ; i <2*n ; i++)
    {
        y=x-v[i];
        if(y==0)continue;
        mp.clear();
        ans.clear();
        for(int j = 0 ; j < 2*n  ; j++)
        {
            mp[v[j]]++;
        }
        int flag=1;
        for(int j = 0 ; j < n*2 ; j++)
        {
            if(mp[v[j]]==0)continue;
            if(!mp[v[j]+y])
            {
                flag=0;
                break;
            }
            mp[v[j]]--;
            mp[v[j]+y]--;
            ans.push_back(v[j]+y);
        }
        if(!flag)continue;
        if(flag)
        {
            cout << y << "\n";
            for(int j = 0 ; j < n ; j++)
            {
                cout << ans[j] << " ";
            }
            return 0;
        }
    }
    cout << -1;
    return 0;
}
