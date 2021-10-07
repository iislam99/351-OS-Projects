/*
Iftekharul Islam (893441071)
Due: 11 Sept. 2020
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
  printf("I am the parent!\n");
  pid_t child_pid;
  child_pid = fork();

  if (child_pid < 0) {// Error
    fprintf(stderr, "Fork Failed");
    exit(-1);
  }
  else if (child_pid == 0) { // Child process
    printf("I am the child!\n");
    pid_t grandchild_pid;
    grandchild_pid = fork();

    if (grandchild_pid < 0) { // Error
      fprintf(stderr, "Fork Failed");
      exit(-1);
    }
    else if (grandchild_pid == 0) { // Child process of child process
      printf("I am the grandchild! Opening Firefox...\n");
      execlp("/bin/firefox", "firefox", NULL);
    }
    else {
      wait(NULL);
      printf("I am the child! Grandchild process complete.\n");
    }
  }
  else {
    wait(NULL);
    printf("I am the parent! Child process complete.\n");
  }
}
