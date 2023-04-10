#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
 
int main(){
  int parent[2]; 
  int child[2]; 
  pid_t pid;
  ssize_t size;
  char buf[100];
  
  if(pipe(parent) < 0){ 
    printf("Can\'t create pipe\n");
    close(parent[0]);
    close(parent[1]);
    return -1;
  }
  if(pipe(child) < 0){ 
    printf("Can\'t create pipe\n");
    close(child[0]);
    close(child[1]);
    return -1;
  }
  
  pid = fork(); 
  if(pid < 0){ 
    printf("Can\'t fork child\n");
    return -2;
  }else if (pid > 0){ 
    
    close(parent[0]);
    close(child[1]);

    size = write(parent[1], "Hello, Parent!", 15);
    if(size != 15){printf("P: Can\'t write all string\n"); return -3;}
    

    size = read(child[0], buf, 14);
    if(size != 14){printf("P: Can\'t read string\n"); return -4;} 
    printf("P: %s\n", buf);
    
    close(parent[1]);
    close(child[0]);
    printf("Wait for child\n");
    waitpid(pid, NULL, 0);
    printf("Parent exit\n");
  }else{ 
    close(parent[1]);
    close(child[0]);
    
    size = read(parent[0], buf, 15);
    if(size != 15){printf("C: Can\'t read string\n"); return -5;} 
    printf("C: %s\n", buf);
    
    size = write(child[1], "Child, hello!", 14);
    if(size != 14){printf("C: Can\'t write all string\n"); return -6;}
    
    close(parent[0]);
    close(child[1]);
    printf("Child exit\n");
  }
  return 0; 
}