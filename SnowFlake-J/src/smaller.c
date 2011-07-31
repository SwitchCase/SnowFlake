
#include <stdio.h>
#include "libconfig.h"

int main(int argc, char **argv) {
	
	char SRVR[1000];
	char *p=SRVR;
	config_t config;
	config_init(&config);
	if ( config_read_file(&config, "/etc/snowflake.conf") == CONFIG_TRUE ) {
		printf("PARt 1\n");
		const config_setting_t *setting = config_lookup(&config, "server");
		
		if( setting != NULL) {
			p = config_setting_get_string(setting);
			printf("opened file\n");	
			printf("SERVER ADDRESS = %s\n",p);
		}
		else {
			printf("ERROR\n");
		}
	}
	else {
		fprintf(stderr, "%s:%d - %s\n", config_error_file(&config),
            config_error_line(&config), config_error_text(&config));
    config_destroy(&config);
    return(1);
	}
	
	
}
