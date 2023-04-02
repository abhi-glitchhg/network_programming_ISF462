#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main( int argc, char **argv){

	if (argc!=2)
	{
		printf("number of argument not valid");
		return 1;
	}

	char url[1024];


	//printf("%s", argv[1]); 
	char command[1024]= "curl ";

	//printf("%d",sizeof(argv[1])); 
	for (int i=0; i< strlen(argv[1]); i++){
		command[i+5] = argv[1][i];

	}

	char redirect[]= " > test.html\n";

	int command_size = strlen(command);
//	printf(" \n%s", command );
//	printf("%d", strlen(redirect)) ;
	for (int i=0; i<strlen(redirect); i++ )	

		command[i+command_size] = redirect[i];

	

	printf("executing following curl command \n%s", command);

	system(command);

	return 1;
	

}
