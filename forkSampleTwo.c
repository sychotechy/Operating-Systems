#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
  int numPro = 3;
  pid_t childPid;

  printf("Parent process (PID : %d) is creating child process...\n",getpid());

  for(int i=0;i<numPro;++i){
    childPid = fork();

    if(childPid == -1){
      perror("Fork failed");
      exit(EXIT_FAILURE);
    }
    else if(childPid == 0){
      printf("Child process (PID : %d) created by parent (PID : %d)\n",getpid(),getppid());
      exit(EXIT_SUCCESS);
    }
  }

  for(int i=0;i<numPro;++i){
    wait(NULL);
  }
  printf("Parent process (PID : %d) has finished creating child processes.\n",getpid());
  return 0;
}
