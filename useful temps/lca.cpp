#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
int n, l;
vector<int> adj[100005];

int timer;
vector<int> tin, tout;
vector<vector<int>> up;

void dfs(int v, int p)
{
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];

    for (int u : adj[v]) {
        if (u != p)
            dfs(u, v);
    }

    tout[v] = ++timer;
    return;
}

bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

void preprocess(int root) {
    tin.resize(n+1);
    tout.resize(n+1);
    timer = 0;
    l = ceil(log2(n+1));
    up.assign(n+1, vector<int>(l + 1));
    dfs(root, root);
}
int main()
{
    cin >> n ;
    int x , y;
    for(int i  = 0 ;  i < n -1 ; i++)
    {
        cin >>x>>y ;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    preprocess(1);
    int q ;
    cin >> q ;
    while(q--)
    {
        cin >>x  >> y ;
        cout << lca(x ,y) << "\n";
    }
    return 0;
}
