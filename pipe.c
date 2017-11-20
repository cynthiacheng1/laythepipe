#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
  int READ = 0;
  int WRITE = 1;

  int fds[2];
  pipe(fds);
  int fds1[2];
  pipe(fds1);
  int num = 16;

  if (fork() != 0){ //parent
    close(fds[READ]);
    close(fds1[WRITE]);
    int num = 16;
    write(fds[WRITE], &num, sizeof(num));
    printf("[parent] sending: %d\n", num);
    close(fds[WRITE]);
    read(fds1[READ], &num, sizeof(num));
    printf("[parent] received: %d\n", num);
    close(fds1[READ]);
  }

  else{
    close(fds[WRITE]);
    close(fds1[READ]);
    read(fds[READ], &num, sizeof(num));
    printf("[child] doing quick maths on %d\n", num );
    num = num * 100;
    write(fds1[WRITE], &num, sizeof(num));
    close(fds1[WRITE]);
  }
  return 0;
}
