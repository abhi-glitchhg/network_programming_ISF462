#include<stdio.h>
#include<stdlib.h>	
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

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

	printf("enter the port of the server\n");
	scanf("%d", &server_port);

	struct sockaddr_in socket_address; // ipv4
	
	socket_address.sin_family = AF_INET;
	socket_address.sin_port = htons(server_port);
	socket_address.sin_addr.s_addr = inet_addr(server_ip);



	// connect
	int connection_flag = connect(socket_flag, (struct sockaddr *) &socket_address, sizeof(socket_address) );

	if (connection_flag==-1)
		printf(" failed to connect to the server with ip %s/%d", server_ip, server_port);

	printf("connection done baby");	
	


	//take input until the input is quit
	//
	


	// close connection





	return 0;


}
