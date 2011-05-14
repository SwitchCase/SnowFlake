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
#include<ctime>
#define FOR(i,n) for(i=0;i<n;i++)
#define FORS(i,a,n) for(i=a;i<n;i++)
#define ERR(x) cerr<<#x<<" "<<x<<endl
#define pb push_back
using namespace std;
typedef vector<int> VI;
typedef long long ll;
typedef long double ld;

FILE *flog;
char SRVR[1000], USR_NAME[1000], PASSWD[1000], DB_NAME[1000];

void printDate() {
	
	time_t tt;
	struct tm *tod;
	time(&tt);
	tod=localtime(&tt);
	char AM[2][5]={"AM\0","PM\0"};
	fprintf(flog," [%d-%d-%d :: %d:%d:%d%s] ",tod->tm_mday,tod->tm_mon+1,tod->tm_year+1900,tod->tm_hour%12,tod->tm_min,tod->tm_sec, AM[tod->tm_hour/12]);
		
}

char * trim(char *inp,int n) {
	cerr<<"TRIM CALLED WID "<<inp<<" "<<n<<endl;
	int i=0;
	while(i++<n) {
		cerr<<*inp;
		if(*inp=='\t' || *inp=='\r' || *inp==' ')inp++;
		else {
			cerr<<endl;
			return inp;
		}
	}
	return inp;
}

int removeHash(char inp[],int l) {
	int i=0;
	int ff=0;
	while(i<l) {
	
		if(!ff && inp[i]=='#') {
			inp[i]=0;
			ff=1;
		}
		else if(ff)inp[i]=0;
		i++;
	}
	return 0;
}

int loadParameters() {
	FILE *f=fopen("/etc/snowflake.conf","r");
	if(f==NULL) {
		printDate();
		fprintf(flog,"SnowFlake configurations were not found. Service Killed\n");
		exit(1);
	}
	char buff[1000],toprocess[1000],lhs[1000],equals[1000],rhs[1000];	
	char wrd[1000];
	int curr=0,len,fi;
	int w=0;
	int r;
	char *pro;
	char *lhsp,*rhsp,*eqp;
	while(fgets(buff,sizeof(buff),f)!=NULL) {
		fflush(f);
		memset(toprocess,0,sizeof (toprocess));
		curr=0;
		fi=0;
		len=strlen(buff);
		cerr<<"FOUND LINE :"<<buff<<endl;
		removeHash(buff,strlen(buff));
		pro=trim(&buff[0],strlen(buff));
		
		cerr<<"REMAINING TO PROCESS "<<pro<<endl;
		
		if(strlen(pro)>10 && sscanf(pro," %s %s %s",lhs,equals,rhs)==EOF) {
			printDate();
			fprintf(flog,"SnowFlake config is corrupt. Please Check\n");
		} ;
		cerr<<"LHS :"<<lhs<<"RHS :"<<rhs<<"eq :"<<equals<<endl;
		lhsp=trim(&lhs[0],strlen(lhs));
		eqp=trim(&equals[0],strlen(equals));
		rhsp=trim(&rhs[0],strlen(rhs));
		cerr<<lhsp<<" "<<eqp<<" "<<rhsp<<endl;
		if(!strcmp(lhsp,"server") && !strcmp(eqp,"=")) {
			memcpy(SRVR,rhsp,strlen(rhsp));	
		}
		else if(!strcmp(lhsp,"user") && !strcmp(eqp,"=")) {
			memcpy(USR_NAME,rhsp,strlen(rhsp));
			
		}
		else if(!strcmp(lhsp,"password") && !strcmp(eqp,"=")) {
			memcpy(PASSWD,rhsp,strlen(rhsp));
		}
		else if(!strcmp(lhsp,"db_name") && !strcmp(eqp,"=")) {
			memcpy(DB_NAME,rhsp,strlen(rhsp));
		}
		else {
			printDate();
			fprintf(flog,"SnowFlake config has invalid attribute. Please check.\n");
		}
		memset(buff,0,sizeof(buff));	
	}
	
}

 
int main()
{
	flog=stderr;
	if(loadParameters()) {
		cerr<<"ERROR"<<endl;
	}
	cerr<<USR_NAME<<" "<<PASSWD<<" "<<SRVR<<" "<<DB_NAME<<endl;
}
