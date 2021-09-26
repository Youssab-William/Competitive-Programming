/*
problem : http://usaco.org/index.php?page=viewproblem2&cpid=921
sol: standard HLD
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll OO= 0;
struct SGTR
{
    int sz;
    vector<ll>segment;
    void calcsz(int n)
    {
        segment.clear();
        sz=1;
        while(sz<n)sz*=2;
        segment.assign( (sz*2)+1 , OO);
    }
    ll query(int left , int right , int idx , int l , int r)
    {
        if(right<l||left>r)
            return OO;
        if(left<=l && right>=r)
            return segment[idx];
        int m=(l+r)/2;
        return (query( left , right , idx*2 , l , m ))^(query( left , right , idx*2+1 , m+1 , r ));
    }
    ll query(int left , int right)
    {
        return query( left , right , 1 , 1 , sz);
    }
    void update(int index , int val , int idx , int l , int r)
    {
        if(l==r)
            segment[idx]=val;
        else
        {
            int m = (l+r)/2 ;
            if(index<=m)
                update(index , val , idx*2 , l , m);
            else update(index , val , idx*2 +1 , m+1 , r);
            segment[idx]=(segment[idx*2]^segment[idx*2+1]);
        }
    }
    void update(int index , int val)
    {
        update(index , val , 1 , 1, sz);
    }

};

vector<int> parent, depth, heavy, head, pos;
int cur_pos;

int dfs(int v, vector<vector<int>> const& adj) {
    int sz = 1;
    int max_c_size = 0;
    for (int c : adj[v]) {
        if (c != parent[v]) {
            parent[c] = v, depth[c] = depth[v] + 1;
            int c_size = dfs(c, adj);
            sz += c_size;
            if (c_size > max_c_size)
                max_c_size = c_size, heavy[v] = c;
        }
    }
    return sz;
}
SGTR segtree;
ll arr[100001];
void decompose(int v, int h, vector<vector<int >> const& adj) {
    head[v] = h, pos[v] = cur_pos++;
    segtree.update(pos[v] , arr[v]);
    if (heavy[v] != -1)
        decompose(heavy[v], h, adj);
    for (int c : adj[v]) {
        if (c != parent[v] && c != heavy[v])
            decompose(c, c, adj);
    }
}

void init(vector<vector< int >> const& adj) {
    int n = adj.size();
    parent = vector<int>(n+1);
    depth = vector<int>(n+1);
    heavy = vector<int>(n+1, -1);
    head = vector<int>(n+1);
    pos = vector<int>(n+1);
    cur_pos = 1;

    int tmm = dfs(1, adj);
    segtree.calcsz(n);
    decompose(1, 1, adj);
}
ll query(int a, int b) {
    ll res = 0;
    for (; head[a] != head[b]; b = parent[head[b]]) {
        if (depth[head[a]] > depth[head[b]])
            swap(a, b);
        ll cur_heavy_path_max = segtree.query(pos[head[b]], pos[b]);
        res = (res^cur_heavy_path_max);
    }
    if (depth[a] > depth[b])
        swap(a, b);
    ll last_heavy_path_max = segtree.query(pos[a], pos[b]);
    res = (res^last_heavy_path_max);
    return res;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("cowland.in" , "r" , stdin);
    freopen("cowland.out" , "w" , stdout);
        int num,q;
        cin >> num >> q;
        for(int i =1; i<=num ; i++)
        {
            cin >> arr[i];
        }
        segtree.calcsz(num);
        vector<vector<int> >v(num+1);
        for(int i = 0 ;i < num-1 ; i++)
        {
            //cout << i << "\n";
            int a, b;
            cin >> a >>b;
            v[a].push_back(b);
            v[b].push_back(a);
        }
        init(v);
        while(q--)
        {
            int a, b,c;
            cin >> c>> a >> b;
            if(c==2)cout << query(a,b)<< "\n";
            else
            {
                segtree.update(pos[a], b);
            }
        }
	return 0;
}
