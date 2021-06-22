/*
          check over the bridges and remove them from the graph
          compress each connected component into one node
          add the bridges again
          now you the new graph is a tree 
          connecting each two nodes by at least two paths on a tree 
          is a well known problem that can be solved by adding (x+1)/2 edges where x is the number of the leaves on the tree
*/

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1001;
int parent[N] , siz[N];
int vis[N];
vector<int>v[N];
vector<int>newgraph[N];
vector<pair<int,int> >bridges;
int n , m , x , y ;
int leaves;
void dfs(int node , int par)
{
    if(newgraph[node].size()==1)
    {
        leaves++;
        return;
    }
    for(int u : newgraph[node])
    {
        if(u!=par)
            dfs(u , node);
    }
}
int fnd( int node)
{
    if(parent[node]==0)
    {
        return node;
    }
    return fnd(parent[node]);
}
void uni(int a , int b)
{
    a=fnd(a);
    b=fnd(b);
    if(a==b)
    {
        return;
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
    return ;
}
int main()
{
    cin >> n >> m ;
    vector<pair<int,int> >edges;
    for(int i = 0 ; i < m ; i++)
    {
        cin >> x >> y ;
        if(x>y)swap(x,y);
        v[x].push_back(y);
        v[y].push_back(x);
        edges.push_back({x,y});
    }
    map<int, int>ind;
    for(int i = 0 ; i  < m ; i++)
    {
        for(int j = 1 ; j<=1000 ; j++)
        {
            parent[j]=0;
            siz[j]=1;
        }
        for(int  j = 0 ; j < m ; j++)
        {
            if(i==j)continue;
            x=edges[j].first;
            y=edges[j].second;
            uni(x , y);
        }
        if(siz[fnd(1)]!=n)
        {
            bridges.push_back(edges[i]);
            ind[i]++;
        }
    }
    for(int j = 1 ; j<=1000 ; j++)
        {
            parent[j]=0;
            siz[j]=1;
        }
    for(int i = 0 ; i  < m ; i++)
    {
        if(ind[i])continue;
        uni(edges[i].first , edges[i].second);
    }
    int sz=bridges.size();
    for(int i = 0 ; i < sz ; i++)
    {
        x=fnd(bridges[i].first);
        y=fnd(bridges[i].second);
        newgraph[x].push_back(y);
        newgraph[y].push_back(x);
    }
    dfs(fnd(1) , 0);
    cout << (leaves+1)/2 ;
    return 0;
}
