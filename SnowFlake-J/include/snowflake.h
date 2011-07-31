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
int run();
void killSelf();
void cleanUp();
void sigHandler(int);

#endif

