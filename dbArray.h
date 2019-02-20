//m#include <string>
//#include <cstring>
//using namespace std;
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
		strcat(text,",");

		//printf("playerArray[%d].name=%s\n",i,playerArray[i].name );
		//printf("playerArray[%d].ip=%s\n",i,playerArray[i].ip );
		//printf("playerArray[%d].port=%s\n",i,playerArray[i].port );
	}
return text;
//	return rtnPtr;
}



/*
int playerDB_GetSize(struct player playerArray[])
{
	int i=0;
	while(strcmp(playerArray[i].name,"Tail")!=0)
	{
		i++;
	}
	return i;
}
int playerDB_Add(struct player playerArray[],struct player newPlayer)
{
	int size=getdbSize(playerArray);
	strcpy(playerArray[size+1].name,"Tail");
	playerArray[size]=newPlayer;

}
void playerDB_Print(struct player playerArray[],struct player newPlayer)
{
	int size=getdbSize(playerArray);
	for(int i=0;i<size;i++)
	{
		printf("playerArray[%d].name=%s\n",i,playerArray[i].name );
		printf("i=%d\n",i );
	}

}*/