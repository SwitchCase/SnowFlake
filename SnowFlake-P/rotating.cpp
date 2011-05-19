#include<iostream>
#include<cstdio>
#define N 			if(counter>=sqr)\
				break;\
				in=true;\
				if(mat[si][sj]!=smallest)\
				return 0;\
				if(!(counter%(n-(2*i)-1)))\
				dif=(dif==1?n:1);\
				if(counter && !(counter%((n-(2*i)-1)<<1)))\
				sign*=-1;\
				smallest +=sign*dif;\
				counter++;\

using namespace std;
#define getcx getchar_unlocked

inline void inp( int &n )//fast input function
{
 n=0;
 int ch=getcx();
 while( ch < '0' || ch > '9' ) ch=getcx();

 while( ch >= '0' && ch <= '9' )

n = (n<<3)+(n<<1) + ch-'0', ch=getcx();
}
int n,mat[1005][1005];
int move(int si,int sj,int i,int smallest)
{

		int counter=0,dif=n,sign=1,sqr=(n-2*i)*(n-2*i);
		while(counter<sqr)
		{
//			cout<<"C"<<counter;
			bool in=false;
			for(;si==i && sj<n-i-1;sj++)
			{
				N
			}
			for(;sj ==n-i-1 && si<n-i-1;si++)
			{
				
				N
			}
			for(;si==n-i-1 &&sj>0+i;sj--)
			{	
				
				N
			}
			for(;sj==i && si>i;si--)
			{	
				N
			}
//			cout<<"S"<<si<<" "<<sj;
			if(in==false)	
			return 0;
		}
		return 1;
}
struct index
{
	int i;
	int j;
}smalindx[500005];
int main()
{
	int cas=1,value;
	while(1)
	{
		bool s=true;
		int smallest=1;
		scanf("%d",&n);
		if(!n)
		break;
		int half=(n*n)>>1;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
			{
				//scanf("%d",&mat[i][j]);
				inp(value);
 				mat[i][j]=value;
				if(mat[i][j]<=half+1 && !((mat[i][j]-1)%(n+1)))
				{
//					cout<<"IN"<<i<<" "<<j<<endl;
					smalindx[mat[i][j]].i=i;
					smalindx[mat[i][j]].j=j;
				}	
			}
		half=n>>1;
		for(int i=0;i<half;i++)
		{	
			if(!move(smalindx[smallest].i,smalindx[smallest].j,i,smallest))
			{
				s=false;
				break;
			}
			smallest +=n+1;
		}
		//cout<<"small"<<smallest;
		if((s && n&1 && mat[n>>1][n>>1]!=smallest))	s=false;
		
		if(s)
		printf("%d. YES\n",cas++);
		else
		printf("%d. NO\n",cas++);
	}
}
