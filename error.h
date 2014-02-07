#include <stdio.h>
#include <stdlib.h>

void err_sys(const char *n)
{
	fprintf(stderr,"%s\n",n);
	exit(1);
}
