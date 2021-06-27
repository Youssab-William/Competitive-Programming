/*
    sort the pairs according to the the start points 
    count the used layers that the current conductor can pass on by finding the max layer used for any enpoint with index more than the current endpoint using segment tree
    let's say the max layer used is M then we can connect the current conductor in layer M+1 at least
    maximizing that value with ans we can know the minimal number of layers needed to accommodate all the conductors 
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
ll OO=-1;
struct SGTR
{
    int sz=1;
    vector<ll>segment;
    void calcsz(int n)
    {
        while(sz<n)sz*=2;
        segment.assign( (sz*2)+1 , OO);
    }
    void build( vector<ll>&ar  , int idx , int l , int r)
    {
        if(l==r)
           {
               if(l<(int)ar.size())
                 segment[idx]=ar[l];
           }
        else
        {
            int m= (l+r)/2 ;
            build( ar , idx*2 , l , m );
            build( ar , idx*2 +1 , m+1 , r );
            segment[idx]=max(segment[idx*2],segment[idx*2+1]);
        }
    }
    void build( vector<ll>&ar)
    {
        build(ar , 1 , 1 , sz);
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
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    SGTR segtree;
    int n , m , x;
    cin >> n ;
    vector<ll>arr(1000002 , 0);
    segtree.calcsz(1000002);
    segtree.build(arr);
    vector<pair<int,int> >vp;
    int nums[n];
    for(int i = 0 ; i < n ; i++)
    {
        cin >>nums[i]>>x;
        vp.push_back({nums[i], x});
    }
    sort(vp.begin(),vp.end());
    int ans=0;
    for(auto u : vp)
    {
        x = u.second;
        m = segtree.query(x+1 , 1000002);
        segtree.update(x , m+1);
        ans=max(ans , m+1);
    }
    cout << ans ;
    return 0;
}
