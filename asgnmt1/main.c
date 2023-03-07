#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
	printf("assignment 1 \n");
	pid_t s = fork(); // we create fork here
	pid_t parent_id;
	if (s==0){
		// child
		
		sleep(2); // added to avoid any possible race conditions related to stdout stream.	
		printf("from child process Its own PID: %d, \n",getpid());
                printf("from child process, parent PID: %d, \n",getppid());

		exit(0);
	}
	else {
		parent_id = getpid();
		printf("from parent process, own PID %d, \n",parent_id);
		printf("from parent process, childrens PID: %d, \n", s);
		s = wait(NULL); //waits for child to finish execution.
		printf("children finished execution with pid %d, \n", s);

		exit(0);


	}

	return 0;



}



