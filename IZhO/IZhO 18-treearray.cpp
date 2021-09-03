/*

observation: the answer of the second type of queries will always be segment of length two or one 
so we can build 2nd array saving the LCA of each two consecutive nodes in the array 
while answering each query check if the node v exists in the array within the given interval if yes the answer is l = r = the index of the node v
if not check if any two node exists within the given interval with LCA == v if yes we found answer 
if not print -1 -1 

processing the query type one will be just updading the value of the first original array then recalculate the LCA with the previous and next element again   

we can calculate the LCAs with binary lifting 
we can use sets to save the occurences of some answers to check easily in logN if we have occurence within the given interval (using lower bound)

*/

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
int n, m , q ,l;
vector<int> adj[200005] ;
set<int>ansone[200005] , anstwo[200005];
int arr[200005];
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
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >>m >> q ;
    int x , y ,z, que , val , idx;
    for(int i  = 0 ;  i < n -1 ; i++)
    {
        cin >>x>>y ;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    preprocess(1);
    vector<int>vv;
    for(int i = 0 ; i < m ;i++)
    {
        cin >> arr[i];
        ansone[arr[i]].insert(i);
        if(i==0)continue;
        vv.push_back(lca(arr[i] , arr[i-1]));
    }
    for(int i = 0; i < m-1 ; i++)
    {
        anstwo[vv[i]].insert(i);
    }
    while(q--)
    {
        cin >> que;
        if(que==1)
        {
            cin >> x >> y ;
            x--;
            val=arr[x];
            ansone[val].erase(ansone[val].lower_bound(x));
            arr[x]=y;
            ansone[y].insert(x);
            if(x<m-1)
            {
                val=vv[x];
                anstwo[val].erase(anstwo[val].lower_bound(x));
                vv[x]=lca(arr[x] , arr[x+1]);
                anstwo[vv[x]].insert(x);
            }
            if(x>0)
            {
                val=vv[x-1];
                anstwo[val].erase(anstwo[val].lower_bound(x-1));
                vv[x-1]=lca(arr[x-1] , arr[x]);
                anstwo[vv[x-1]].insert(x-1);
            }
        }
        else
        {
            cin >>x >>y>>z;
            if(ansone[z].lower_bound(x-1)!=ansone[z].end())
            {
                idx=*ansone[z].lower_bound(x-1);
                if(idx<y)
                {
                    cout << idx+1 << " " << idx+1 << "\n";
                    continue;
                }
            }
            if(anstwo[z].lower_bound(x-1)!=anstwo[z].end())
            {
                idx=*anstwo[z].lower_bound(x-1);
                if(idx<y-1)
                {
                    cout << idx+1<< " " <<idx+2<< "\n";
                    continue;
                }
            }
            cout << "-1 -1\n";
        }
    }
    return 0;
}
