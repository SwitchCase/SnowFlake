#include <iostream>
#include <cstdio>
#include <cassert>
using namespace std;

int Role(int n, int m, int k) 
{ 
	int v=1;
	for (int L=n;L>0;L--)
	{ 
		v=(v+m-2)%L+1; 
		if (v==k) 
			return n+1-L;
		if (v<k)
			k--;
	} 
	return -1; 
}


int main()
{
	int n,m,k;
	int tc;
	scanf("%d",&tc);
	while(tc--)
	{
		scanf("%d %d %d",&n,&m,&k);
		printf("%d\n",Role(n,m,k));
	}
}


