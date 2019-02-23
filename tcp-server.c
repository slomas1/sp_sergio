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
struct player_query pquery();
struct player playerDB[100];
//struct player gameDB[100];
//char callerIP[16];
void 
DieWithError(const char *errorMessage) /* External error handling function */
{
	perror(errorMessage);
	exit(1);
}



//EchoString(int sockfd,struct sockaddr_in Client)
void
EchoString(int sockfd)
{
    ssize_t n;
    char    line[ECHOMAX];
    struct message readMsg;
    struct player_query queryMsg;

      // printf("Enter ECHOSTRING\n");
	//    if ( (n = read(sockfd, line, ECHOMAX)) == 0 )

        if ( (n = read(sockfd, &readMsg, sizeof(struct message))) == 0 )
        {
   	    	return; /* connection closed by other end */
        }
        
        readMsg.command[ n ] = '\0';            

//printf("IP address is: %s\n", inet_ntoa(Client.sin_addr));
  //char *callerIP=inet_ntoa(Client.sin_addr);
//printf("IP address is: %s\n", callerIP);
       
    printf("Command = %s\n",readMsg.command );
    printf("arg1 = %s\n",readMsg.arg1 );

//*
	if(strcmp(readMsg.command,"register") == 0 )
	{
		if(registerPlayer(readMsg.arg1,readMsg.arg2,readMsg.arg3) == 0)
			strcpy(line,"Success");
		else
			strcpy(line,"Player exists");
	}
	if(strcmp(readMsg.command,"query players") == 0 )
	{
		queryMsg=pquery(playerDB);
       	 	write(sockfd, &queryMsg, sizeof(struct player_query) );
	}
    if(strcmp(readMsg.command,"start game") == 0 )
    {

        //queryMsg=pquery();
          //  write(sockfd, &queryMsg, sizeof(struct player_query) );
    }

 //*/



            strcpy(line,"Success");



	//registerPlayer(char *playerName,char *ipAddres,char *port)
        write(sockfd, line, n );
       // write(sockfd, sendMsg, sizeof(message) );
}


//struct player_query pquery()
struct player_query pquery(struct player playerArray[])
{
    struct player_query newPQ;
    int numPlayers=playerDB_GetSize(playerArray);
    char pqList[200];

    newPQ.players=numPlayers;
    
    if (numPlayers==0)
     strcpy(newPQ.List,"EMPTY");
    else
    {
        //printf("pDB_ListV\n%s\n",playerDB_List(playerDB) );
     strcpy(newPQ.List,playerDB_List(playerArray) );
        //strcpy(newPQ.List,playerDB_List(playerDB));


     //strcpy(newPQ.List,"not EMPTY");
        //strcpy(pqList
    //strcat(pqList,'('')');
    
    }


    //strcpy(newPQ.List,pqList);
    return newPQ;
}


int
deregisterPlayer(char *playerName)
{
    //player
	//playerDB_Delete(playerDB,playerName);
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
    //printf("found complete\n");
    if(found!=1)
    {
        playerDB_Add(playerDB,newPlayer);
    }


        return found;
}

void
game_start(int k,char *caller)
{
	int numPlayers=playerDB_GetSize(playerDB);
    int callerFound=playerSearch(playerDB,caller);/*
	if(numPlayers>=k+1 && callerFound==1 )
	{
		selectKplayers
	}
	//add game
*/

}

void selectKplayers(int k)
{
	int rando;
    int count=0;
	int flag=0;
	int used[k]  ;
	int numPlayers=6;//playerDB_GetSize(playerDB);
	srand(time(NULL)); // randomize seed
int i=0;
    while (i<k)
	{
        rando=(rand() % numPlayers);
        printf("rando=%d,count=%d\n", rando,count);

        flag=0;

        //if(i==0)
        //{
            used[i]=rando;
            count++;
            i++;
        //}
        //else
        {
		  for(int j=0;j<count;j++)
		  {
			if(rando==used[j]  )
            {
                printf("\nflag=1\nnot added\n");   
				flag=1;
            }
		}
        if(flag==0)
        {
            printf("\nflag=0\n");   
	       used[i]=rando;
            count++;
            i++;
        }

    }
				
		
    	//printf("rand[%d]=%d\n",i, used[i]);
        /// printf("rand=%d\n", rand()%numPlayers);
	}
        for(int i=0;i<k;i++)
    {
    printf("rand[%d]=%d\n",i, used[i]);
    }
	
}

int
main(int argc, char **argv)
{
   strcpy(playerDB[0].name,"Tail");
//strcpy(callerIP,"192.168.1.3");//delete
//printf("test\n");
    registerPlayer("playerName3","192.168.1.5","313");
    registerPlayer("playerName1","192.168.1.1","420");
    registerPlayer("playerName2","192.168.1.2","950");
    registerPlayer("playerName4","192.168.1.3","3313");
    registerPlayer("playerName9","192.168.1.76","955");
    registerPlayer("playerName7","192.168.1.68","952");

    printf("callerID =%d\n" ,callerIndex(playerDB,"192.168.1.3"));
	//selectKplayers(4);
//int specialindex=callerIndex(playerDB,callerIP);

//	int size=10;
//srand(time(NULL)); // randomize seed
//for(int i=0;i<size;i++)
 //   printf("rand=%d\n", rand()%size);
}



/*   strcpy(playerDB[0].name,"Tail");
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
//   */

/*

    int sock, connfd;                
    struct sockaddr_in echoServAddr;
    struct sockaddr_in echoClntAddr;
    unsigned int cliAddrLen;        
    char echoBuffer[ECHOMAX];       
    unsigned short echoServPort;    
    int recvMsgSize;                

    struct message client_message;

printf("declares\n");
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


    EchoString(connfd,echoClntAddr);
/*
for(;;)
{
	EchoString(connfd);
}
/

printf("EXIT ECHO STRING\n");

	close(connfd);
char str[50];
strcpy(str,"test");
    //printf("registered players = %d",registerPlayer(str));
	//playerSearch(str);
}
//*/

