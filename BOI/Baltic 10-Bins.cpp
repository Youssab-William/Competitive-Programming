/*
        brute force on K from the greatest K to the smallest
        check every K by frequency arrays in O(M)
*/
#include <bits/stdc++.h>
 
using namespace std;
typedef long long ll;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll m , n ;
    cin >>m >> n ;
    int a[n];
    for(int i = 0 ; i < n ; i++ )
    {
        cin >> a[i];
    }
    set<ll>s1 , s2;
    ll l[1002]={0} , r[1002]={0} , d[1002]={0};
    int k = n/2 ;
    for(int i = 0 ; i < k ; i++)
    {
        l[a[i]]++;
    }
    for(int i = k ; i < 2*k ; i++)
    {
        r[a[i]]++;
    }
    bool can;
    for(int i = k ; i>=0 ;i--)
    {
        can=true;
        for(int j = m ; j>0 ; j--)
        {
            d[j]=r[j+1]+d[j+1]-l[j];
            if(d[j]<0)
            {
                can=false;
                break;
            }
        }
        if(can)
        {
            cout << i;
            return 0;
        }
        l[a[i-1]]--;
        r[a[i-1]]++;
        r[a[2*i-1]]--;
        r[a[2*i-2]]--;
    }
}
