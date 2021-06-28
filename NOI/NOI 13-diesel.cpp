/*
        dp[x][y] = maximum fuel I can have reaching the cell (x,y)
        the first row in the dp has only one way to fill it which is from left to right
        then for each row from second to last you can update dp[i][j] from the above cell 
        and then try updating the row with paths from left to right and from right left  
        maximizing each path with dp[i][j]
        ans = dp[n-1][m-1] 
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1e3+3;
int arr[N][N] , dp[N][N];
int n , m ;
int main()
{
    cin >> n >> m ;
    for(int i = 0 ; i  < n ; i++)
    {
        for(int j =  0 ; j < m ;j++)
        {
            cin >> arr[i][j];
            arr[i][j]/=100;
        }
    }
    memset(dp , -1 , sizeof dp);
    dp[0][0]=25000;
    int x;
    for(int i = 1 ; i < m ; i++)
    {
        x=10;
        if(arr[0][i]>arr[0][i-1])
        {
            x+= (4 * (arr[0][i]-arr[0][i-1]) * ((dp[0][i-1]+8000)/1000) );
        }
        dp[0][i]=max(dp[0][i-1]-x , dp[0][i]);
    }
    for(int i=1 ; i< n ; i++)
    {
        for(int j = 0 ; j < m ; j++)
        {
            x=10;
            if(arr[i][j]>arr[i-1][j])
            {
                x+= (4 * (arr[i][j]-arr[i-1][j]) * ((dp[i-1][j]+8000)/1000) );
            }
            dp[i][j]=max(dp[i-1][j]-x, dp[i][j]);
        }
        for(int j = 1 ; j < m ; j++)
        {
            x=10;
            if(arr[i][j]>arr[i][j-1])
            {
                x+= (4 * (arr[i][j]-arr[i][j-1]) * ((dp[i][j-1]+8000)/1000) );
            }
            dp[i][j]=max(dp[i][j-1]-x,dp[i][j]);
        }
        for(int j = m-2 ; j >=0 ; j--)
        {
            x=10;
            if(arr[i][j]>arr[i][j+1])
            {
                x+= (4 * (arr[i][j]-arr[i][j+1]) * ((dp[i][j+1]+8000)/1000) );
            }
            dp[i][j]=max(dp[i][j+1]-x,dp[i][j]);
        }
    }
    cout << dp[n-1][m-1] ;
    return 0;
}
