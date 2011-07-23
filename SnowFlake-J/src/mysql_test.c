#include <my_global.h>
#include <mysql.h>


#define DB_NAME "onj2"
#define DB_TB_NAME "submissions"
#define USR_NAME "root"
#define PASSWD "sparkie"
#define SRVR "localhost"
#define QUERY(c,s) mysql_query(c,s)
#define RES mysql_store_result
#define FIELDS_IN mysql_num_fields 
#define ROW mysql_fetch_row
#define FREE mysql_free_result
#define CLOSE mysql_close

int main(int argc, char **argv)
{
	printf("MySQL client version: %s\n", mysql_get_client_info());
	MYSQL *conn;
	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL_FIELD *field;


	conn=mysql_init(NULL);
	if(conn==NULL) {  
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
	}
	if (mysql_real_connect(conn, SRVR, USR_NAME, PASSWD, DB_NAME,0, NULL, 0) == NULL) {
    	printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
    	exit(1);
    }
    uint time= 1303400820;
    char query[1000];
    int i;
/*    for( i=0;i<1000;i++) {
    
    	sprintf(query,"INSERT INTO submissions VALUES (%d,%d,1, 100, %d)",i+12,i+13,time + 1010*i);
		if(mysql_query(conn,query)==0)printf("DID NOT RUN\n");
	}*/
	if( mysql_query(conn,"select * from submissions where status>10 ORDER by time")!=0) {
		printf("QUERY FAILED\n");
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	result=RES(conn);
	int fields=FIELDS_IN(result);
	int tot=0;
	while((row=ROW(result))) {
		tot++;
		for(i=0;i<fields;i++) {
			printf("%s ",row[i]);
		}		
		printf("\n");
	}	
	printf("TOTAL %d\n",tot);
	FREE(result);
	CLOSE(conn);
}

