//Sergio Lomas
//Group27
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
			gameArray[i]=temp;

		}
		if(strcmp(gameArray[i].gameID,deleteGameID)==0)
		{
			gameArray[i]=temp;
			gameDeleted=1;
			
		}
	}
}

char* gameDB_List(struct game gameArray[])
{
	char *gtext=malloc(400*sizeof(char));
	strcpy(gtext,"");
	int size=gameDB_GetSize(gameArray);
	for(int i=0;i<size;i++)
	{
		strcat(gtext,"(");
		strcat(gtext,gameArray[i].gameID);
		strcat(gtext,",");
		strcat(gtext,gameArray[i].caller.name);
		strcat(gtext,",\n");
		strcat(gtext,gameArray[i].gamePList);
		strcat(gtext,")");
		if(i!=size-1)
		{
			strcat(gtext,"\n\n");
		}

	}
	return gtext;
}
int gameDB_exists(struct game gameArray[], char *game_id)
{
	int size=gameDB_GetSize(gameArray);
	int found=0;
	for(int i=0;i<size;i++)
	{
		if(strcmp(gameArray[i].gameID,game_id)==0)
			found=1;
	}

	return found;
}

