/*
        binary search on the smallest median X
        check every X by using 2d prefix sum array to know the number of elements <= X in any submatrix let that number = num
        if(num<=H*W-num) in any of the submatrices of size H*W then we can try smaller X if not try larger X 
*/
#include <bits/stdc++.h>
#include "quality.h"
using namespace std;
int rectangle(int R, int C, int H, int W, int Q[3001][3001]) {
	int l=1 , r= 3000*3000 , m , ans=r ;
	int arr[R+1][C+1]={0};
	int x;
	bool flag;
	while(l<=r)
    {
        m=(l+r)>>1;
        memset(arr , 0 , sizeof arr);
        for(int i = 0 ; i  < R ;  i++)
        {
            for(int j = 0 ; j < C ;j++)
            {
                if(Q[i][j]<=m)
                {
                    arr[i+1][j+1]=1;
                }
            }
        }
        for(int i = 1 ; i <= R ; i++)
        {
            for(int j = 1 ; j <=C ; j++)
            {
                arr[i][j]+= arr[i-1][j] + arr[i][j-1] - arr[i-1][j-1];
            }
        }
        flag=false;
        for(int i = H ; i <=R ; i++)
        {
            for(int j = W ; j<=C ; j++)
            {
                x=arr[i][j]+arr[i-H][j-W]-arr[i-H][j]-arr[i][j-W];
                if(x>=(H*W)-x)
                {
                    flag=true;
                    break;
                }
            }
            if(flag)
                break;
        }
        if(flag)
        {
            ans=m;
            r=m-1;
        }
        else
        {
            l=m+1;
        }
    }
    return ans;

}
