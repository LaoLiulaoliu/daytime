#define MAXLINE 4096

#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv)
{
	int listenfd, connfd, listenq = 1024;
	struct sockaddr_in servaddr;
	char buff[MAXLINE];
	time_t ticks;
	
	if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket error");
		exit(1);
	}

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(9999);

	if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		printf("bind error");
		exit(1);
	}
	
	if (listen(listenfd, listenq) < 0)
	{
		printf("listen error");
		exit(1);
	}
	
	for ( ; ; )
	{
		if ( (connfd = accept(listenfd, (struct sockaddr *)NULL, NULL)) < 0)
		{
			if (errno == EPROTO || errno == ECONNABORTED)
				continue;
			else
			{
				printf("accept error");
				exit(1);
			}
		}

		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		int i;
		for (i = 0; i < strlen(buff); i++)
			write(connfd, &buff[i], 1);
/*		if (write(connfd, buff, strlen(buff)) != strlen(buff))
		{
			printf("close error");
			exit(1);
		}
*/
		if (close(connfd) == -1)
		{
			printf("close error");
			exit(1);
		}
	}
}
