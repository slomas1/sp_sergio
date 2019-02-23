/*
int gameDB_idGen()
{


}

void gameDB_Add(struct player playerArray[],struct player newPlayer)
{
	
	int size=gameDB_GetSize(playerArray);
	strcpy(playerArray[size+1].name,"Tail");
	playerArray[size]=newPlayer;
}

int gameDB_GetSize(struct player playerArray[])
{
	int i=0;
	while(strcmp(playerArray[i].name,"Tail")!=0)
	{
		i++;
	}
	return i;
}


void gameDB_Print(struct player playerArray[])
{

	int size=gameDB_GetSize(playerArray);
	for(int i=0;i<size;i++)
	{
		printf("playerArray[%d].name=%s\n",i,playerArray[i].name );
		printf("playerArray[%d].ip=%s\n",i,playerArray[i].ip );
		printf("playerArray[%d].port=%s\n",i,playerArray[i].port );
	}
}

void gameDB_Delete(struct player playerArray[],char *deletePlayer)
{
	int size=gameDB_GetSize(playerArray);
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


	//strcpy(playerArray[size+1].name,"Tail");
	//playerArray[size]=newPlayer;
	
}



//void gameDB_List(struct player playerArray[])
char* gameDB_List(struct player playerArray[])
{
	char *text=malloc(100*sizeof(char));
	strcpy(text,"LIST:");
	int size=gameDB_GetSize(playerArray);
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



//*/