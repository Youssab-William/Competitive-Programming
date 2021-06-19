/*
        store the indices of occurence of each digit in each number
        try all the combinations of four-digit password   (10^4 combinations)
        we can check each password if it's valid or not be looping over all 
        the given number and binary search about the first occurence of the digit on turn
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
vector<int>v[1001][15];
int n , x;
bool solve( vector<int> ch)
{
    int one=ch[0] , two=ch[1] , three= ch[2] , four=ch[3] , idx1 , idx2 , idx3 , idx4;
    for(int i = 0 ; i  < n ; i++)
    {
        if(v[i][one].empty())return false;
        auto it= lower_bound(v[i][one].begin() , v[i][one].end() , 0);
        idx1= *it;
        if(it==v[i][one].end())return false;
        if(v[i][two].empty())return false;
        it = lower_bound( v[i][two].begin() ,v[i][two].end()  , idx1);
        idx2= *it;
        if(it==v[i][two].end())return false;
        if(v[i][three].empty())return false;
        it = lower_bound( v[i][three].begin() ,v[i][three].end()  , idx2);
        idx3= *it;
        if(it==v[i][three].end())return false;
        if(v[i][four].empty())return false;
        it = lower_bound( v[i][four].begin() ,v[i][four].end()  , idx3);
        idx4= *it;
        if(it==v[i][four].end())return false;
     }
    return true;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n ;
    string s;
    for(int i = 0 ;  i< n ; i++)
    {
        cin >> x ;
        cin >> s ;
        for(int j = 0 ; j < x ; j++)
        {
            v[i][int(s[j]-'0')].push_back(j);
        }
    }

    vector<int>check;
    int ans=0;
    for(int i = 0 ; i < 10 ; i++)
    {
        for(int j = 0 ; j < 10 ; j++)
        {
            for(int k = 0 ; k < 10 ; k++)
            {
                for(int l = 0 ; l < 10 ; l++)
                {
                    check.push_back(i);
                    check.push_back(j);
                    check.push_back(k);
                    check.push_back(l);
                    if(solve(check))
                    {
                        ans++;
                    }
                    check.clear();
                }
            }
        }
    }
    cout << ans;
    return 0;
}
