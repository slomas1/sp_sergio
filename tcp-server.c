#include	<sys/socket.h> 	/* for socket() and bind() */
#include	<stdio.h>		/* printf() and fprintf() */
#include	<stdlib.h>		/* for atoi() and exit() */
#include	<arpa/inet.h>	/* for sockaddr_in and inet_ntoa() */
#include	<sys/types.h>
#include    <string.h>
#include	<unistd.h>
#include    "message.h"
#include    "dbArray.h"
#define	ECHOMAX	255		/* Longest string to echo */
#define BACKLOG	128


int registerPlayer(char *playerName,char *ipAddres,char *port);
struct player_query pquery();
struct player playerDB[100];
//char *pqList[500];

void 
DieWithError(const char *errorMessage) /* External error handling function */
{
	perror(errorMessage);
	exit(1);
}



void
EchoString(int sockfd)
{
    ssize_t n;
    char    line[ECHOMAX];
    struct message readMsg;
    struct player_query queryMsg;

      // printf("Enter ECHOSTRING\n");
	//    if ( (n = read(sockfd, line, ECHOMAX)) == 0 )
//        printf("DEBUG \n");

        if ( (n = read(sockfd, &readMsg, sizeof(struct message))) == 0 )
        {
 //       printf("DEBUG2 \n");
   	    	return; /* connection closed by other end */
        }
   //     printf("DEBUG3 \n");
        
        readMsg.command[ n ] = '\0';            
       printf("Command = %s\n",readMsg.command );
        printf("arg1 = %s\n",readMsg.arg1 );


	if(strcmp(readMsg.command,"register") == 0 )
	{
//	printf("\nCommand = %s",readMsg.command);
		if(registerPlayer(readMsg.arg1,readMsg.arg2,readMsg.arg3) == 0)
			strcpy(line,"Success");
		else
			strcpy(line,"Player exists");
	}
	if(strcmp(readMsg.command,"query players") == 0 )
	{
	//printf("\nCommand = %s",readMsg.command);
		queryMsg=pquery();
//			strcpy(line,"Query Success");
       	 	write(sockfd, &queryMsg, sizeof(struct player_query) );
	}
	//registerPlayer(char *playerName,char *ipAddres,char *port)
  //      write(sockfd, line, n );
       // write(sockfd, sendMsg, sizeof(message) );
}


struct player_query 
pquery()
{
    struct player_query newPQ;
    int numPlayers=playerDB_GetSize(playerDB);
    char pqList[200];

    newPQ.players=numPlayers;
    
    if (numPlayers==0)
     strcpy(newPQ.List,"EMPTY");
    else
    {
        //printf("pDB_ListV\n%s\n",playerDB_List(playerDB) );
     strcpy(newPQ.List,playerDB_List(playerDB) );
        //strcpy(newPQ.List,playerDB_List(playerDB));


     //strcpy(newPQ.List,"not EMPTY");
        //strcpy(pqList
    //strcat(pqList,'('')');
    
    }


    //strcpy(newPQ.List,pqList);
    return newPQ;
}
int 
playerSearch(char *playerName)
{
    //printf("Entered playerSearch\n");
    int numPlayers=playerDB_GetSize(playerDB);
    int foundPS=0;
    //printf("get size complete\n");
    if (numPlayers>0)
    {
    	for(int i=0;i<numPlayers;i++)
        {
            if(strcmp(playerDB[i].name,playerName)==0)
                foundPS=1;
        }
    }
        //printf("numPlayers=%d\n",numPlayers );
        return foundPS;//NOT FOUND
}


int
deregisterPlayer(char *playerName)
{
	
	return 1;
}


int
registerPlayer(char *playerName,char *ipAddres,char *port)
{
    //printf("Entered registerPlayer\n");
    struct player newPlayer;
    strcpy(newPlayer.name,playerName);
    strcpy(newPlayer.ip,ipAddres);
    strcpy(newPlayer.port,port);

    int found=0;
    found=playerSearch(playerName);
    //printf("found complete\n");
    if(found!=1)
    {
        playerDB_Add(playerDB,newPlayer);
    }


        return found;
}

int
main(int argc, char **argv)
{
    strcpy(playerDB[0].name,"Tail");
    registerPlayer("playerName1","192.168.1.1","420");
    registerPlayer("playerName2","192.168.1.2","950");
    registerPlayer("playerName3","192.168.1.3","313");
    //playerDB_Print(playerDB);
    //printf("Players=%d\n%s\n",pquery().players,pquery().List);
    //pquery();
    playerDB_Print(playerDB);
printf("\n\n");
    playerDB_Delete(playerDB,"playerName2");
    registerPlayer("playerName4","192.168.1.4","32");
printf("\n\n");
    playerDB_Print(playerDB);
    registerPlayer("playerName5","192.168.1.5","333");
printf("\n\n");
    playerDB_Print(playerDB);
}
/*
    int sock, connfd;                
    struct sockaddr_in echoServAddr;
    struct sockaddr_in echoClntAddr;
    unsigned int cliAddrLen;        
    char echoBuffer[ECHOMAX];       
    unsigned short echoServPort;    
    int recvMsgSize;                

    struct message client_message;

    if (argc != 2)         
    {
        fprintf(stderr,"Usage: %s <TDP SERVER PORT>\n", argv[0]);
        exit(1);
    }

    echoServPort = atoi(argv[1]); 

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        DieWithError("server: socket() failed");

    memset(&echoServAddr, 0, sizeof(echoServAddr));
    echoServAddr.sin_family = AF_INET;             
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    echoServAddr.sin_port = htons(echoServPort);     

    if (bind(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("server: bind() failed");
  
	if (listen(sock, BACKLOG) < 0 )
		DieWithError("server: listen() failed");

	cliAddrLen = sizeof(echoClntAddr);
	connfd = accept( sock, (struct sockaddr *) &echoClntAddr, &cliAddrLen );


for(;;)
{
	EchoString(connfd);
}
printf("EXIT ECHOSTRING");

	close(connfd);
char str[50];
strcpy(str,"test");
    //printf("registered players = %d",registerPlayer(str));
	//playerSearch(str);
}
//*/

