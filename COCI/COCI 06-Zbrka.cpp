/*
        the easy dp solution : dp[n][c] = dp[n-1][c-i] for all i from 0 to n-1 
        this solution is O(n^2 * c) 
        good optimization is to observe the relation between dp[n][c] and dp[n][c-1]
        dp[n][c] = dp[n][c-1] + dp[n-1][c] - dp[n-1][c-n] 
        which leads to the second optimization that we only need 2 rows of the dp table at a time 
        final time comlexity is O(NC) and the memory complexity O(2*C)
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll ans=0;
ll mm=1000000007;
ll n , c;
ll dp[2][10001];

int main()
{
    cin >> n >> c;
    dp[(1&1)][0]=1;
    dp[(1&1)][1]=0;
    dp[(2&1)][0]=1;
    dp[(2&1)][1]=1;
    for(int i = 3 ; i <=n ; i++)
    {
        for(int j = 0 ; j <= c ; j++)
        {
            if(j==0)
            {
                dp[(i&1)][j]=1;
                continue;
            }
            dp[(i&1)][j]=dp[(i&1)][j-1]%mm +dp[((i-1)&1)][j]%mm;
            dp[(i&1)][j]%=mm;
            if(j>=i){
                    dp[(i&1)][j]= (dp[(i&1)][j]%mm - ((dp[((i-1)&1)][j-i])%mm) + mm )%mm;
                    dp[(i&1)][j]%=mm;
            }

        }
    }
    cout << dp[(n&1)][c] ;
    return 0;

}
