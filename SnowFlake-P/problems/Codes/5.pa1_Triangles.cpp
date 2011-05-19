#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int MODULO = 1000000009;
int C[25][25];
int res[1000007];


int Count(int baseLength, int top)
{
	if (baseLength > 25)
		return 0;
	top -= 1 << (baseLength - 1);
	if (top < 0)
		return 0;

	memset(res,0,sizeof res);
	res[0] = 1;
	for (int i = 0; i < baseLength; ++i)
	{
		int cur = C[baseLength - 1][i];
		for (int j = 0; j + cur <= top; ++j)
		{
		    res[j + cur] += res[j];
		    if (res[j + cur] >= MODULO)
		        res[j + cur] -= MODULO;
		}
	}
	return res[top];
}

void preprocess()
{
	C[0][0] = 1;
	for (int i = 1; i < 25; ++i)
	{
		C[i][0] = 1;
		for (int j = 1; j < 25; ++j)
		    C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
	}
}

int main()
{
	preprocess();
	
	int tc;
	scanf("%d",&tc);
	while(tc--)
	{
		int n,r;
		scanf("%d %d",&n,&r);
		printf("%d\n",Count(n,r));
	}
}



