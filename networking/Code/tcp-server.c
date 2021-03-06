#include	<sys/socket.h> 	/* for socket() and bind() */
#include	<stdio.h>		/* printf() and fprintf() */
#include	<stdlib.h>		/* for atoi() and exit() */
#include	<arpa/inet.h>	/* for sockaddr_in and inet_ntoa() */
#include	<sys/types.h>
#include    <string.h>
#include    <time.h>
#include	<unistd.h>
#include    "message.h"
#include    "playerDBArray.h"
#include    "gameDBArray.h"
#define	ECHOMAX	255		/* Longest string to echo */
#define BACKLOG	128



int registerPlayer(char *playerName,char *ipAddres,char *port);
void selectKplayers( int k,int callerindex);
struct game_Init  game_start(int k,char *callerAddr,char *callerName);
int getID();


struct player playerDB[100];
struct game gameDB[100];
struct player tempPlayerDB[100];

struct player_query pquery();
struct game_query gquery();
struct game_init gameInit();
//char callerIP[16];

void 
DieWithError(const char *errorMessage) /* External error handling function */
{
	perror(errorMessage);
	exit(1);
}


void
msgController(int sockfd,struct sockaddr_in Client)
{
    ssize_t n;
    char line[ECHOMAX];
    char *callerIP=inet_ntoa(Client.sin_addr);
    char callersName[25];

    struct message readMsg;
    struct player_query queryMsg;
    struct game_query gqueryMsg;
    struct game_Init gameMsg;

    if ( (n = read(sockfd, &readMsg, sizeof(struct message))) == 0 )
    {
   	    return; /* connection closed by other end */
    }       
    readMsg.command[ n ] = '\0';            
    printf("Command = %s\n",readMsg.command );

	if(strcmp(readMsg.command,"register") == 0 )
	{
		if(registerPlayer(readMsg.arg1,readMsg.arg2,readMsg.arg3) == 0)
			strcpy(line,"Success");
		else
			strcpy(line,"FAILURE: Player exists");
        
        write(sockfd, line, n );
	}
	if(strcmp(readMsg.command,"queryplayers") == 0 )
	{
		queryMsg=pquery();
       	 write(sockfd, &queryMsg, sizeof(struct player_query) );
	}
    if(strcmp(readMsg.command,"startgame") == 0 )
    {
        int k=atoi(readMsg.arg1);
        strcpy(callersName,caller_Name(playerDB,callerIP));
        gameMsg=game_start(k,callerIP,callersName);
        write(sockfd, &gameMsg, sizeof(struct game_Init) );
    }
    if(strcmp(readMsg.command,"querygames") == 0 )
    {
        gqueryMsg=gquery();
        printf("gquerymsg numbers of games = %d\n",gqueryMsg.numGames);

        write(sockfd, &gqueryMsg, sizeof(struct game_query) );
    }
    if(strcmp(readMsg.command,"end") == 0 )
    {
        if(gameDB_exists(gameDB,readMsg.arg1)==1)
        {
            gameDB_Delete(gameDB,readMsg.arg1);
            strcpy(line,"Success");
        }
        else
            strcpy(line,"FAILURE");

        write(sockfd, line, n );
    }

    if(strcmp(readMsg.command,"deregister") == 0 )
    {
        if(playerSearch(playerDB,readMsg.arg1)==1) 
        {
            playerDB_Delete(playerDB,readMsg.arg1);
            strcpy(line,"Success");
        }
        else
            strcpy(line,"FAILURE");

        write(sockfd, line, n );
    }
    if(strcmp(readMsg.command,"exit") == 0 )
        exit(0);
}



struct player_query pquery()
{
    struct player_query newPQ;
    int numPlayers=playerDB_GetSize(playerDB);
    char pqList[200];

    newPQ.players=numPlayers;
    
    if (numPlayers==0)
        strcpy(newPQ.List,"EMPTY");
    else
        strcpy(newPQ.List,playerDB_List(playerDB));

    return newPQ;
}
struct game_query gquery()
{
    struct game_query newGQ;
    int num_games=gameDB_GetSize(gameDB);
    char gqList[200];

    newGQ.numGames=num_games;
    if (num_games==0)
    {
        strcpy(newGQ.gameList,"EMPTY");
    
    }
    else
        strcpy(newGQ.gameList,gameDB_List(gameDB));

