/*
    we can solve this problem greedly by sorting the edges and try to give it to the childs in order 
    we can do this effeciently using dsu 
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1e3+5 , K = 1e4+3;
int n , m , k , a , b, c;
int parent[K][N] , siz[K][N];
int nxt[N][N]={0};
int fnd(int num , int node)
{
    if(parent[num][node]==0)
    {
        return node;
    }
    else return parent[num][node] = fnd(num, parent[num][node]);
}
void uni(int num,int a , int b)
{
    a=fnd(num, a);
    b=fnd(num, b);
    if(a==b)
    {
        return;
    }
    if(siz[num][a]>siz[num][b])
    {
        parent[num][b]=a;
        siz[num][a]=siz[num][b]+siz[num][a];
    }
    else
    {
        parent[num][a]=b;
        siz[num][b]=siz[num][b]+siz[num][a];
    }
    return;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m >> k;
    int ans[m]={0};
    for(int j = 0 ;  j <  K ; j++)
    {
        for(int i = 1 ; i <N ; i++)
        {
            parent[j][i]=0;
            siz[j][i]=1;
        }
    }
    map<pair<int,int> , int>mp;
    vector<pair<pair<int,int> ,pair<int,int> > >s;
    vector<pair<int,int> >edges;
    int x,y, z, l;
    for(int i = 0 ; i < m ; i++)
    {
        cin >> a>> b >> c;
        edges.push_back({a,b});
        pair<pair<int,int> ,pair<int,int> > p = make_pair(make_pair(0-c , i), make_pair(a, b));
        s.push_back(p);
    }
    sort(s.begin() , s.end());
    for(auto p : s)
    {
        x=p.first.first;
        y=p.first.second;
        z=p.second.first;
        l=p.second.second;
        for(int i = nxt[z][l] ;  i < k ; i++)
        {
            a=fnd(i+1 , z );
            b=fnd(i+1 , l );
            if(a!=b)
            {
                uni(i+1, z , l);
                ans[y]=i+1;
                nxt[z][l]=i+1;
                nxt[l][z]=i+1;
                break;

            }
        }
    }
    for(int i = 0 ; i < m ; i++)
    {
        cout <<ans[i] << "\n";
    }
    return 0;
}
