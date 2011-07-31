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
#include <signal.h>

#include "snowflake.h"
#include "argtable2.h"
#include "libconfig.h"

FILE *flog;
char toExec[5][1000];
MYSQL *conn;
char* ATTR[7];
char *SRVR, *USR_NAME, *PASSWD, *DB_NAME;
char *DB_TB_NAME;


int main(int argc, char** argv) {

	signal(SIGINT, sigHandler);
	signal(SIGSEGV, sigHandler);
	
 	atexit(cleanUp);   	
	flog = stderr;	
	struct arg_lit *start 	= arg_lit0("s", "start", "Starts SnowFlake.");
	struct arg_lit *stop 	= arg_lit0("p", "stop", "Stops SnowFlake.");
	struct arg_lit *restart = arg_lit0("r", "restart", "Restarts SnowFlake.");
	struct arg_file *config = arg_file0("c", "config", "config_file", "Snowflake Configuration file.");
	struct arg_lit *help  	= arg_lit0("h", "help", "Help menu");
	struct arg_end *end 	= arg_end(10);
	void *argtable[] 		= { start, stop, restart, config, help, end };
	
	if (arg_nullcheck(argtable) != 0) {
		fprintf(flog, " [ERROR] Insufficient memory to hold arguments.\n");
	}	
	
	//Default file for configurations.
	config->filename[0] = "/etc/snowflake.conf";
	start->count = 1;
	
	int nerrors = arg_parse(argc, argv, argtable);
	if ( !nerrors) {
		fprintf(flog, "Options you have entered are:\n");
		
		if (help->count) {
			arg_print_glossary(flog, argtable, "%-25s %s\n");
			exit(1);
		}
		
		if (config->count || config->filename[0] != NULL) {
			fprintf(flog, "Config file set to %s\n",config->filename[0]);
			if ( loadFromConfig(config->filename[0]) != 0 ) {
				fprintf(flog, "Snowflake config at %s may be corrupt.\n\n",config->filename[0]);
				exit(1);
			}
			else {
				SRVR 	 	= ATTR[0];
				USR_NAME 	= ATTR[1];
				PASSWD	 	= ATTR[2];
				DB_NAME	 	= ATTR[3];
				DB_TB_NAME  = ATTR[4];
			}
		}
		
		if ( start->count + restart->count + stop->count > 1) {
			fprintf(flog, " [ERROR] Start, Stop and Restart must be used independent of each other\n");
			arg_print_syntaxv(flog, argtable, "\n\n");
			arg_print_glossary(flog, argtable, "%-25s %s\n");	
			exit(1);
		} 
		
		if (restart->count) {
			fprintf(flog, "Restart SnowFlake Server.\n");
			killSelf();
			run();
		}
		else if (stop->count) {
			fprintf(flog, "Stop SnowFlake Server.\n");
			killSelf();	
		}
		else {
			fprintf(flog, "Start SnowFlake Server.\n");
			run();
		}		
	}
	else {
		arg_print_errors(flog, end, "snowFlake");
		fprintf(flog, "\nUsage:\nsnowFlake ");
		arg_print_syntaxv(flog, argtable, "\n\n");
		arg_print_glossary(flog, argtable, "%-25s %s\n");
		exit(1);
	}

}


void printDate() {
	
	time_t tt;
	struct tm *tod;
	time(&tt);
	tod=localtime(&tt);
	char AM[2][5]={"AM\0","PM\0"};
	fprintf(flog, " [%d-%d-%d :: %d:%d:%d%s] ", tod->tm_mday, tod->tm_mon + 1, tod->tm_year + 1900, tod->tm_hour % 12, tod->tm_min, tod->tm_sec, AM[tod->tm_hour / 12]);
	fflush(flog);
		
}



int UpdateRecord(MYSQL *conn,  char* user, int status) {
	char query[1000];
	sprintf(query, "UPDATE %s SET status=%d where id='%s'", DB_TB_NAME, status, user);
	if ( QUERY(conn,query) != 0 ) {
		fprintf(flog, "##FAILED :: Query --- %s\nError %u: %s\n", query, mysql_errno(conn), mysql_error(conn));
		return -1;
	}
	return 0;

}


