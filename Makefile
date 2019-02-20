all : server  peer 

server : 
	gcc -o manager tcp-server.c 
peer :
	gcc -o client tcp-client.c 
clean :
	rm  manager client message tcp-client tcp-server
