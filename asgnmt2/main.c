#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int fd1[2]; int fd2[2];
    pipe(fd1); pipe(fd2);
    
    //int ff;
    //scanf("%d",&ff );
    pid_t pid = fork();

    if (pid>0){
    // this is parent
    printf("this is parent %d \n", getpid());

    // parent uses first pipe fd1 to write the data; so we will close the reading for fd1 and we will read from fd2; so we will close the write of fd2;
    //
    sleep(2);
    close(fd1[0]);
    close(fd2[1]);

    // parent asking for input
    printf("parent (%d) asking for input  \n", getpid()) ;
    int i =1211;
    scanf("%d", &i);
    //writing the data to the pipe;
    write( fd1[1], &i,sizeof(i));
    //reading data from the pipe;
    int j;
    read(fd2[0], &j, sizeof(j));
    printf("parent (%d) has recieved the  integer \n" , getpid());
    printf("the integer sent by children(%d)  is %d \n",pid,j);

    //close the remaining ends of the pipe for respective process
    close(fd1[1]); close(fd2[0]);
    //exit
    exit( 0);}

    else 
    {
    //this is child 
    printf("this is child (%d) \n", getpid());

    //close the respective pipe endds;
    close(fd1[1]);
    close(fd2[0]);
    sleep(1);
    int i;
    
    //read from pipe;
    read( fd1[0], &i, sizeof(i));
    printf("children(%d) now received the integer  \n" , getpid() );
    printf("the integer sent by by the parent(%d) is %d \n", getppid(), i);

    printf("child(%d) is asking for input  \n", getpid());
    int j ;
    //write to the pipe;
    scanf("%d", &j);
    write(fd2[1], &j, sizeof(j));
    
    //close the remaining ends of the pipe for respective process

    close(fd2[1]);
    close(fd1[0]);
    //exit
    exit(0);


    }
    return 0;

    



}