int checkForQueuedItems() {
	
	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	
	int ret = 0;

	if ( conn == NULL ) {  
		fprintf(flog, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
	}
	
    char query[1000];
    int i;
    sprintf(query, "select id, problemid, src_cd, timelimit from %s where status>10 ORDER by time Limit 1", DB_TB_NAME);
	if ( QUERY(conn, query) != 0 ) {
		fprintf(flog, "QUERY FAILED\n");
		fprintf(flog, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	result = RES(conn);
	int fields = FIELDS_IN(result);
	int tot = 0;
	row = ROW(result);
	tot++;
	for( i=0; i < fields; i++) {
		strcpy(toExec[i], row[i]);
		ret = 1;
	}	
	UpdateRecord(conn, toExec[0], 10);	
	
	fprintf(flog, "\n");
	fprintf(flog, "TOTAL %d\n", tot);
	FREE(result);

	return ret;
}



int run() {
    conn = mysql_init(NULL); /* mysql connection*/
   	pid_t myPid = getpid();
        /* Our process ID and Session ID */
    pid_t pid, sid;
    int status, exit_code;
    fprintf(flog, "MySQL client version: %s\n", mysql_get_client_info());
    char *JUDGE = "/var/www/judge/onj";
    FILE *judge = fopen(JUDGE,"r");
    if ( judge == NULL ) {
    	printDate();
    	fprintf(flog, "Judge does not exist. WTF man!!\n");
    	exit(EXIT_FAILURE);
    }
    if ( mysql_real_connect(conn, SRVR, USR_NAME, PASSWD, DB_NAME, 0, NULL, 0) == NULL ) {
    	fprintf(flog, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
    	exit(1);
    }
    
    
    
        /* Fork off the parent process */
    pid = fork();
    if ( pid < 0 ) {
    	printf("FAILED AT FORK\n");
    	exit(EXIT_FAILURE);
    }
        /* If we got a good PID, then
           we can exit the parent process. */
    if ( pid > 0 ) {
    	printf("DONE AT FORK\nCreated Child %d using parent %d\n\n",pid, myPid);        
    	exit(EXIT_SUCCESS);
    }

        /* Change the file mode mask */
    umask(0);
        
        /* Close out the standard file descriptors */
        #ifndef DEBUG
       		close(STDIN_FILENO);
       		close(STDOUT_FILENO);
        	close(STDERR_FILENO);
        	flog=fopen("/var/log/snowflake/daemon.logs","a+"); /*Open file for read and write and start from beginning.*/    	
        	
        #else
    		flog=stdout;
        #endif

		/* Open any logs here */                
        
    
    if ( flog == NULL ) {
    	printf("FAILED AT FILE\n");
     	exit(EXIT_FAILURE);
    }
           
    fprintf(flog, "SnowFlake started @");		                
    printDate();
    fprintf(flog, "with pid = %d\n--------------\n\n",myPid);
        
    /* Create a new SID for the child process */
    sid = setsid();
    if ( sid < 0 ) {
                /* Log the failure */
        fprintf(flog, "Snowflake died because setsid failed.\n\n");
    	exit(EXIT_FAILURE);
    }
        
    /* Change the current working directory */
    if ( chdir("/") < 0 ) {
        /* Log the failure */
    	exit(EXIT_FAILURE);
    }
    flog = stdout;    
   /* The Big Loop */

    while (1) {
        fflush(flog);
        #ifdef DEBUG
        	fprintf(flog, "Checking for Queued Items\n");
        #endif
        if ( checkForQueuedItems() ) {
        	pid = fork();
        	if ( pid > 0 ) {
        		printDate();
        		fprintf(flog, "Forked a child process pid=%d\n", pid);
        		fflush(flog);
        		wait4(pid, &status, 0, NULL);
        		if ( WIFEXITED(status) ) {
					exit_code = WEXITSTATUS(status);
					#ifdef DEBUG
						fprintf(flog, "Updating ... with status code=%d for id %s", exit_code, toExec[0]);
						fflush(flog);
					#endif
					UpdateRecord(conn, toExec[0], exit_code);
					printDate();
					fprintf(flog, " %d Execution completed. Judge returned a status %d\n", pid, exit_code);
					fflush(flog);
        		}
        	}
        	else {
        		execl(JUDGE, toExec[1], toExec[2], toExec[3], NULL);
        	}
        }
        else {
        	#ifdef DEBUG
        		fprintf(flog, "Sleeping for a while. Do not wake me.\n");
        		fflush(flog);
        	#endif
    		sleep(5); /* wait 5 seconds */	 	 		              
    	}
    }
    
    fclose(flog);
    CLOSE(conn);
    exit(EXIT_FAILURE);
}

int loadFromConfig(char *config_file) {
	config_t config;
	config_init(&config);
	const char* attr[] ={"server", "user", "password", "db_name", "db_table", NULL};
	int curr=0;
	if ( config_read_file(&config, config_file) == CONFIG_TRUE ) {
		while( attr[curr] != NULL ) {
			const config_setting_t *setting = config_lookup(&config, attr[curr]);
			
			if( setting != NULL) {
				ATTR[curr] = config_setting_get_string(setting);
				fprintf(flog, "%s is %s\n", attr[curr], ATTR[curr]);
			}
			else {
				fprintf(flog, "Setting %s not found. Please check\n", attr[curr]);
				config_destroy(&config);
				return 1;
			}
			curr++;
		}
	}
	else {
		fprintf(flog, "%s:%d - %s\n", config_error_file(&config),
            config_error_line(&config), config_error_text(&config));
   		config_destroy(&config);
   		return 1;
	}
	
}

void cleanUp() {
	printDate();
	fprintf(flog, "SnowFlake Dying !!\n"); 
	fflush(flog);
	close(flog);
}
void killSelf() {
	system("killall -s 9 snowFlake");
}

void sigHandler(int signum) {
	fprintf(flog, "Snowflake recvd signal %d\n",signum);
	fprintf(flog, "Snowflake killed\n");	
	exit(1);
}
