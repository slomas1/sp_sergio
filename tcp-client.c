#include        <sys/socket.h>  /* for socket() and bind() */
#include        <stdio.h>               /* printf() and fprintf() */
#include        <stdlib.h>              /* for atoi() and exit() */
#include        <arpa/inet.h>   /* for sockaddr_in and inet_ntoa() */
#include        <sys/types.h>
#include        <string.h>
#include        <unistd.h>
#include		"message.h"

#define ECHOMAX 255             /* Longest string to echo */
#define BACKLOG 128


void
DieWithError(const char *errorMessage) /* External error handling function */
{
        perror(errorMessage);
        exit(1);
}

void
str_cli(struct message msg, int sockfd)
//str_cli(FILE *fp, int sockfd)
{
	ssize_t n;
        char    sendline[ECHOMAX], recvline[ECHOMAX];
	struct player_query qmsg;

       /// while (fgets(sendline, ECHOMAX, fp) != NULL) {

                write(sockfd, &msg, sizeof(struct message));
	//	if ( (n = read(sockfd, &msg, sizeof(struct message))) == 0)
	//	if ( (n = read(sockfd, &qmsg, sizeof(struct player_query))) == 0)
                if ( (n = read(sockfd, recvline, ECHOMAX)) == 0)

                        DieWithError("str_cli: server terminated prematurely");
                //write(sockfd, sendline, strlen(sendline));

                //if ( (n = read(sockfd, recvline, ECHOMAX)) == 0)
                //if ( (n = read(sockfd, &msg, ECHOMAX)) == 0)
                //        DieWithError("str_cli: server terminated prematurely");

				//msg[ n ] = '\0';
                printf("\nresponse from server: %s\n",recvline);
                //printf("\nresponse from server: %s\n",recvline);
                //fputs(msg, stdout);
        //}
}

int
main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in servaddr;
	struct message in_msg;
	strcpy(in_msg.command,"register");
	strcpy(in_msg.arg1,"Sergio");
	strcpy(in_msg.arg2,"192.168.1.69");
	strcpy(in_msg.arg3,"6969");
	if (argc != 3)
		DieWithError( "usage: tcp-client <Server-IPaddress> <Server-Port>" );
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	str_cli(in_msg, sockfd);		/* do it all */
	strcpy(in_msg.command,"query players");
	strcpy(in_msg.arg1,"");
	strcpy(in_msg.arg2,"");
	strcpy(in_msg.arg3,"");
	str_cli(in_msg, sockfd);		/* do it all */
	//str_cli(stdin, sockfd);		/* do it all */

	exit(0);
}
