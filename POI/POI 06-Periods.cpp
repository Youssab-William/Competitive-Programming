/*
      this problem can be solved by Z-function algorithm (https://cp-algorithms.com/string/z-function.html)
      let's define z[i] = the length of the longest substring that starts at i and it is also prefix of the string s
      let j = min(z[i+1] , i+1)
      now we know that the prefix s[0...i] is one of the potential answers to the range[i+1 , j]
      to find the optimal potential answer to each index 
      we can iterate from n-1 to 0 
      maintaining a vector where the the indices we did not answer yet are stored
      for each i : the optimal answer for all the indices in the vector that are within the range[i+1 , j] is i+1 
      and then push the index i to the vector
      this way we are sure that the optimal answer each index is calculated 
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
string s;
vector<ll>z;

void z_function() {
    ll n = (ll) s.length();
    z.resize(n);
    for (ll i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    cin >> n >> s;
    z_function();
    vector<ll>v;
    ll ans=0;
    for(ll i = n -1 ; i>= 0 ; i--)
    {
        ll x = min(i+1 , z[i+1])+i ;
        while(!v.empty()&&v.back()<=x)
        {
            ans+=i+1;
            v.pop_back();
        }
        v.push_back(i);
    }
    cout << ans;
    return 0;
}
