//  https://www.spoj.com/problems/QTREE/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll OO= -1;
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
        return max(query( left , right , idx*2 , l , m ),query( left , right , idx*2+1 , m+1 , r ));
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
            segment[idx]=max(segment[idx*2],segment[idx*2+1]);
        }
    }
    void update(int index , int val)
    {
        update(index , val , 1 , 1, sz);
    }

};

vector<int> parent, depth, heavy, head, pos, edgy;
int cur_pos;

int dfs(int v, vector<vector<pair<int,int> >> const& adj) {
    int sz = 1;
    int max_c_size = 0;
    if(v==1)edgy[v]=-1;
    for (auto cc : adj[v]) {
            int c=cc.first,c2=cc.second;
        if (c != parent[v]) {
            parent[c] = v, depth[c] = depth[v] + 1;
            edgy[c]=c2;
            int c_size = dfs(c, adj);
            sz += c_size;
            if (c_size > max_c_size)
                max_c_size = c_size, heavy[v] = c;
        }
    }
    return sz;
}
SGTR segtree;
void decompose(int v, int h, vector<vector<pair<int,int> >> const& adj) {
    head[v] = h, pos[v] = cur_pos++;
    segtree.update(pos[v] , edgy[v]);
    if (heavy[v] != -1)
        decompose(heavy[v], h, adj);
    for (auto cc : adj[v]) {
            int c=cc.first;
        if (c != parent[v] && c != heavy[v])
            decompose(c, c, adj);
    }
}

void init(vector<vector< pair<int,int> >> const& adj) {
    int n = adj.size();
    parent = vector<int>(n+1);
    depth = vector<int>(n+1);
    heavy = vector<int>(n+1, -1);
    head = vector<int>(n+1);
    pos = vector<int>(n+1);
    edgy = vector<int>(n+1);
    cur_pos = 1;

    int tmm = dfs(1, adj);
    segtree.calcsz(n);
    decompose(1, 1, adj);
}
int query(int a, int b) {
    int res = -1;
    for (; head[a] != head[b]; b = parent[head[b]]) {
        if (depth[head[a]] > depth[head[b]])
            swap(a, b);
        int cur_heavy_path_max = segtree.query(pos[head[b]], pos[b]);
        res = max(res, cur_heavy_path_max);
    }
    if (depth[a] > depth[b])
        swap(a, b);
    int last_heavy_path_max = segtree.query(pos[a]+1, pos[b]);
    res = max(res, last_heavy_path_max);
    return res;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	int t;
	cin >>t;
	while(t--)
    {
        int num;
        cin >> num ;
        segtree.calcsz(num);
        //cout <<"took\n";
        vector<vector<pair<int,int> > >v(num+1);
        vector<pair<int,int> >ee;
        for(int i = 0 ;i < num-1 ; i++)
        {
            //cout << i << "\n";
            int a, b,c;
            cin >> a >>b>>c;
            ee.push_back({a,b});
            v[a].push_back({b,c});
            v[b].push_back({a,c});
        }
        init(v);
        int q;
        string s;
        while(cin>>s&&s!="DONE")
        {
            int a, b;
            cin >> a >> b;
            if(s[0]=='Q')cout << query(a,b)<< "\n";
            else
            {
                int x=ee[a-1].first , y=ee[a-1].second;
                if(depth[x]<depth[y])
                    swap(x,y);
                segtree.update(pos[x], b);
            }
        }
    }
	return 0;
}
