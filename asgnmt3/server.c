#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>
#include<pthread.h>

// handle the threading logic 
void* handle_connection(int* p_client){
	int client_loc = *p_client;
	free(p_client);

	char buff[1024];
	size_t bytes_read; 
	while (bytes_read = read(client_loc, buff, 1024)){
		buff[bytes_read-1] = 0; // remove the new line character and replace with stop  
		if (bytes_read==5)
			// check if the word is quit
			if (buff[0]=='q' && buff[1] =='u' && buff[2]=='i' && buff[4] =='t')
				{
					close(client_loc); 
					return NULL;
				}
		printf("%s", buff);
	}
	return NULL;


	
}

int main(){

	
	struct sockaddr_in client_address;
    	socklen_t client_address_len = sizeof(client_address);
 	int client_socket;	

	int server_port;
	struct sockaddr_in server_address; // ipv4
					   //
	server_address.sin_family = AF_INET; 
	server_address.sin_addr.s_addr = INADDR_ANY;
	// take user input for the server ip and port;
	printf(" give port address \n");

	scanf("%d", &server_port);

	server_address.sin_port = htons(server_port);


	int socket_flag = socket(AF_INET, SOCK_STREAM,0 );

	if (socket_flag<0)
		perror("unable to create socket \n");



	int binding_status = bind(socket_flag, (struct sockaddr *) &server_address, sizeof(server_address));
	if (binding_status <0)
		perror( "error while binding \n");

	int listening_status = listen(socket_flag, 10);
     	if (listening_status <0)
		perror("Server is unable to listen :( \n");

	printf("Server listening on %d\n", server_port);

	while (true){
	
		// accept a new connection
		printf("waiting for a connection \n");

		client_socket = accept(
				socket_flag , (struct sockaddr *)&client_address,sizeof(client_address) );
		if (client_socket<0)
			perror("Error while accepting incoming connections : \n");
		printf("connected with one of the incoming connection");

		pthread_t t;
		int * pclient = malloc(sizeof(int));
		*pclient = client_socket;
		//
		pthread_create(&t, NULL ,handle_connection, pclient);
		// spawn a  new thread for the same;
		//
		//
	
	}
	return 0;
}




