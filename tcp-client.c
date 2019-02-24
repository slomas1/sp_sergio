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

//void str_cli(struct message msg, int sockfd)
void
//manager_talk(struct message msg, int sockfd)
//str_cli(FILE *fp, int sockfd)
str_cli( int sockfd)
{
	ssize_t n;
    char    sendline[ECHOMAX], recvline[ECHOMAX];
	struct player_query qmsg;
	struct game_query gqmsg;
	struct game_Init gamemsg;
	struct message msg;
	char cmd;

       //while (fgets(sendline, ECHOMAX, fp) != NULL) 
	   	for(;;)
       	{
       		printf("\nCommand: ");
       		scanf("%s",msg.command);
			//sendline[ n ] = '\0';
       		//printf("comparison = %d\n",strncmp(sendline,recvline,9));
       		if(strncmp(msg.command,"register",9)==0)
       		{
       			printf("Player Name: ");
       			scanf("%s",msg.arg1);
       			printf("IP Address: ");
       			scanf("%s",msg.arg2);
       			printf("Port: ");
       			scanf("%s",msg.arg3);
            	write(sockfd, &msg, sizeof(struct message));

            	if ( (n = read(sockfd, recvline, ECHOMAX)) == 0)
            		DieWithError("str_cli: server terminated prematurely");
               
                printf("\nResponse from server:%s\n",recvline);
       		}
       		else if(strncmp(msg.command,"queryplayers",12)==0)
       		{
            	write(sockfd, &msg, sizeof(struct message));

            	if ( (n = read(sockfd, &qmsg,sizeof(struct player_query) )) == 0)
            		DieWithError("str_cli: server terminated prematurely"); 
                printf("\nResponse from server:\nNumber of players:%d\nPlayers:%s\n",qmsg.players,qmsg.List);
       		}
       		else if(strncmp(msg.command,"startgame",9)==0)
       		{
       			printf("K Players: ");
       			scanf("%s",msg.arg1);
       			write(sockfd, &msg, sizeof(struct message));
       			if ( (n = read(sockfd, &gamemsg,sizeof(struct game_Init) )) == 0)
            		DieWithError("str_cli: server terminated prematurely"); 
                printf("\nResponse from server:%s\nPlayers:%s\n",gamemsg.response,gamemsg.participantList);

       		}
       		else if(strncmp(msg.command,"querygames",10)==0)
       		{
            	write(sockfd, &msg, sizeof(struct message));
            	if ( (n = read(sockfd, &gqmsg,sizeof(struct player_query) )) == 0)
            		DieWithError("str_cli: server terminated prematurely"); 
                printf("\nResponse from server:\nNumber of games:%d\nGames:%s\n",gqmsg.numGames,gqmsg.gameList);

       		}
       		else if(strcmp(msg.command,"exit")==0)
       		{
       			write(sockfd, &msg, sizeof(struct message));
       			exit(0);
       		}
       		else
       			printf("Not Recognized\n");


       		//printf("cmd:%s\narg1:%s\narg2:%s\narg3:%s\n", msg.command,msg.arg1,msg.arg2,msg.arg3);



            //write(sockfd, sendline, strlen(sendline));

            //if ( (n = read(sockfd, recvline, ECHOMAX)) == 0)
            //    DieWithError("str_cli: server terminated prematurely");

        }	

                //WORKING write(sockfd, &msg, sizeof(struct message));
	//	if ( (n = read(sockfd, &msg, sizeof(struct message))) == 0)
	//if(strcmp(msg.command,"register") != 0)
	//{
	//	if ( (n = read(sockfd, &qmsg, sizeof(struct player_query))) == 0)
                //WORKING if ( (n = read(sockfd, recvline, ECHOMAX)) == 0)
                      //WORKING DieWithError("str_cli: server terminated prematurely");
                //write(sockfd, sendline, strlen(sendline));

                //if ( (n = read(sockfd, recvline, ECHOMAX)) == 0)
                //if ( (n = read(sockfd, &msg, ECHOMAX)) == 0)
                //        DieWithError("str_cli: server terminated prematurely");

				//msg[ n ] = '\0';
                //printf("\nresponse from server:\nPlayers = %d\n%s\n",qmsg.players,qmsg.List);
               // printf("\nresponse from server:%s\n",msg.command);
	//}               
                    //WORKING printf("\nresponse from server: %s\n",recvline);
                //fputs(msg, stdout);
        //}
}


void peer_talk()
{


}
int
main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in servaddr;
	struct message in_msg;
	if (argc != 3)
		DieWithError( "usage: tcp-client <Server-IPaddress> <Server-Port>" );
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));	
	
	str_cli(sockfd);		

	exit(0);
}
