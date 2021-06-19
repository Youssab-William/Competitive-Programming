/*
          we are going to save the pervious orders in priority queue 
          when we reach to order we cannot afford it dosn't matter which one we can't afford 
          so we check the largest order we placed before if it is greater than the current order 
          we will replace it with the current order and keep the difference so that we can increase 
          the value of what we have so we can take more orders
*/

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
int main()
{
    ll n ,x ;
    cin >> n ;
    priority_queue<pair<ll,ll> >pq;
    ll have=0;
    ll arr[n];
    for(int i = 0 ; i < n ; i++)
    {
        cin >> arr[i];
    }
    for(ll i = 0 ; i < n ; i++)
    {
        cin >> x;
        have+=arr[i];
        if(have>=x)
        {
            pq.push({x,i+1});
            have-=x;
            continue;
        }
        else
        {
            if(pq.empty()||pq.top().first<=x)
                continue;
            else
            {
                have+=(pq.top().first-x);
                pq.pop();
                pq.push({x,i+1});
            }
        }
    }
    cout << pq.size() << "\n";
    set<ll>s;
    while(!pq.empty())
    {
        s.insert(pq.top().second);
        pq.pop();
    }
    for(int u : s)
    {
        cout << u << " ";
    }
    return 0;
}
