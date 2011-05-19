// <-------------------[sWitCHcAsE]---------------------->
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<cassert>
#include<vector>
#include<map>
#include<cstring>
#include<cassert>
#include<queue>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORS(i,a,n) for(int i=a;i<n;i++)
#define DEBUG
#define ERR(x)  if(debug)cerr<<#x<<" "<<x<<endl 
#define pb push_back
using namespace std;
typedef vector<int> VI;
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> II;

int debug=0;
II ext_euclid(ll a,ll b) {
	ll x,lx,y,ly;
	x=ly=0;
	y=lx=1;
	ll t,q;
	while(b) {
		q=a/b;
		t=b;b=a%b;a=t;
		t=x;x=lx-q*x;lx=t;
		t=y;y=ly-q*y;ly=t;
	}
	//ERR(lx);ERR(ly);
	return make_pair(lx,ly);
}

ll gcd(ll a,ll b) {
	if(b==0)return a;
	else return gcd(b,a%b);
}
 
ll lcm;
ll n1,n2; 

void positivise(ll &a,ll &b) {
	if(a>=0 && b>=0)return;

	ll m1,m2;
	m1=lcm/n1;
	m2=lcm/n2;
	ll n1_t=(-a)/m1;
	n1_t++;
	ll n2_t=(-b)/m2;
	n2_t++;
	ERR(a);ERR(b);ERR(lcm);ERR(n1_t);ERR(n2_t);ERR(m1);ERR(m2);
	if(a<0) {
		a=a + n1_t*m1;
		b=b-n1_t*m2;
	}
	else {
		a=a-n2_t*m1;
		b=b+n2_t*m2;
	}
	cerr<<"AFTER positivise "<<a<<" "<<b<<endl;
	
}
#define MAX 2000000000

int check(int a) {
	if(a>0 && a<=MAX)return 1;
	cerr<<a<<" NOT INSIDE"<<endl;
	return 0;
}
int main(int argc,char** args)
{
	int N;
	
	ll c1,c2;
	while(scanf("%d",&N),N) {
		assert(check(N));
		scanf("%Ld %Ld %Ld %Ld",&c1,&n1,&c2,&n2);
		assert(check(n1));
        assert(check(n2));
        assert(check(c1));
        assert(check(c2));
		ll g=gcd(n1,n2);
		lcm= (n1/g)*n2;
		//ERR(g);
		if(N%g) {
			printf("failed\n");
			continue;
		}
		II ee=ext_euclid(n1,n2);
		ll x0=ee.first;
		ll y0=ee.second;
		x0*=N/g;
		y0*=N/g;
		ERR(x0);ERR(y0);ERR(g);
		ll t1= ceil(-x0 /(n2/g));
		ll t2= floor(y0 /(n1/g));
		ERR(t1);ERR(t2);
		ll X1,Y1,X2,Y2;
		X1= x0 + (n2/g) * t1;
		Y1= y0 - (n1/g)*t1;
		X2= x0 + (n2/g) * t2;
		Y2= y0 - (n1/g)*t2;
		ll printed=1;
		ll cst1,cst2;
		positivise(X1,Y1);
		positivise(X2,Y2);
		cst1= c1*X1 + c2*Y1;
		cst2=c1*X2 + c2*Y2;
		ERR(X1);ERR(Y1);ERR(cst1);ERR(X2);ERR(Y2);ERR(cst2);
		if( c1*X1 + c2*Y1 < c1*X2 + c2*Y2) {
			if(X1 >=0 && Y1>=0) {
				printed=0;
				printf("%lld %lld\n",X1,Y1);
			}
		}
		else {
			if(X2 >=0 && Y2>=0) {
				printed=0;
				printf("%lld %lld\n",X2,Y2);
			}
		}
		if(printed)printf("failed\n");
		
 	}
}
