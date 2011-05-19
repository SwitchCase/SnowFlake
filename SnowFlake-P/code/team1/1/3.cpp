// <-------------------[sWitCHcAsE]---------------------->

#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
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

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef unsigned int uint;

using namespace std;
inline VS split(string s,char* tok){VS vs;char *pch;char *q= (char*)s.c_str();  pch=strtok(q,tok);while(pch !=NULL){vs.pb(string(pch));pch=strtok(NULL,tok);}return vs;}

#define MAX 10000000
int main()
{
    	int ana[]={2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, 97, 113, 131, 199, 311, 337, 373, 733, 919, 991};
    	int a=0;
    	while(scanf("%d",&a),a)
    	{
            if(a>=991)printf("0\n");
            else
            {
                if(a>=100)
                {
                    for(int i=13;i<22;i++)
                    {
                        if(ana[i]>a)
                        {
                            printf("%d\n",ana[i]);
                            goto kontinue;
                        }
                    }
                }
                else if(a>=10)
                {
                    for(int i=0;i<22;i++)
                    {
                        if(ana[i]>a && ana[i]<100)
                        {
                            printf("%d\n",ana[i]);
                            goto kontinue;
                        }
                    }
                    printf("0\n");
                }
                else
                {
                    for(int i=0;i<22;i++)
                    {
                        if(ana[i]>a && ana[i]<10)
                        {
                            printf("%d\n",ana[i]);
                            goto kontinue;
                        }
                    }
                    printf("0\n");
                    
                }
                kontinue:continue;
            }
        }
        
    
}
