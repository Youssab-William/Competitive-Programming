#include <bits/stdc++.h>
 
using namespace std;
typedef long long ll;
int arr[5001];
vector<int>v[5001];
ll visited;
ll BFS(int source)
{
    queue<int>q;
    q.push(source);
    arr[source]++;
    ll node , sz , salary=1 , ret=0;
    while(!q.empty())
    {
        sz=q.size();
        while(sz--)
        {
            ret+=salary;
            node=q.front();
            q.pop();
            visited++;
            for(int i = 0 ; i  < v[node].size() ; i++ )
            {
                if(arr[v[node][i]]==0)
                {
                    q.push(v[node][i]);
                    arr[v[node][i]]++;
                }
            }
        }
        salary++;
    }
    return ret;
}
int main()
{
    int n ;
    cin >> n ;
    for(int i = 1 ; i <=n ; i++)
    {
        int x , y;
        cin >> x ;
        while(x--)
        {
            cin >> y;
            v[y].push_back(i);
        }
    }
    ll ans = INT_MAX , found ;
    for(int i = 1 ; i <= n ; i++)
    {
        memset(arr , 0 , sizeof arr);
        visited=0;
        found=BFS(i);
        if(visited==n)
            ans=min(ans , found);
    }
    cout << ans ;
}
