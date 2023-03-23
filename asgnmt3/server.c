#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main(){

	// take user input for the server ip and port;
	//
	char server_ip[16];
	printf(" give ip address for the server to host \n");

	scanf("%s", server_ip);
	server_ip[strcspn(server_ip, "\n")] =0;
	printf(" give port address \n");

	int server_port;
	scanf("%d", &server_port);

	int socket_flag = socket(AF_INET, SOCK_STREAM,0 );

	if (socket_flag==-1)
		printf("unable to create socket");

	struct sockaddr_in server_address; // ipv4
					   //
	server_address.sin_family = AF_INET; 
	server_address.sin_port = htons(server_port);
	server_address.sin_addr.s_addr = inet_addr(server_ip);


	int binding_status = bind(socket_flag, (struct sockaddr *) &server_address, sizeof(server_address));
	if (binding_status ==-1)
		printf( "error while binding");

	int listening_status = listen(socket_flag, 10);
	
	printf("Server listening on %s:%d\n", server_ip, server_port);
	
	
	struct sockaddr_in client_address;
    	socklen_t client_address_len = sizeof(client_address);

    	int client_socket = accept(socket_flag, (struct sockaddr *)&client_address, &client_address_len);
    	
	if (client_socket < 0) {
        	perror("Error accepting connection");
        	exit(EXIT_FAILURE);
    	}

	return 0;

}


// add logic here to handle the threaded code; aka handling the client;

int func( int accept){
	return 0;

}
