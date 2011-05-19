#include<cmath>
#include<cstdio>

using namespace std;

#define tests(tc) int tc;scanf("%d",&tc);while(tc--)

void printFactors(int num)
{
	int i;
	for ( i = 2; i*i <= num; i++ ) 
	{	
		while(num>i && num%i==0)
		{
			printf("%d*",i);
			num /= i; 
		}
		if(num==i)
		{
			printf("%d\n",i);
			num /= i;
			break;
		}
	}
	if(num!=1)
		printf("%d\n",num);	
}


int main()
{
	int num;
		
	tests(tc) 
	{
		scanf("%d",&num);

		printFactors(num);
	}	
	
	return 0;
}
