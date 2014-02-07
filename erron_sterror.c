#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main()
{
	int fd;
	extern int errno;

	if ( (fd = open("no/such/file",0)) < 0)
	{
		printf("errno = %d\n",errno);
		char *mesg = strerror(errno);
		printf("Mesg:%s\n",mesg);
	}

	return 0;
}
