// <-------------------[sWitCHcAsE]---------------------->
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cassert>
#include <vector>


#define FOR(i,a) for(int i=0;i<a;i++)
#define FORS(i,a,b) for(int i=a;i<b;i++)
#define FORR(i,a) for(int i=a;i>=0;i--)
#define pb push_back
#define VI vector<int>
#define VS vector <string>
#define MAX2(a,b) (a)<(b)?(b):(a)
#define MIN2(a,b) (a)<(b)?(a):(b)
#define LEN(s) strlen(s)
#define tests(tc) int tc;scanf("%d",&tc);while(tc--)
#define TEN(n) (long long)pow(10LL,n)
#define foreach(it,x) for(typeof(x.begin()) it=x.begin();it!=x.end();++it)
#define bits __builtin_popcount
#define ERR(x) if(debug) cerr<<#x<<" "<<x<<endl;
#define ASS(x) assert(x>0 && x<=MAX)

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef unsigned int uint;

using namespace std;

int MAX=2000000000;
int sieve[100000];
VI primes;

void dosieve() {
	cerr<<"DOING SIEVE"<<endl;
    memset(sieve,1,sizeof sieve);
    sieve[2]=1;
    int i=4;
    while(i<100000) {
        sieve[i]=0;
        i=i+2;
    }
    primes.pb(2);
    for(i=3;i*i<100000;i+=2) {
        if(sieve[i]) {
            primes.pb(i);
            for(int j=i*i;j<100000;j+=2*i) {
                sieve[j]=0;
            }
        }
    }
    cerr<<"DONE SIEVE"<<endl;
}

void itoa(int a,char *buff,int) {

	sprintf(buff,"%d",a);
}

int isPrime(int N) {
    for(int i=0;i<primes.size();i++) {
        if(N%primes[i])return 0;
    }
    return 1;
}
/*
int main() {
    int a,b;
    while(1) {
    scanf("%d %d",&a,&b);
    cout<<GCD(a,b)<<endl;
}
}*/

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

ll GCD(ll a,ll b) {
	if(b==0)return a;
	else return GCD(b,a%b);
}
 
ll lcm;
ll n1,n2; 

void positivise(ll &a,ll &b) {
	if(a>=0 && b>=0)return;
	assert(lcm!=0);
	ll m1,m2;
	m1=lcm/n1;
	m2=lcm/n2;
	if(m1==0 || m2==0){
		ERR(n1);
		ERR(n2);
	}
	assert(m1!=0 && m2!=0);
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


int main() {
    dosieve();
    int TOTAL_FILES=200;
    int TESTS=10000;
    char buff[100];
    int done=0;
    string filename="tempin";
     int dt=TESTS;
    for(;done<2;done++) {
        itoa(done,buff,10);
        freopen((filename+string(buff)).c_str(),"w",stdout);
        dt=TESTS;
        while(dt--) {
            int N=(rand()%MAX);
            cout<<N<<endl;
            cout<<(rand() %MAX)<<" "<<(rand()%(N+rand()%10))<<endl;
            cout<<(rand() %MAX)<<" "<<(rand()%(N+rand()%10))<<endl;
        }
        cout<<"0"<<endl;
    }
    while(done<TOTAL_FILES) {
        cerr<<"TESTS DONE "<<done<<endl;
        itoa(done,buff,10);
        freopen((filename+string(buff)).c_str(),"w",stdout);
        dt=TESTS;   
        while(dt--) {
       
            int primeth=rand()%primes.size();
            primeth += rand()%1007;
            int gcd;
            if(primeth<primes.size()) {
                gcd=primes[primeth];
            }
            else {
                gcd=primeth%MAX;
            }
            int N=(done<90?((rand()%MAX)*gcd)%MAX:rand()%MAX);
            if(N==0) N=121*13*19;
            int left=rand()%MAX;
            int c2=(rand()%left)*gcd;
            int c1=(rand()%left)*gcd;
            c1=abs(c1);
            c2=abs(c2);
            c1%=MAX;
            c2%=MAX;
            
            cerr<<c1<<" "<<c2<<endl;
            assert(c1<=MAX && c1>0);
            assert(c2<=MAX && c2>0);
            assert(gcd>0);
            int ff=rand()%gcd;
            int temp=(abs(gcd*gcd)%MAX);
            if(temp==0)temp=121;
            int ss=rand()%temp;
            int lf=rand()%N;
            if(ss==0)ss+=112;
            int sf= (N - (ff *lf))/ss;
            n1=lf;
            n2=sf;
            
            II ans=ext_euclid(n1,n2);
            cerr<<"DONE "<<endl;
            ll p1=ans.first;
            ll p2=ans.second;
            lcm = (n1/GCD(n1,n2)) * n2;
            lcm=abs(lcm);
            ERR(lcm);
            positivise(p1,p2);
           	ERR(p1);
           	if(p1>=0 && p1<=MAX && p2>=0 && p2<=MAX) {
           		n1=p1%MAX;
           		n2=p2%MAX;
           	} 
           	else {
           		n1=abs(n1)%MAX;
           		n2=abs(n2)%MAX;
           	}
           	N=abs(N);
           	c1=abs(c1);
           	c2=abs(c2);
           	n1=abs(n1)%MAX;
           	if(n1<=0)n1=12;
           	n2=abs(n2);
           	if(n2<=0)n2=13;
           	ASS(N);ASS(c1);ASS(c2);ASS(n1);ASS(n2);
            cout<<N<<endl<<c1<<" "<<n1<<endl<<c2<<" "<<n2<<endl;
        }
        cout<<"0"<<endl;
        done++;
    }
    system("pause");
    
}
