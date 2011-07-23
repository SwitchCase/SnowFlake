#ifndef _snowFlake
#define _snowFlake

#define QUERY(c,s) mysql_query(c,s)
#define RES mysql_store_result
#define FIELDS_IN mysql_num_fields 
#define ROW mysql_fetch_row
#define FREE mysql_free_result
#define CLOSE mysql_close

void printDate();
int UpdateRecord(MYSQL*,char*, int);
int checkForQueuedItems();
char* trim(char *,int);
int removeHash(char[],int);
int loadParameters();
int isWhiteSpace(char);
int process(char*,char*,char*,char*);
int run();

#endif