    return newGQ;
}

int
deregisterPlayer(char *playerName)
{
	playerDB_Delete(playerDB,playerName);
	return 1;
}


int
registerPlayer(char *playerName,char *ipAddres,char *port)
{
    struct player newPlayer;
    strcpy(newPlayer.name,playerName);
    strcpy(newPlayer.ip,ipAddres);
    strcpy(newPlayer.port,port);

    int found=0;
    found=playerSearch(playerDB,playerName);
    if(found!=1)
    {
        playerDB_Add(playerDB,newPlayer);
    }
        return found;
}

int game_End(char *gameIdentifier,char *callerAddr)
{
return 0;
}

struct game_Init  game_start(int k,char *callerAddr,char *callerName)
{
	struct game_Init gameInit;

    int numPlayers=playerDB_GetSize(playerDB);
    int callerFound=playerSearch(playerDB,callerName);
    int callIndex=callerIndex(playerDB,callerAddr);

    char newid[20];
    sprintf(newid,"%d",getID());
    struct game newGame;
	if(numPlayers>=k+1 && callerFound==1 )
	{
		selectKplayers(k,callIndex);
        strcpy(newGame.gamePList,playerDB_List(tempPlayerDB));
        strcpy(newGame.gameID,newid);
        newGame.caller=playerDB[callIndex];
        gameDB_Add(gameDB,newGame);

        strcpy(gameInit.response,newGame.gameID);
        strcpy(gameInit.participantList,playerDB_List(tempPlayerDB));
        tempDB_Delete(tempPlayerDB);
	}
    else
    {
        strcpy(gameInit.response,"FAILURE");
        strcpy(gameInit.participantList,"EMPTY");

    }
    
    return gameInit;
}

int getID()
{
    int rando;
    int count=0;
    int flag=1;
    int totalGames=gameDB_GetSize(gameDB);
    srand(time(NULL)); // randomize seed
    int i=0;
    while (flag==1)
    {   
        rando=(rand() % 100);
        flag=0;
        for(int i=0;i<totalGames;i++)
        {
            if(atoi(gameDB[i].gameID) == rando)
                flag=1;
        }   
    }

    return rando;

}

void selectKplayers( int k,int callerindex)
{

    //int callerindex=callerIndex(playerDB,callerAddr);
	int rando;
    int count=0;
	int flag=0;
	int used[k]  ;
	int numPlayers=playerDB_GetSize(playerDB);
	srand(time(NULL)); // randomize seed
    int i=0;
    while (i<k)
	{
        rando=(rand() % numPlayers);
        //printf("rando=%d,count=%d\n", rando,count);
        flag=0;
        if (rando == callerindex)
        {
          //  printf("\nflag=1 not added\n");   
            flag=1;
        }
        else if(i==0 )
        {
            used[i]=rando;
            count++;
            i++;
        }
        else
        {
		  for(int j=0;j<count;j++)
		  {
           //printf("j=%d\n",j);
			if(rando==used[j] )
            {
              // printf("\nflag=1 not added\n");   
				flag=1;
            }
		}
        if(flag==0)
        {
         //   printf("\nflag=0\n");   
	       used[i]=rando;
            count++;
            i++;
        }
    }
	}
    for(int i=0;i<k;i++)
    {
        //tempPlayerDB[i]=playerDB[used[i]];
        playerDB_Add(tempPlayerDB,playerDB[used[i]]);

    //printf("rand[%d]=%d\n",i, used[i]);
    //printf("tempPlayerDB[%d]=%s\n",i, tempPlayerDB[i].name);
    }
	
}

int
main(int argc, char **argv)
{
   strcpy(playerDB[0].name,"Tail");
   strcpy(gameDB[0].gameID,"Tail");
   strcpy(tempPlayerDB[0].name,"Tail");

    int sock, connfd;                
    struct sockaddr_in echoServAddr;
    struct sockaddr_in echoClntAddr;
    unsigned int cliAddrLen;        
    char echoBuffer[ECHOMAX];       
    unsigned short echoServPort;    
    int recvMsgSize;                

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
    msgController(connfd,echoClntAddr);

}
	close(connfd);
}
//*/

