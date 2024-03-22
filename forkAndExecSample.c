#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
  pid_t pid = fork();

  if(pid==-1){
    perror("Fork failed");
    exit(EXIT_FAILURE);
  }
  else if(pid==0){
    printf("Child process (PID : %d) executing ls -l\n",getpid());

    char *args[] = {"ls","-l",NULL};
    execvp(args[0],args);

    perror("execvp failed");
    exit(EXIT_FAILURE);
  }
  else{
    printf("Parent process (PID : %d) waiting for child...\n",getpid());
    wait(NULL);
    printf("Parent process: Child process completed.\n");
  }
  return 0;
}
