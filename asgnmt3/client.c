#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdbool.h>
int main(){

	char server_ip[16];
//	char server_port[5];
	//create a socket
	int server_port;
	int socket_flag = socket(AF_INET, SOCK_STREAM,0);
	char newline_char = '\n';

	if (socket_flag==-1)
		printf("socket flag is -1");	


	//take input for the ip of the server
	printf("enter the server Ip address\n");
	scanf("%s", server_ip);
	server_ip[strcspn(server_ip, "\n")] = 0;

	printf("enter the port of the server\n");
	scanf("%d", &server_port);

	struct sockaddr_in  server_socket; // ipv4
	
	 server_socket.sin_family = AF_INET;
	 server_socket.sin_port = htons(server_port);
	 server_socket.sin_addr.s_addr = inet_addr(server_ip);

	    if(inet_pton(AF_INET,server_ip ,& server_socket.sin_addr) < 1){
        	perror("client: inet_pton() error ->");
        	exit(EXIT_FAILURE);
    }


	// connect
	int connection_flag = connect(socket_flag, (struct sockaddr *) & server_socket, sizeof(server_socket) );

	if (connection_flag<0)
	{		perror(" failed to connect to the server");
			exit(EXIT_FAILURE);
	}
	char string_buffer[1024];
	char stopword[1024];
	stopword[0] = 'q'; stopword[1] = 'u' ; stopword[2] = 'i' ; stopword[3] ='t' ;
	printf(" eneter words here; to stop the process, enter 'quit' and process will terminate. \n: ");
	
        while(true){ 
		fgets(string_buffer, sizeof(string_buffer), stdin);

		int len_string = strlen(string_buffer);



//		if (write( socket_flag, string_buffer, len_string)<0)
//		{
//		perror("error while writing the data");
///		exit(EXIT_FAILURE);
//		}

		if (send(socket_flag, string_buffer, len_string,0) < 0)
		{
			perror("error while sending the data");
			exit(EXIT_FAILURE);
		}
		if (len_string == 5){
			if (string_buffer[0]=='q' && string_buffer[1] == 'u' && string_buffer[2] =='i' && string_buffer[3] == 't')
				
				break;
		
		}	
		memset(string_buffer, 0,1024);
	}	



	 close(socket_flag);

	//take input until the input is quit
		


	// close connection





	return 0;


}
