all : server  peer 

server : 
	gcc -std=c99 -o manager tcp-server.c 
peer :
	gcc -std=c99 -o bingo tcp-client.c 
clean :
	rm -f a.out manager bingo tcp-client tcp-server
