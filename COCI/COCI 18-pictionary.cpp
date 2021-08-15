/*
        we can loop over the days ( from M to 1 )
        and construct a spanning tree by connecting each number on its turn with its multiples if they are not already connected
        making the cost of the edge = the number of the day
        then for each query 
        we need to go through the path from A and B to their LCA and find the max edge
        we don't need to use binary lifting to solve the problem.
        since we only add edges between number and its multiples ,
        then the depth of the tree is at most logN.
        so we can just go to nodes' parent iteratively until they are in
        the same node and calculate the maximum edge on the path.
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1e5+5;
int n , m , q , a , b;
int parent[N] , siz[N] , vis[N] , dep[N];
int par[N] , edg[N];
vector<pair<int,int> >v[N];
int fnd( int node)
{
    if(parent[node]==0)
    {
        return node;
    }
    else return fnd(parent[node]);
}
int uni(int a , int b)
{
    a=fnd(a);
    b=fnd(b);
    if(a==b)
    {
        return 0;
    }
    if(siz[a]>siz[b])
    {
        parent[b]=a;
        siz[a]=siz[b]+siz[a];
    }
    else
    {
        parent[a]=b;
        siz[b]=siz[b]+siz[a];
    }
    return 1;
}
void dfs(int node , int p)
{
    for(auto u: v[node])
    {
        if(u.first!=p)
        {
            par[u.first]=node;
            edg[u.first]=u.second;
            dep[u.first]=dep[node]+1;
            dfs(u.first , node);
        }
    }
    return;
}
int main()
{
    cin >> n >> m >> q;
    for(int i = 1 ; i <N ; i++)
    {
        parent[i]=0;
        siz[i]=1;
    }
    for(int i = m ; i>0 ; i--)
    {
        for(int j = i+i ; j<=n ; j+=i)
        {
            if(uni(i , j))
            {
                v[i].push_back({j , m-i+1});
                v[j].push_back({i , m-i+1});
            }
        }
    }
    par[1]=0;
    dep[1]=0;
    dfs(1 , 0);
    while(q--)
    {
        cin >> a >> b ;
        int ans=0;
        while(a!=b)
        {
            if(dep[a]>=dep[b])
            {

                ans=max(ans , edg[a]);
                a=par[a];
            }
            else
            {

                ans=max(ans , edg[b]);
                b=par[b];
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
