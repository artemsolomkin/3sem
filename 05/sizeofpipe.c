#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
int main()
{

    int fd[2];
    char a[100];
    int size=0;
    int c,b;
    
    if((pipe(fd)) < 0)
    {
        printf("can't create pipe\n");
        exit(-1);
    }
    else
    {
        while(true)
        {
            c = write(fd[1], "w", 1);
            b = read(fd[0], a, 1);
            size += 1;
            printf("%d\n", size); 
        } 
        
    }   
    return 0;
}