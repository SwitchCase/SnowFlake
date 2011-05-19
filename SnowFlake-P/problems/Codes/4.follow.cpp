#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>

#define MAX 100
#define tests(tc) int tc;scanf("%d",&tc);while(tc--)
#define DB(x) cerr<<#x<<" : "<<x<<endl<<flush;


using namespace std;

char mat[MAX][MAX];
int N;

void findPos(char *str)
{
	int len = strlen(str);
	int i = 0, j = 0;
	for (int p = 0; p < len; p += 1) 
	{
		if(str[p] == 'R' && mat[i][j+1] == '.')
			j = min(j+1, N-1);
		else if(str[p] == 'L' && mat[i][j-1] == '.')
			j = max(j-1, 0);
		else if(str[p] == 'U' && mat[i-1][j] == '.')
			i = max(i-1, 0);
		else if(str[p] == 'D' && mat[i+1][j] == '.')
			i = min(i+1, N-1);	
		//cout << i << " " << j << endl;	
	}	
	printf("(%d,%d)\n",i,j);
}

int main() 
{
	char str[1002];
	tests(tc)
	{
		cin >> N;
		for (int i = 0; i < N; i += 1) 
			for (int j = 0; j < N; j += 1) 
				cin >> mat[i][j];		
		cin >> str;
		findPos(str);	
	}	
}
