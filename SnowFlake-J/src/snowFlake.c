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
char ATTR[8][256];
char *SRVR, *USR_NAME, *PASSWD, *DB_NAME, *JAIL;
char *DB_TB_NAME;
char *JUDGE;
char *CONFIG;

int sighupRecvd;


int main(int argc, char** argv) {

	sighupRecvd = 0;
 	signal(SIGHUP, sigHandler);	
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
		fprintf(flog, "[ERROR] Insufficient memory to hold arguments.\n");
	}	
	
	//Default file for configurations.
	config->filename[0] = "/etc/snowflake.conf";
	CONFIG = (char*) &config->filename[0];
	start->count = 1;
	int MODE = 0; /*Whether to Run or not!*/
	int nerrors = arg_parse(argc, argv, argtable);
	if ( !nerrors) {
		fprintf(flog, "[INFO] Options you have entered are:\n");
		if (help->count) {
			arg_print_glossary(flog, argtable, "%-25s %s\n");
			exit(1);
		}
		if (config->count || config->filename[0] != NULL) {
			CONFIG = (char*)  &config->filename[0];
			if ( populateConfigs(CONFIG) ) {
				exit(1);
			}
		}
		if ( start->count + restart->count + stop->count > 1) {
			fprintf(flog, "[ERROR] Start, Stop and Restart must be used independent of each other\n");
			arg_print_syntaxv(flog, argtable, "\n\n");
			arg_print_glossary(flog, argtable, "%-25s %s\n");	
			exit(1);
		} 
		
		if (restart->count) {
			fprintf(flog, "[INFO] Restart SnowFlake Server.\n");
			killSelf();
			MODE = 1;
		}
		else if (stop->count) {
			fprintf(flog, "[INFO] Stop SnowFlake Server.\n");
			killSelf();	
		}
		else {
			fprintf(flog, "[INFO] Start SnowFlake Server.\n");
			MODE = 1;
		}		
	}
	else {
		arg_print_errors(flog, end, "snowFlake");
		fprintf(flog, "\nUsage:\nsnowFlake ");
		arg_print_syntaxv(flog, argtable, "\n\n");
		arg_print_glossary(flog, argtable, "%-25s %s\n");
		exit(1);
	}
	arg_freetable(argtable, sizeof(argtable)/sizeof(argtable[0]));
	if ( MODE ) {
		run();
	}

	return 0;
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

int populateConfigs( char* configFile ) {
	if ( loadFromConfig(configFile) != 0 ) {
		fprintf(flog, "[INFO] Snowflake config at %s may be corrupt.\n\n",configFile);
		return 1;
	}
	else {
		SRVR        = (char*) ATTR[0];
		USR_NAME    = (char*) ATTR[1];
		PASSWD      = (char*) ATTR[2];
		DB_NAME     = (char*) ATTR[3];
		DB_TB_NAME  = (char*) ATTR[4];
		JUDGE       = (char*) ATTR[5];
		JAIL 		= (char*) ATTR[6];
		return 0;
	}
}

int UpdateRecord(MYSQL *conn,  char* user, int status) {
	char query[1000];
	sprintf(query, "UPDATE %s SET status=%d where id='%s'", DB_TB_NAME, status, user);
	printDate();
	fprintf(flog, "[INFO] Trying query %s\n\n",query);
	if ( QUERY(conn,query) != 0 ) {
		fprintf(flog, "[ERROR] Query --- %s\nError %u: %s\n", query, mysql_errno(conn), mysql_error(conn));
		return -1;
	}
	return 0;
}


