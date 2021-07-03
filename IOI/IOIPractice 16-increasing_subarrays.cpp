/*
    observation : if we the interval [L,R] can be a good interval with <= M operations 
    so any interval starts from L and ends at i (somewhere between L and R) can be also good interval with <= M operations
    using the observation we can use 2 pointers method 
    increasing R as far as we can add v[R+1] to the current interval
    we can precalculate arr where arr[i] = the index of the next greater number than v[i] 
    insted of bruteforce when moving the left pointer to calculate the new cost we can use the precalculated array and jump from each num to the next greater num 
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {

	ll n, m ,x;
	vector<ll>v , ad , prfx , tmp;
	cin >> n >> m;
	ll arr[n+1];
	memset( arr , -1 , sizeof arr);
	prfx.push_back(0);
	for(int i = 0  ; i < n ; i++)
    {
        cin >> x;
        v.push_back(x);
        tmp.push_back(x);
        prfx.push_back(x+prfx[i]);
    }
    stack<ll>st;
    for(int i = 0  ; i < n ; i++)
    {
        while(!st.empty()&&v[i]>v[st.top()])
        {
            arr[st.top()]=i;
            st.pop();
        }
        st.push(i);
    }
    for(int i = 0  ; i < n ; i++)
    {
        if(arr[i]==-1)
            arr[i]=n;
    }
    ll l =0, r=1 , ans=0;
    ad.push_back(0);
    while(r<n)
    {
        if(v[r]+m>=v[r-1])
        {
            m-=max(0ll , v[r-1]-v[r]);
            v[r]+=max(0ll , v[r-1]-v[r]);
            r++;
        }
        else
        {
            ans+=(r-l);
            int j = l+1;
            if(j==r)
            {
                r++;
                l++;
                continue;
            }
            if(tmp[j]>=tmp[l])
            {
                l++;
                continue;
            }
            ll x1=l , y1=min(arr[l]-1 , r-1)  , x2=l+1 , y2 = min(arr[x2]-1,r-1);
            m+=(tmp[x1]*(y1-x1+1))-(prfx[y1+1]-prfx[x1]);
            while(true)
            {
                if(y2==y1)
                {
                    m-=((tmp[x2]*(y2-x2+1))-(prfx[y2+1]-prfx[x2]));
                    v[y2]=tmp[x2];
                    x2=y2+1;
                    break;
                }
                m-=((tmp[x2]*(y2-x2+1))-(prfx[y2+1]-prfx[x2]));
                v[y2]=tmp[x2];
                x2=y2+1;
                y2=min(arr[x2]-1,r-1);

            }
            l++;

        }

    }
    ans+=((r-l)*(r-l+1)/2);
    cout << ans;
	return 0;
}
