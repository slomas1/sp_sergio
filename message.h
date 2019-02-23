struct player {
  char  name[50];
  char  ip[16];
  char  port[16];
};

struct game {
  char gameID[10];
  struct player caller;
  char gamePList[300];


};
struct game_Init {
  char response[16];// game-ID or Failure
  char participantList[200];
};

struct player_query {
int 	players;
char List[200];
};

struct game_query {
  char  name[50];
  char  ip[16];
  char  port[16];
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
