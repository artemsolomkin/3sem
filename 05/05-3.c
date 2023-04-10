#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
   int     fd_prnt[2] = {}, fd_chld[2] = {}, result = 0;    

   size_t size = 0;
   char  resstring[14] = {}, resstring_1[20] = {};

   if(pipe(fd_prnt) < 0 || pipe(fd_chld) < 0){
     printf("Can\'t open pipe\n");
     exit(-1);
   }

   result = fork();

   if(result == -1) {
      printf("Can\'t fork child\n");
      exit(-1);
   } else if (result > 0) {

     /* Parent process */

      close(fd_prnt[0]);
      close(fd_chld[1]);

      size = write(fd_prnt[1], "Sapere, Aude!", 14);

      if(size != 14){
        printf("Can\'t write all string to pipe\n");
        exit(-1);
      }

      size = read(fd_chld[0], resstring_1, 20);
      printf("%s", resstring_1);
      if(size != 20){
           printf("Can\'t read string");
           exit(-1);
      }

      printf("%s", resstring_1);

      close(fd_prnt[1]);
      close(fd_chld[0]);
      printf("Parent exit\n");

   } else {

      /* Child process */

      close(fd_prnt[1]);
      close(fd_chld[0]);
      size = read(fd_prnt[0], resstring, 14);

      if(size < 0){
         printf("Can\'t read string from pipe\n");
         exit(-1);
      }
      printf("%s\n",resstring);
      size = write(fd_chld[1], "Child process does task\n", 25);
        if (size != 20) {
            printf("Can\'t write string\n");
            exit(-1);
        }
      printf("Child exit");

      close(fd_prnt[0]);
      close(fd_chld[1]);
   }

   return 0;
}