int checkForQueuedItems() {
    MYSQL_RES *result;
    MYSQL_ROW row;
    #ifdef DEBUG
	printDate();
	fprintf(flog, "[DEBUG] Inside Checking\n\n");
    #endif
    int ret = 0;
    if ( conn == NULL ) {  
		fprintf(flog, "[ERROR] %u: %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
    }
	
    char query[1000];
    int i;
    sprintf(query, "select id, problemid, src_cd, timelimit from %s where status>10 ORDER by time Limit 1", DB_TB_NAME);
    #ifdef DEBUG
		printDate();
		fprintf(flog, "[INFO] Trying query \"%s\"\n\n", query);
    #endif
    if ( QUERY(conn, query) != 0 ) {
		fprintf(flog, "[ERROR] QUERY FAILED\n");
		fprintf(flog, "[ERROR] %u: %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
    }
    printDate();
    fprintf(flog, "[INFO] Query finished \n\n");
    result = RES(conn);
    int fields = FIELDS_IN(result);
    int tot = 0;
    row = ROW(result);
    tot++;
    fprintf(flog, "[INFO] Fields in result %d and rows\n\n",fields);
    if ( fields && row) {
		for( i=0; i < fields; i++) {
			strcpy(toExec[i], row[i]);
			ret = 1;
		}	
			UpdateRecord(conn, toExec[0], 10);	
    }
    else {
		printDate();
		fprintf(flog, "[INFO] Query returned nothing\n\n");
    }	
    fprintf(flog, "\n");
    fprintf(flog, "[INFO] TOTAL %d\n", tot);
    FREE(result);
    fprintf(flog, "[INFO] Going to return %d from CQI\n\n", ret);
    return ret;
}

int run() {
    pid_t myPid = getpid();
    /* Our process ID and Session ID */
    pid_t pid, sid;
    int status, exit_code;
    switch ( (pid = fork()) ) {
		case 0: break;
		case -1: return -1;
		default: fprintf(flog, "[INFO] Exiting after 1st fork and pid of child is %d\n\n", pid);
		 		exit(0);
    } 

    if ( (sid = setsid()) == (pid_t)-1) {
		fprintf(flog, "[ERROR] setsid() failed for pid = %d !!\n\n", pid);
    }
    fprintf(flog, "[INFO] Setsid returned %d\n\n", sid);
	
    switch ( (pid = fork()) ) {
		case -1 : return -1;
		case 0  : break;
		default : fprintf(flog, "[INFO] Exiting after 2nd fork and pid of child is %d\n\n", pid);	
		  exit(0);
    }
    /*clean file mode creation mask */
    umask(0);
    /* change directory to root directory.*/
    chroot("/");
    myPid = getpid();  
    /* Connect to MYSQL Connection*/
    conn = mysql_init(NULL); 
    fprintf(flog, "[INFO] MySQL client version: %s on pid = %d\n", mysql_get_client_info(), myPid);
    if ( mysql_real_connect(conn, SRVR, USR_NAME, PASSWD, DB_NAME, 0, NULL, 0) == NULL ) {
    	fprintf(flog, "[ERROR] %u: %s on pid = %d\n", mysql_errno(conn), mysql_error(conn), myPid);
		exit(1);
    }

    /* Ensure that the JUDGE EXISTS*/
    FILE *judge = fopen(JUDGE,"r");
    if ( judge == NULL ) {
    	printDate();
    	fprintf(flog, "[ERROR] Judge does not exist. WTF man!!\n");
    	exit(EXIT_FAILURE);
    }

    /* Close out the standard file descriptors */
    #ifndef DEBUG
  		close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
        flog = fopen("/var/log/snowflake/daemon.logs","w+"); /*Open file for read and write and start from beginning.*/    		
    #else
    	flog = stdout;
    #endif

    /* Open any logs here */                
    if ( flog == NULL ) {
    	printf("FAILED AT FILE\n");
     	exit(EXIT_FAILURE);
    }
    
    myPid = getpid();    
    fprintf(flog, "[INFO] SnowFlake started @");		                
    printDate();
    fprintf(flog, "with pid = %d\n--------------\n\n",myPid);
        
   /* The Big Loop */

    while (1) {
        fflush(flog);
       	fprintf(flog, "[INFO] Checking for Queued Items\n");
        if ( checkForQueuedItems() ) {
        	pid = fork();
        	if ( pid > 0 ) {
        		printDate();
        		fprintf(flog, "[INFO] Forked a child process pid=%d\n", pid);
        		fflush(flog);
        		wait4(pid, &status, 0, NULL);
        		if ( WIFEXITED(status) ) {
					exit_code = WEXITSTATUS(status);
					fprintf(flog, "[INFO] Updating ... with status code=%d for id %s\n", exit_code, toExec[0]);
					fflush(flog);
					UpdateRecord(conn, toExec[0], exit_code);
					printDate();
					fprintf(flog, "[INFO] %d Execution completed. Judge returned a status %d\n", pid, exit_code);
					fflush(flog);
        		}
        		else {
        			if ( WIFSIGNALED(status) ) {
        				status = WTERMSIG(status);
					}
        			printDate();
        			fprintf(flog, "[INFO] Exit status was wierd! Terminated with signal %d\n\n", status );
        		}
        	}
        	else {
        		if (execl(JUDGE, toExec[1], toExec[2], toExec[3], NULL)) {
        			fprintf(flog, "[ERROR] Exec failed on \"%s %s %s %s\"\n\n",JUDGE, toExec[1], toExec[2], toExec[3]);
        		}
        	}
        }
        else {
       		fprintf(flog, "[INFO] Sleeping for a while. Do not wake me.\n");
       		fflush(flog);
    		sleep(5); /* wait 5 seconds */	 	 		              
    	}
		if ( sighupRecvd ) {
			sighupRecvd = 0;
			printDate();
			fprintf(flog, "[INFO] Resetting Daemon\n\n");
			fprintf(flog, "[INFO] Reloading config\n\n");
			if ( populateConfigs(CONFIG) ) {
				fprintf(flog, "[ERROR] Snowflake config file %s may be corrupt. Please check.\nExiting SnowFlake\n", CONFIG);
				exit(1);
			}
			printDate();
			fprintf(flog, "[INFO] Resetting MYSQL connection\n\n");
			CLOSE(conn);
			conn = mysql_init(NULL);
			fprintf(flog, "[INFO] MySQL client version: %s\n", mysql_get_client_info());
			if ( mysql_real_connect(conn, SRVR, USR_NAME, PASSWD, DB_NAME, 0, NULL, 0) == NULL ) {
				fprintf(flog, "[ERROR] %u: %s\n", mysql_errno(conn), mysql_error(conn));
				exit(1);
			}
		}
    }
    
    fclose(flog);
    CLOSE(conn);
    exit(EXIT_FAILURE);
}

int loadFromConfig(const char *config_file) {
	config_t config;
	config_init(&config);
	const char* attr[] ={"server", "username", "password", "db_name", "db_table", "judge", "jail", NULL};
	int curr=0;
	if ( config_read_file(&config, config_file) == CONFIG_TRUE ) {
		while( attr[curr] != NULL ) {
			const config_setting_t *setting = config_lookup(&config, attr[curr]);
			
			if( setting != NULL) {
				char *tmp = (char*) config_setting_get_string(setting);
				if ( strlen(ATTR[curr]) > 255 ) {
					fprintf(flog, "[INFO] Setting %s is too large. Please truncate it to fit 255 bytes\n", attr[curr]);
				}
				memcpy(ATTR[curr], tmp, strlen(tmp));
				fprintf(flog, "[INFO] %s is %s\n", attr[curr], ATTR[curr]);
			}
			else {
				fprintf(flog, "[INFO] Setting %s not found. Please check\n", attr[curr]);
				config_destroy(&config);
				return 1;
			}
			curr++;
		}
	}
	else {
		fprintf(flog, "[INFO] %s:%d - %s\n", config_error_file(&config),
	    config_error_line(&config), config_error_text(&config));
   		config_destroy(&config);
   		return 1;
	}
	config_destroy(&config);

	return 0;
}

void cleanUp() {
	printDate();
	fprintf(flog, "[INFO] SnowFlake Dying !!\n"); 
	fflush(flog);
	fclose(flog);
}
void killSelf() {
	system("killall -s 9 snowFlake");
}

void sigHandler(int signum) {
	fprintf(flog, "[INFO] Snowflake recvd signal %d\n",signum);
	if ( signum == SIGHUP ) {
		sighupRecvd = 1;
		return;
	}
	fprintf(flog, "[INFO] Snowflake killed\n");	
	exit(1);
}
