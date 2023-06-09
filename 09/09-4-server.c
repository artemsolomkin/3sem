#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LAST_MESSAGE 255

int main(void)
{
    int msqid;
    char pathname[]="09-4-client.c";
    key_t  key;
    int len, maxlen;

    struct mymsgbuf
   {
      long mtype;
      struct { 
        short sinfo;
        float finfo;
      } info;
   } mybuf;
    
    key = ftok(pathname, 0);
    
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
       printf("Can\'t get msqid\n");
       exit(-1);
    }
    
    while (1) {
       maxlen = sizeof(struct mymsgbuf);;
       
       if (( len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 0, 0)) < 0){
         printf("Can\'t receive message from queue\n");
         exit(-1);
       }
       
       printf("message type = %ld, sinfo = %d, finfo = %f\n", mybuf.mtype, mybuf.info.sinfo, mybuf.info.finfo);
    }    

    return 0;       
}