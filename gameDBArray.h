int gameDB_GetSize(struct game gameArray[])
{
	int i=0;
	while(strcmp(gameArray[i].gameID,"Tail")!=0)
	{
		i++;
	}
	return i;
}

void gameDB_Add(struct game gameArray[],struct game newGame)
{
	
	int size=gameDB_GetSize(gameArray);
	strcpy(gameArray[size+1].gameID,"Tail");
	gameArray[size]=newGame;
}

void gameDB_Print(struct game gameArray[])
{

	int size=gameDB_GetSize(gameArray);
	for(int i=0;i<size;i++)
	{
		printf("gameArray[%d].name=%s\n",i,gameArray[i].gameID );
		printf("gameArray[%d].caller=%s\n",i,gameArray[i].caller.name );
		printf("gameArray[%d].gameplayerlist=%s\n",i,gameArray[i].gamePList );
	}
}

void gameDB_Delete(struct game gameArray[],char *deleteGameID)
{
	int size=gameDB_GetSize(gameArray);
	int gameDeleted=0;
	struct game temp;
	for(int i=0;i<size;i++)
	{
		temp=gameArray[i+1];
		if(gameDeleted==1)
		{
	printf("Game already deleted\n");
			gameArray[i]=temp;

		}
		if(strcmp(gameArray[i].gameID,deleteGameID)==0)
		{
			printf("gameArray[%d] = %s\n",i,gameArray[i].gameID);
			gameArray[i]=temp;
			gameDeleted=1;
			
		}
	}
	//strcpy(gameArray[size+1].name,"Tail");
	//gameArray[size]=newPlayer;
}
/*
int gameDB_idGen()
{


}


//void gameDB_List(struct game gameArray[])
char* gameDB_List(struct game gameArray[])
{
	char *text=malloc(100*sizeof(char));
	strcpy(text,"LIST:");
	int size=gameDB_GetSize(gameArray);
	for(int i=0;i<size;i++)
	{
		strcat(text,"(");
		strcat(text,gameArray[i].name);
		strcat(text,",");
		strcat(text,gameArray[i].ip);
		strcat(text,",");
		strcat(text,gameArray[i].port);
		strcat(text,")");
		if(i!=size-1)
			strcat(text,",");

		//printf("gameArray[%d].name=%s\n",i,gameArray[i].name );
		//printf("gameArray[%d].ip=%s\n",i,gameArray[i].ip );
		//printf("gameArray[%d].port=%s\n",i,gameArray[i].port );
	}
return text;
//	return rtnPtr;
}



//*/