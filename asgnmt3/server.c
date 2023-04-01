#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>
#include<pthread.h>

#define MATCHPATTERN "127.*"
#define SHELLSCRIPT1 " ifconfig  | grep 'inet ' | awk {'print $2'} | grep -v '127.*' >> myip.txt "
#define SHELLSCRIPT2 "rm myip.txt"


// handle the threading logic 
void* handle_connection(void* p_client){
	int client_loc = *((int *)p_client);
	free(p_client); // free the space;

	pthread_t self_id ;

	self_id = pthread_self();


	char buff[1024];
	size_t bytes_read; 
	while (bytes_read = recv(client_loc, buff, 1024,0)){
		if (bytes_read==5)
			if (buff[0]=='q' && buff[1] =='u' && buff[2]=='i' && buff[3] =='t')
				{
					printf("exit for the thread with threadid %lu \n", self_id);
					fflush(stdout);
					close(client_loc); 
					return NULL;
				}
		printf("%lu %s",self_id, buff);
		fflush(stdout);
		printf("%c",'\n');
		memset(buff, 0,1024);
	}
	return NULL;


	
}

int main(){

	
	struct sockaddr_in client_address;
    	socklen_t client_address_len = sizeof(client_address);
 	int client_socket;	
	int server_port;
	struct sockaddr_in server_address; // ipv4
	server_address.sin_family = AF_INET; 
	server_address.sin_addr.s_addr = INADDR_ANY;
	// take user input for the server ip and port;
	printf(" give port address \n");

	scanf("%d", &server_port);

	server_address.sin_port = htons(server_port);


	int server_socket = socket(AF_INET, SOCK_STREAM,0 );

	if (server_socket<0){
		perror("unable to create socket \n");
		exit(EXIT_FAILURE);
	}


	int binding_status = bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	if (binding_status <0)
	{
		perror( "error while binding \n");
		exit(EXIT_FAILURE);
	}

	int listening_status = listen(server_socket, 10);
     	if (listening_status <0){
		perror("Server is unable to listen :( \n");
		exit(EXIT_FAILURE);
	}


	char output[256];
	system(SHELLSCRIPT1);

	FILE * ptr = fopen("myip.txt", "r");
	fscanf(ptr, "%s", output);
	 system(SHELLSCRIPT2);
	printf("Host ip of the server is : %s \n", output);
	printf("Server listening on port number %d\n", server_port);


	char buff[1024];

	while (true){
	
		// accept a new connection
		printf("\nwaiting for a connection \n");

		socklen_t cli_addr_size = sizeof(client_address);

		client_socket = accept(
				server_socket , (struct sockaddr *)&client_address, &cli_addr_size);
		if (client_socket<0)
			perror("Error while accepting incoming connections : \n");
		printf("connected with one of the incoming connection \n");

		//size_t bytes_read; 
		//while (bytes_read = recv(client_socket, buff, 1024, 0)){
		//	printf("%s", buff);
		//	pr.intf("\n");
	//}
		pthread_t t;
		int * pclient = malloc(sizeof(int));

		*pclient = client_socket;

		pthread_create(&t, NULL , handle_connection, pclient);	
		
	}
	return 0;
}
