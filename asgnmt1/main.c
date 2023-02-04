#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>

int ans(){

	pid_t s = fork(); // we create fork here
	if (s==0){
		// child
		
		sleep(2); // added to avoid any possible race conditions related to stdout stream.	
		printf("from child process Its own PID: %d, \n",getpid());
                printf("from child process, parent PID: %d, \n",getppid());

		exit(0);
	}
	else {

		printf("from parent process, own PID %d, \n",getpid());
		printf("from parent process, childrens PID: %d, \n", s);
		s = wait(NULL); //waits for child to finish execution.
		printf("children finished execution with pid %d, \n", s);
		return getpid(); // cheeky way to handle when parent finishes the execution.
	}
	return 0;



}

int main(){

	printf("assignment 1\n\n");
	int temp = ans(); 
	if (temp!=0)
		printf( "parent finished execution with PID, %d \n", temp);
	return 0;
}


