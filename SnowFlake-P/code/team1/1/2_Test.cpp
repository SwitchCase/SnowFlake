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

#define FOR(i,n) for(i=0;i<n;i++)
#define FORS(i,a,n) for(i=a;i<n;i++)
#define ERR(x) cerr<<#x<<" "<<x<<endl
#define pb push_back
using namespace std;
typedef vector<int> VI;
typedef long long ll;
typedef long double ld;
void itoa(int a,char *buff,int) {
	sprintf(buff,"%d",a);
}

#define MAX 1001 
int main(int argc,char** args)
{
	int i,j,k;
	int files=4;
	int tests=2000;
	string filename="in";
	char buff[100];
	FOR(i,files) {
		itoa(i,buff,10);
        freopen((filename+string(buff)).c_str(),"w",stdout);
        int t=rand()%tests;
        cout<<t<<endl<<endl;
        while(t--) {
        	int n=rand()%MAX;
        	if(n<5)n+=25;
        	cout<<n<<endl<<endl;
        }
        
	}
	
 	
 	
}
