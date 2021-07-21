/*
    the cost will not change for any valid distrubution for the extraction points among the distribution stations
    with this observation the problem became to just find any possible distrubution
    we can do this using sweep line techinque to find such distribution 
    by sweeping over the X axis connecting each distribution station with the first extraction point above it 
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
int a , b;
int n ;
int main()
{
    cin >> n;
    vector<pair<int,pair<int,int> > >line;
    ll cost =0 ;
    set<pair<int,int> >s;
    set<pair<int,int> >::iterator it;
    for(int i = 1 ;i  <=n ; i++)
    {
        cin >> a >> b ;
        line.push_back({a , {0-i , b} });
        cost+=(b-a);
    }
    for(int i = 1 ; i <=n ; i++)
    {
        cin >> a >> b ;
        line.push_back({a , {i , b} });
        cost+=(a-b);
    }
    sort(line.begin() , line.end());
    vector<pair<int,int> >ans;
    for(int i = 0 ; i < 2*n ; i++)
    {
        if(line[i].second.first<0)
        {
            s.insert({line[i].second.second , 0-line[i].second.first });
        }
        else
        {
            it=s.lower_bound({line[i].second.second, 0});
            pair<int,int> p = *it;
            ans.push_back({p.second,line[i].second.first});
            s.erase(it);
        }
    }
    cout << cost << "\n";
    for(int i = 0 ; i <  ans.size() ; i++)
    {
        cout << ans[i].first << " " << ans[i].second << "\n";
    }
    return 0;
}
