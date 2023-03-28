#include<stdio.h>
#include<stdlib.h>	
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
int main(){

	char server_ip[16];
//	char server_port[5];
	//create a socket
	int server_port;
	int socket_flag = socket(AF_INET, SOCK_STREAM,0);


	if (socket_flag==-1)
		printf("socket flag is -1");	


	//take input for the ip of the server
	printf("enter the server Ip address\n");
	scanf("%s", server_ip);
	server_ip[strcspn(server_ip, "\n")] = 0;

	printf("enter the port of the server\n");
	scanf("%d", &server_port);

	struct sockaddr_in socket_address; // ipv4
	
	socket_address.sin_family = AF_INET;
	socket_address.sin_port = htons(server_port);
	socket_address.sin_addr.s_addr = inet_addr(server_ip);

	    if(inet_pton(AF_INET,server_ip ,&socket_address.sin_addr) < 1){
        	perror("client: inet_pton() error ->");
        	exit(EXIT_FAILURE);
    }


	// connect
	int connection_flag = connect(socket_flag, (struct sockaddr *) &socket_address, sizeof(socket_address) );

	if (connection_flag<0)
		perror(" failed to connect to the server");

	char string_buffer[1024];
	char stopword[1024];
	stopword[0] = 'q'; stopword[1] = 'u' ; stopword[2] = 'i' ; stopword[3] ='t' ;
	 printf(" eneter words here; to stop enter 'quit \n: ");
	 
	 while (strcmp(string_buffer, stopword)){
	
		scanf("%s", string_buffer);
		if (write(socket_flag, &string_buffer, 1024) <0)
			perror("error while writing data to the socket.");


	
	 }


	 close(socket_flag);

	//take input until the input is quit
		


	// close connection





	return 0;


}
