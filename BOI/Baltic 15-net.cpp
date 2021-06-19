/*
        This problem can be solved with optimal number of operation by connecting the tree leaves with each other
        using the fact that we can always pick a node which can contain half the number of the leaves in its subtree,
        we can solve the problem by connecting the i-th leaf with the (i+x/2)th leaf where x = number of leaves
*/

#include <bits/stdc++.h>
 
using namespace std;
typedef long long ll;
vector<int>v[500001] , leafs;
 
void dfs(int node , int p )
{
    if(v[node].size()==1)
    {
        leafs.push_back(node);
    }
    for(int u : v[node])
    {
        if(u!=p)
        {
            dfs(u , node);
        }
    }
    return;
}
int main()
{
    int n  , x, y ;
    cin >>n  ;
    for(int i =  0 ; i < n-1; i++)
    {
        cin >> x >>y  ;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    dfs(1 , -1);
    int sz= leafs.size();
 
    if(sz&1)
    {
        cout << sz/2 +1 << "\n";
 
    }
    else cout << sz/2 << "\n";
    for(int i = 0 ; i < (sz/2) ; i++)
    {
        cout << leafs[i] << " " << leafs[i+((sz+1)/2)] << "\n";
    }
    if(sz&1)
    {
        cout << leafs[sz/2] << " " <<1 << "\n";
    }
    return 0;
}
