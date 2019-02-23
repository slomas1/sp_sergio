int playerDB_GetSize(struct player playerArray[])
{
	int i=0;
	while(strcmp(playerArray[i].name,"Tail")!=0)
	{
		i++;
	}
	return i;
}
void playerDB_Add(struct player playerArray[],struct player newPlayer)
{
	
	int size=playerDB_GetSize(playerArray);
	strcpy(playerArray[size+1].name,"Tail");
	playerArray[size]=newPlayer;
}

void playerDB_Print(struct player playerArray[])
{

	int size=playerDB_GetSize(playerArray);
	for(int i=0;i<size;i++)
	{
		printf("playerArray[%d].name=%s\n",i,playerArray[i].name );
		printf("playerArray[%d].ip=%s\n",i,playerArray[i].ip );
		printf("playerArray[%d].port=%s\n",i,playerArray[i].port );
	}
}

void playerDB_Delete(struct player playerArray[],char *deletePlayer)
{
	int size=playerDB_GetSize(playerArray);
	int playerDeleted=0;
	struct player temp;
	for(int i=0;i<size;i++)
	{
		temp=playerArray[i+1];
		if(playerDeleted==1)
		{
			printf("Player already deleted");
			playerArray[i]=temp;
		}
		if(strcmp(playerArray[i].name,deletePlayer)==0)
		{
			printf("playerArray[%d] = %s\n",i,playerArray[i].name);
			playerArray[i]=temp;
			playerDeleted=1;
		}
	}
}



//void playerDB_List(struct player playerArray[])
char* playerDB_List(struct player playerArray[])
{
	char *text=malloc(100*sizeof(char));
	strcpy(text,"LIST:");
	int size=playerDB_GetSize(playerArray);
	for(int i=0;i<size;i++)
	{
		strcat(text,"(");
		strcat(text,playerArray[i].name);
		strcat(text,",");
		strcat(text,playerArray[i].ip);
		strcat(text,",");
		strcat(text,playerArray[i].port);
		strcat(text,")");
		if(i!=size-1)
			strcat(text,",");

		//printf("playerArray[%d].name=%s\n",i,playerArray[i].name );
		//printf("playerArray[%d].ip=%s\n",i,playerArray[i].ip );
		//printf("playerArray[%d].port=%s\n",i,playerArray[i].port );
	}
return text;
//	return rtnPtr;
}

int 
playerSearch(struct player playerArray[], char *playerName)
{
    //printf("Entered playerSearch\n");
    int numPlayers=playerDB_GetSize(playerArray);
    int foundPS=0;
    //printf("get size complete\n");
    if (numPlayers>0)
    {
    	for(int i=0;i<numPlayers;i++)
        {
            if(strcmp(playerArray[i].name,playerName)==0)
                foundPS=1;
        }
    }
        //printf("numPlayers=%d\n",numPlayers );
        return foundPS;//1 is FOUND
}

int 
callerIndex(struct player playerArray[], char *callerIP)
{
	int numPlayers=playerDB_GetSize(playerArray);
    int callerIndex=0;
    if (numPlayers>0)
    {
    	for(int i=0;i<numPlayers;i++)
        {
            if(strcmp(playerArray[i].ip,callerIP)==0)
                callerIndex=i;
        }
    }

    return callerIndex;
}
