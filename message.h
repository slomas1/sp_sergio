struct player {
  char  name[50];
  char  ip[16];
  char  port[16];
};

struct game {
  char gameID[20];
  struct player caller;
  char gamePList[400];


};
struct game_Init {
  char response[16];// game-ID or Failure
  char participantList[200];
};

struct player_query {
int 	players;
char List[400];
};

struct game_query {
  int  numGames;
  char  gameList[400];
};
struct message {
  char  command[50];
  char  arg1[50];
  char  arg2[50];
  char  arg3[50];
};
/*
struct MinerInformation {
	char userName[30];
	char IP[16];
	char port[6];
  	int command ;
	int initialCoins;
};*/
