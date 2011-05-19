#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <my_global.h>
#include <mysql.h>

#include "snowflake.h"


FILE *flog;
char toExec[5][1000];
MYSQL *conn;
char SRVR[1000], USR_NAME[1000], PASSWD[1000], DB_NAME[1000];


int main(void) {

	conn=mysql_init(NULL); /* mysql connection*/
    if(loadParameters()) {
    	printDate();
    	fprintf(flog,"Failed to load Parameters. Exiting SnowFlake.\n");
    	exit(EXIT_FAILURE);
    }
        /* Our process ID and Session ID */
    pid_t pid, sid;
    int status,exit_code;
        /* Fork off the parent process */
    pid = fork();
    if (pid < 0) {
    	printf("FAILED AT FORK\n");
    	exit(EXIT_FAILURE);
    }
        /* If we got a good PID, then
           we can exit the parent process. */
    if (pid > 0) {
    	printf("DONE AT FORK\n");        
    	exit(EXIT_SUCCESS);
    }

        /* Change the file mode mask */
    umask(0);
        
        /* Close out the standard file descriptors */
        #ifndef DEBUG
       		close(STDIN_FILENO);
       		close(STDOUT_FILENO);
        	close(STDERR_FILENO);
        	flog=fopen("/var/log/snowflake/daemon.logs","w+"); /*Open file for read and write and start from beginning.*/    	
        	
        #else
    		flog=stdout;
        #endif

		/* Open any logs here */                
        
    
    if(flog==NULL) {
    	printf("FAILED AT FILE\n");
     	exit(EXIT_FAILURE);
    }
           
    fprintf(flog,"SnowFlake started @");		                
    printDate();
    fprintf(flog,"\n--------------\n\n");
        
    /* Create a new SID for the child process */
    sid = setsid();
    if (sid < 0) {
                /* Log the failure */
    	exit(EXIT_FAILURE);
    }
        
    /* Change the current working directory */
    if ((chdir("/")) < 0) {
        /* Log the failure */
    	exit(EXIT_FAILURE);
    }
    flog=stdout;    
   /* The Big Loop */
    fprintf(flog,"MySQL client version: %s\n", mysql_get_client_info());
    char *JUDGE="/var/www/judge/onj";
    FILE *judge=fopen(JUDGE,"r");
    if(judge==NULL) {
    	printDate();
    	fprintf(flog,"Judge does not exist. WTF man!!\n");
    	exit(EXIT_FAILURE);
    }
    while (1) {
        fflush(flog);
        if(checkForQueuedItems()) {
        	pid=fork();
        	if(pid > 0) {
        		printDate();
        		fprintf(flog," Forked a child process pid=%d\n",pid);
        		wait4(pid,&status,0,NULL);
        		if(WIFEXITED(status)) {
					exit_code=WEXITSTATUS(status);
					UpdateRecord(conn, toExec[0],exit_code);
					printDate();
					fprintf(flog," %d Execution completed. Judge returned a status %d\n",pid,exit_code);
        		}
        	}
        	else {
        		execl(JUDGE,toExec[1],toExec[2],toExec[3]);
        	}
        }
        else {
    		sleep(5); /* wait 5 seconds */	 	 		              
    	}
    }
    
    fclose(flog);
    CLOSE(conn);
    exit(EXIT_SUCCESS);
    
}


void printDate() {
	
	time_t tt;
	struct tm *tod;
	time(&tt);
	tod=localtime(&tt);
	char AM[2][5]={"AM\0","PM\0"};
	fprintf(flog," [%d-%d-%d :: %d:%d:%d%s] ",tod->tm_mday,tod->tm_mon+1,tod->tm_year+1900,tod->tm_hour%12,tod->tm_min,tod->tm_sec, AM[tod->tm_hour/12]);
		
}



int UpdateRecord(MYSQL *conn,  char* user, int status) {
	char query[1000];
	sprintf(query,"UPDATE %s SET status=%d where id='%s'",DB_TB_NAME,status,user);
	if(QUERY(conn,query)!=0) {
		fprintf(flog,"##FAILED :: Query --- %s\nError %u: %s\n",query,mysql_errno(conn),mysql_error(conn));
		return -1;
	}
	return 0;

}


int checkForQueuedItems() {
	
	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	
	int ret=0;

	if(conn==NULL) {  
		fprintf(flog,"Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
	}
	if (mysql_real_connect(conn, SRVR, USR_NAME, PASSWD, DB_NAME,0, NULL, 0) == NULL) {
    	fprintf(flog,"Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
    	exit(1);
    }
    char query[1000];
    int i;
    sprintf(query,"select id, problemid, src_cd, timelimit from %s where status>10 ORDER by time",DB_TB_NAME);
	if( QUERY(conn,query)!=0) {
		fprintf(flog,"QUERY FAILED\n");
		fprintf(flog,"Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	result=RES(conn);
	int fields=FIELDS_IN(result);
	int tot=0;
	row=ROW(result);
	tot++;
	for(i=0;i<fields;i++) {
		strcpy(toExec[i],row[i]);
		ret=1;
	}	
	UpdateRecord(conn,toExec[0],10);	
	
	fprintf(flog,"\n");
	fprintf(flog,"TOTAL %d\n",tot);
	FREE(result);

	
	return ret;
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

		removeHash(buff,strlen(buff));
		pro=trim(&buff[0],strlen(buff));
		
		memset(lhs,0,sizeof(lhs));
		memset(rhs,0,sizeof(rhs));
		memset(equals,0,sizeof(equals));
		
		if(strlen(pro)>3 && process(pro,lhs,equals,rhs)) {
			printDate();
			fprintf(flog,"SnowFlake config is corrupt. Please Check\n");
		} 
		else if(strlen(pro)>3) {
			lhsp=trim(&lhs[0],strlen(lhs));
			eqp=trim(&equals[0],strlen(equals));
			rhsp=trim(&rhs[0],strlen(rhs));
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
		}
		memset(buff,0,sizeof(buff));	
	}
	
}


int isWhiteSpace(char a) {
	return a==' ' || a=='\t';
}

int process(char *inp, char* lhs,char* eq,char* rhs) {
	int n=strlen(inp);
	int i=0;
	int upd=-1;
	int idx=0;
	int chg=0;
	while(i<n && isWhiteSpace(inp[i])) i++;
	idx=0;
	if(i>=n)return 1;
	while(i<n && !isWhiteSpace(inp[i]) && inp[i]!='=') {
		lhs[idx++]=inp[i++];
	}	
	while(i<n && isWhiteSpace(inp[i])) i++;
	idx=0;
	if(i>=n || inp[i]!='=')return 1;
	eq[0]='=';
	i++;
	while(i<n && isWhiteSpace(inp[i])) i++;
	idx=0;
	if(i>=n)return 1;
	while(i<n && !isWhiteSpace(inp[i]) && inp[i]!='=') {
		rhs[idx++]=inp[i++];
	}
	return 0;
	
}

char * trim(char *inp,int n) {
	int i=0;
	while(i++<n) {
		if(*inp=='\t' || *inp=='\r' || *inp==' ')inp++;
		else {
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

