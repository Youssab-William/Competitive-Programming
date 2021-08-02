/*
      problem solution :
     https://codeforces.com/blog/entry/17717?#comment-226989
*/

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 30001;
vector<pair<int,int> >v[N];
int b[N] , p[N] ;
vector<pair<int,int> >vp;
int n , m ;
map<pair<int,int> , int>mp;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int x , y;
    cin>> n>> m ;
    for(int i = 0 ; i < m ; i++)
    {
        cin >> b[i] >> p[i];
        if(i==0)x=b[i];
        if(i==1)y=b[i];
        mp[{b[i],p[i]}]++;
        if(mp[{b[i],p[i]}]>1)continue;
        vp.push_back({b[i], p[i]});
    }
    if(x==y)
    {
        cout << 0 ;
        return 0;
    }
    sort(vp.begin(),vp.end());
    m=vp.size();
    for(int i = 0 ; i < m ; i++)
    {
        int c=1;
        for(int j = vp[i].first+vp[i].second ; j< n ; j+= vp[i].second)
        {
            v[vp[i].first].push_back({j , c});
            c++;
            if(mp.find({j,vp[i].second})!=mp.end())
                break;
        }
    }
    for(int i = m-1 ; i >=0 ; i--)
    {
        int c=1;
        for(int j = vp[i].first-vp[i].second ; j>=0 ; j-= vp[i].second)
        {
            v[vp[i].first].push_back({j , c});
            c++;
            if(mp.find({j,vp[i].second})!=mp.end())
                break;
        }
    }
    int dist[N];
    priority_queue<pair<int,int> >q;
    int processed[N]={0};
    for (int i = 0; i <= n; i++) dist[i] = INT_MAX;
    dist[x] = 0;
    q.push({0,x});
    while (!q.empty())
    {
        int a = q.top().second; q.pop();
        if (processed[a]) continue;
        processed[a] = 1;
        for (auto u : v[a])
        {
            int b = u.first, w = u.second;
            if (dist[a]+w < dist[b])
            {
                dist[b] = dist[a]+w;
                q.push({-dist[b],b});
            }
        }
    }
    if(dist[y]==INT_MAX)
        dist[y]=-1;
    cout << dist[y] ;

    return 0;
}
