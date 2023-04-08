#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdbool.h>
#include<arpa/inet.h>
#include<string.h>
#include<netdb.h>

int main(int argc, char * argv[]){

	if ( argc!=2){
		perror("number of arguments"); exit(EXIT_FAILURE);
	}

	char url[1024] ;// / = argv[1];

	//printf("%s", url); 
	//fgets(url, 1024, stdin);
	//url[strcspn(url, "\n")] = 0;
	strcpy(url, argv[1]);
 	printf("%s\n", url);	
	char *host = strtok(url, "/");
	char *path = strtok(NULL,"");

	if (path == NULL) 
		path = "/";


	struct hostent *he = gethostbyname(host);
	if (he==NULL){
	perror("host creation"); 
	} 

	struct in_addr **addr_list = (struct in_addr ** ) he-> h_addr_list;

	char ip[1024] ;
	strcpy(ip, inet_ntoa( *addr_list[0]) );


	// create a socket
	int socket_flag = socket(AF_INET, SOCK_STREAM, 0); // tcp
							   //
	if (socket_flag <0){
	perror("socket creation"); exit(EXIT_FAILURE);
	}

	// connection
	//
	struct sockaddr_in server;

	server.sin_family = AF_INET; server.sin_port = htons(80); inet_pton(AF_INET, ip, &server.sin_addr);

	if (connect( socket_flag, (struct sockaddr *) &server, sizeof(server) )<0){
	perror("error while connecting to the server" ); exit(EXIT_FAILURE);

	}

	char get_req[1024];

	sprintf(get_req, "GET /%s HTTP/1.0\r\nHost: %s\r\n\r\n", path, host);

	if (send(socket_flag, get_req, strlen(get_req),0)<0){
	perror("error while sending data"); exit(EXIT_FAILURE);
	}

	char response[40960];

	FILE *fp = fopen("test.html", "wb");
	if (fp==NULL){
	perror("error while opening file");exit(EXIT_FAILURE);}
	int response_len= 0; int content_len = 0; int is_body =0;

	int pre_val =0;
	while (true){
	int received = recv(socket_flag, response+response_len, 40960 - response_len,0);
	

	if (received<0){
	printf("some error while receiving the data"); 
	return 1;
	}

	else if (received ==0){
	printf("received all the data; \n");
	break;
	}
	pre_val  = response_len;
	response_len += received; 
	response[response_len] = '\0';
	if (!is_body){
		char *content_length_ptr = strstr(response, "Content-Length");
		if (content_length_ptr!=NULL){
			sscanf(content_length_ptr, "Content-Length: %d", &content_len);
			is_body = 1;
		}
	
	}


	if (is_body ){
		
		char *close_ptr = strstr(response, "Connection: close");
		//*close_ptr = '\0';
		FILE *md =fopen( "metadata.txt", "wb");
		fwrite(response, sizeof(char),close_ptr - response + sizeof("Connection: close\n"), md); 
		fclose(md);
		//fwrite(response, sizeof(char), received, fp );
		fwrite(close_ptr+sizeof("Connection: close\n"), sizeof(char), received, fp );
		printf("writing data to the file\n metadata about the response can be found in metadata.txt \n and the html content is stored at test.html \n");
		if (response_len >= content_len)
			break;
	
	}
	


	}
	printf("done :)");

	fclose(fp);
	close(socket_flag);
	return 1;


}
