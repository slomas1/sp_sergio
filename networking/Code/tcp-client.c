//Sergio Lomas
//Group27
#include        <sys/socket.h>  /* for socket() and bind() */
#include        <stdio.h>               /* printf() and fprintf() */
#include        <stdlib.h>              /* for atoi() and exit() */
#include        <arpa/inet.h>   /* for sockaddr_in and inet_ntoa() */
#include        <sys/types.h>
#include        <string.h>
#include        <strings.h>
#include        <unistd.h>
#include        <time.h>
#include        <unistd.h>
#include		"message.h"

#define ECHOMAX 255             /* Longest string to echo */
#define BACKLOG 128

int bingoCard[5][5];
int markCard[5][5];



int squareNumber();
void cardGen();
void
DieWithError(const char *errorMessage) /* External error handling function */
{
        perror(errorMessage);
        exit(1);
}

void str_cli( int sockfd)
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
                printf("\nResponse from server:\nNumber of players:%d\nPlayers:\n%s\n",qmsg.players,qmsg.List);
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
       		else if(strncmp(msg.command,"deregister",10)==0)
       		{
       			printf("Name: ");
       			scanf("%s",msg.arg1);
            	write(sockfd, &msg, sizeof(struct message));       			
       		}
       		else if(strncmp(msg.command,"gencard",7)==0)
       		{
       			cardGen();
       		}
       		else if(strcmp(msg.command,"help")==0)
       		{
       			printf("\nHELP:Type any of the commands seen below\nregister\t- This will register a new player\nqueryplayers\t- This will query for players that have been registered\nstartgame\t- This will attempt to start a new game\nquerygames\t- This will query for the games currently being played\ngencard\t\t- Generate a bingo card\nexit\t\t- This will close the manager and client connected to it\n");
       		}
       		else if(strcmp(msg.command,"exit")==0)
       		{
       			write(sockfd, &msg, sizeof(struct message));
       			exit(0);
       		}

        }	

}




int BINGO()
{
		return 1;
}
void cardFill(char *calledNum)
{
	int callednumber=4;


	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(callednumber==bingoCard[i][j])
				markCard[i][j]=1;	
		}
	}
}

int winCheck()
{
	int win=0;
	int b,i,n,g,o;
	int i1,i2,i3,i4,i5;
	b=0;i=0;n=0;g=0;o=0;
	i1=0;i2=0;i3=0;i4=0;i5=0;

	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(i==0 && markCard[4][j]==1)
				i1++;
			if(i==1 && markCard[4][j]==1)
				i2++;
			if(i==2 && markCard[4][j]==1)
				i3++;
			if(i==3 && markCard[4][j]==1)
				i4++;
			if(i==4 && markCard[4][j]==1)
				i5++;

			if(j==0 && markCard[i][0]==1)
				b++;
			if(j==1 && markCard[i][1]==1)
				i++;
			if(j==2 && markCard[i][2]==1)
				n++;
			if(j==3 && markCard[i][3]==1)
				g++;
			if(j==4 && markCard[i][4]==1)
				o++;
		}
	}
	if(i1>=5)	
		win=1;
	if(i2>=5)	
		win=1;
	if(i3>=5)	
		win=1;
	if(i4>=5)	
		win=1;
	if(i5>=5)	
		win=1;
	if(b>=5)	
		win=1;
	if(i>=5)	
		win=1;
	if(n>=5)	
		win=1;
	if(g>=5)	
		win=1;
	if(o>=5)	
		win=1;
	if(markCard[0][0]==1 && markCard[1][1]==1 && markCard[3][3]==1 && markCard[4][4]==1)
		win=1;
	if(markCard[4][0]==1 && markCard[3][1]==1 && markCard[1][3]==1 && markCard[0][4]==1)
		win=1;

	return win;
}
void cardGen()	
{

	int squareVal;
	int flag=1;
	
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{

			if(i==2 && j==2)
			{
				bingoCard[2][2]=0;
			}
			else
			{
				flag=1;
				while(flag==1)
				{
					squareVal=squareNumber();
					flag=0;
					switch(j)
					{
						case 0:  
						break;
						case 1: squareVal+=15;
						break;
						case 2:  squareVal+=30;
						break;
						case 3: squareVal+=45;
						break;
						case 4: squareVal+=60;
						break;
					}
					for(int k=0;k<5;k++)
					{
						for(int l=0;l<5;l++)
						{
						if(squareVal==bingoCard[k][l])
							flag=1;
							
						}
					}
				}
				bingoCard[i][j]=squareVal;
			
			}
		}
	}
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			printf("[%d]",bingoCard[i][j]);
		}
		printf("\n");
	}

}
int squareNumber()
{
	int rando;
    int flag=1;
    srand(time(NULL)); // randomize seed
    int i=0;
    while (flag==1)
    {   
        rando=(rand() % 15);
        flag=0; 
    }

    return rando+1;
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
	markCard[2][2]=1;

	str_cli(sockfd);		
	exit(0);
}
