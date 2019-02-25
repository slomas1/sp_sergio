#include        <sys/socket.h>  /* for socket() and bind() */
#include        <stdio.h>               /* printf() and fprintf() */
#include        <stdlib.h>              /* for atoi() and exit() */
#include        <arpa/inet.h>   /* for sockaddr_in and inet_ntoa() */
#include        <sys/types.h>
#include        <string.h>
#include        <time.h>
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
       		printf("\nType help to get a list of commands\n");
	   	for(;;)
       	{
       		printf("\nCommand: ");
       		scanf("%s",msg.command);
			//sendline[ n ] = '\0';
       		//printf("comparison = %d\n",strncmp(sendline,recvline,9));
       		if(strncmp(msg.command,"register",8)==0)
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
                printf("\nGame Identifier from server:%s\nPlayers:\n%s\n",gamemsg.response,gamemsg.participantList);

       		}
       		else if(strncmp(msg.command,"querygames",10)==0)
       		{
            	write(sockfd, &msg, sizeof(struct message));
            	if ( (n = read(sockfd, &gqmsg,sizeof(struct player_query) )) == 0)
            		DieWithError("str_cli: server terminated prematurely"); 
                printf("\nResponse from server:\nNumber of games:%d\nGames:\n%s\n",gqmsg.numGames,gqmsg.gameList);

       		}
       		else if(strcmp(msg.command,"end")==0)
       		{
       			printf("GameID: ");
       			scanf("%s",msg.arg1);
            	write(sockfd, &msg, sizeof(struct message));
            	if ( (n = read(sockfd, recvline, ECHOMAX)) == 0)
            		DieWithError("str_cli: server terminated prematurely");
                printf("\nResponse from server:%s\n",recvline);

       		}
       		if(strncmp(msg.command,"deregister",10)==0)
       		{
       			printf("Name: ");
       			scanf("%s",msg.arg1);
            	write(sockfd, &msg, sizeof(struct message));       			
            	
       		}
       		else if(strcmp(msg.command,"help")==0)
       		{
       			printf("\nHELP:Type any of the commands seen below\nregister\t- This will register a new player\nqueryplayers\t- This will query for players that have been registered\nstartgame\t- This will attempt to start a new game\nquerygames\t- This will query for the games currently being played\nexit\t\t- This will close the manager and client connected to it\n");
       		}
       		else if(strcmp(msg.command,"exit")==0)
       		{
       			write(sockfd, &msg, sizeof(struct message));
       			exit(0);
       		}
       		else
       			printf("Not Recognized\n");

        }	

}


void peer_talk()
{


}
int getnumber()
{
    int rando;
    //int k=20;
    //int count=0;
    //int flag=1;
    //int totalGames=gameDB_GetSize(gameDB);
    srand(time(NULL)); // randomize seed
    int i=0;
        rando=(rand() % 10);

    return rando;

}

void BINGO()
{
	char result[30];
	while(strcmp(result,"Winner")!=0)
	{
	if(getnumber() == 7)
		strcpy(result,"Winner");
	else
		strcpy(result,"no Winner");

		printf("Result:%s\n",result);
	}
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

//BINGO();
	exit(0);
}
