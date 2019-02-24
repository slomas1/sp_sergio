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



//EchoString(int sockfd)
void
EchoString(int sockfd,struct sockaddr_in Client)
{
    ssize_t n;
    char line[ECHOMAX];
    char *callerIP="192.168.1.3";//inet_ntoa(Client.sin_addr);
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

//printf("IP address is: %s\n", callerIP);   
    printf("Command = %s\n",readMsg.command );

//*
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
        printf("gquerymsg numbers of  games = %d\n",gqueryMsg.numGames);

        write(sockfd, &gqueryMsg, sizeof(struct game_query) );
    }

 //*/
	//registerPlayer(char *playerName,char *ipAddres,char *port)
       // write(sockfd, sendMsg, sizeof(message) );
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
    //printf("gquery entered\n");
    printf("games=%d\n", num_games);
    if (num_games==0)
    {
        strcpy(newGQ.gameList,"EMPTY");
    
}
    else
        strcpy(newGQ.gameList,gameDB_List(gameDB));
        //printf("printlist:%s",gameDB_List(gameDB));
        
        //strcpy(newGQ.gameList,playerDB_List(playerDB));
   // printf("newGQ%s\n",newGQ.gameList );
        //strcpy(newGQ.gameList,gameDB_List(gameDB));
    

    return newGQ;
}

int
deregisterPlayer(char *playerName)
{
    //player
	playerDB_Delete(playerDB,playerName);
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
    found=playerSearch(playerDB,playerName);
    //found=playerSearch(playerName);
    //printf("found= %d\n",found);
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
    //*
	if(numPlayers>=k+1 && callerFound==1 )
	{
		selectKplayers(k,callIndex);
        //printf("dblist=%s\n", playerDB_List(tempPlayerDB));
        strcpy(newGame.gamePList,playerDB_List(tempPlayerDB));
        strcpy(newGame.gameID,newid);//FIX THIS
        newGame.caller=playerDB[callIndex];

        strcpy(gameInit.response,newGame.gameID);
        strcpy(gameInit.participantList,playerDB_List(tempPlayerDB));


	}
    else
    {
        printf("ELSE\n");
        strcpy(gameInit.response,newGame.gameID);
        strcpy(gameInit.participantList,"EMPTY");

    }

	//add game
//*/
return gameInit;
}

int getID()
{
    int rando;
    //int k=20;
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


 
    registerPlayer("playerName3","192.168.1.5","313");
    registerPlayer("playerName3","192.168.1.1","420");
    registerPlayer("playerName2","192.168.1.2","950");
    registerPlayer("Namecaller","192.168.1.3","3313");
    registerPlayer("playerName9","192.168.1.76","955");
    registerPlayer("playerName7","192.168.1.68","952");
 
//printf("\n\n\n\n\n");


//*   
//   struct game_Init ginit;
//   ginit=game_start(3,"192.168.1.3","Namecaller");
   //printf("ginit.response=%s\n",ginit.response);
   //printf("ginit.participantList=%s\n",ginit.participantList);

   struct game testGame;
   strcpy(testGame.gameID,"0");
   testGame.caller=playerDB[3];
   strcpy(testGame.gamePList,"ginit.participantList");
//
   struct game testGame2;
   strcpy(testGame2.gameID,"2");
   testGame2.caller=playerDB[4];
   strcpy(testGame2.gamePList,"participantList2");
//
   struct game testGame3;
   strcpy(testGame3.gameID,"3");
   testGame3.caller=playerDB[1];
   strcpy(testGame3.gamePList,"participantList3");

   struct game testGame4;
   strcpy(testGame4.gameID,"4");
   testGame4.caller=playerDB[0];
   strcpy(testGame4.gamePList,"participantList4");

printf("\n\n\n\n\n");
   gameDB_Add(gameDB,testGame);
   gameDB_Add(gameDB,testGame2);
   gameDB_Add(gameDB,testGame3);
   
//   gameDB_Print(gameDB);
   
//    gameDB_Delete(gameDB,"testID_2");
//printf("\n\n\n\n\n");
//  gameDB_Print(gameDB);

   gameDB_Add(gameDB,testGame4);

//printf("\n\n\n\n\n");
   //printf("\n\nPRINTING\n");
   //gameDB_Print(gameDB);


//*/
//struct game_query testgq;
//    gquery();
printf("\n\n\n\n\n");
//printf("numgames=%d\n",testgq.numGames);
printf("numgames=%d\n",gquery().numGames);



 }  /*/UNCOMMENT FOR DEBUG



    int sock, connfd;                
    struct sockaddr_in echoServAddr;
    struct sockaddr_in echoClntAddr;
    unsigned int cliAddrLen;        
    char echoBuffer[ECHOMAX];       
    unsigned short echoServPort;    
    int recvMsgSize;                

    //struct message client_message;

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

//printf("IP address is: %s\n", inet_ntoa(echoClntAddr.sin_addr));
//printf("port is: %d\n", (int) ntohs(echoClntAddr.sin_port));


for(;;)
{
    EchoString(connfd,echoClntAddr);
//
//	EchoString(connfd);


printf("EXIT ECHO STRING\n");
//    if ( (n = read(sockfd, &readMsg, sizeof(struct message))) == 0 )
//        exit(0);

}
	close(connfd);
}
//*/

