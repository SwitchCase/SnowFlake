
#include <stdio.h>
#include "libs/argtable/argtable2.h"

int main(int argc, char **argv) {
	struct arg_int *s;
	s = arg_int0("s", "scalar", "<n>", "foo value");
	struct arg_end *end = arg_end(20);
	void *argtable[] = {s, end};
	
	int nerrors = arg_parse(argc, argv, argtable);
	if (nerrors == 0) {
		
		printf("--scalar = %d\n",s->ival[0]);
	}

	
}
