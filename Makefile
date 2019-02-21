all : server  peer 

server : 
	gcc -o manager tcp-server.c 
peer :
	gcc -o bingo tcp-client.c 
clean :
	rm -f a.out manager bingo tcp-client tcp-server
