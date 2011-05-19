#include<algorithm>
#include<vector>
#include<cstdio>
using namespace std;

char str[250007];
int L,B,E,D;

int coord;
struct Point
{
	int p[2],idx;
};
bool cmp( Point p1, Point p2 )	
{ 
	return p1.p[coord]<p2.p[coord] || (p1.p[coord]==p2.p[coord] && p1.p[1-coord]<p2.p[1-coord]) ;
}
bool cmp1( Point p1, Point p2 )	
{ 
	return p1.idx<p2.idx;
}

Point points[250007];
int pcnt;

void go(int n , int turn)
{
	coord=turn;
	sort(points , points + n+1 ,cmp);
	
	int len;
	int b,e;
	for (int i = 1; i <= n; i += 1)
	{
		if ( points[i].p[coord] == points[i-1].p[coord] )
		{
			len = abs(points[i-1].p[1-coord] - points[i].p[1-coord]);
			if (points[i-1].idx < points[i].idx)
				b = points[i-1].idx ,  e = points[i].idx;
			else
				b = points[i].idx ,  e = points[i-1].idx;

			if ( b+1 != e && ( len < L || ( len == L && b < B) || (len == L && b == B && e > E)) )
			{
				L = len;
				B = b;
				E = e;
			}
		}
	}
}

void solve(int n)
{
	int x=0,y=0;
	points[0] =  (Point) {x,y,0};
	for (int i = 0; i < n; i += 1)
	{
		switch(str[i])
		{
			case 'N':	y++;	break;
			case 'S':	y--;	break;
			case 'E':	x++;	break;
			case 'W':	x--;	break;
		}
		points[i+1] = (Point) {x,y,i+1};
	}
	
	L=n;
	go(n,0);
	go(n,1);
	
	
	sort(points,points+n+1,cmp1);
	if ( points[B].p[0] == points[E].p[0] )
	{
		if ( points[B].p[1] < points[E].p[1] )
			D = 'N';
		else
			D = 'S';
	}
	else
	{
		if ( points[B].p[0] < points[E].p[0] )
			D = 'E';
		else
			D = 'W';
	}
}


int main()
{
	int tc,n;
	scanf("%d",&tc);
	while(tc--)
	{
		scanf("%d",&n);
		scanf("%s",str);
		
		solve(n);
		printf("%d %d %d %c\n",L,B,E,D);
	}
	
}
