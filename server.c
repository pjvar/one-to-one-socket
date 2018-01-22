#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include<pthread.h>
int arr[32];
int i;
char buf[128];
char msg[] = "你的好友已经上线";

void *doit(void *arg){
        if(i==0){
            while(1){
                int r = read(arr[0],buf,128);
                write(arr[1],buf,r);
                int s = read(arr[1],buf,128);
                write(arr[0],buf,s);
            }
        }
        else{
            write(arr[0],msg,strlen(msg) + 1); 
            while(1){
                int r = read(arr[0],buf,128);
                write(arr[1],buf,r);
                int s = read(arr[1],buf,128);
                write(arr[0],buf,s);
            }
        }    
}
int main(void){
    char IP[32];
    //IPV4
    struct sockaddr_in serv;
    struct sockaddr_in client;
    socklen_t cli_len;
    //socket
    int sfd = socket(AF_INET,SOCK_STREAM,0);
    if(sfd == -1){
        perror("socket");
        return -1;
    }
    //初始化
    serv.sin_family = AF_INET;
    serv.sin_port = htons(6000);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    //bind
    int b = bind(sfd,(struct sockaddr *)&serv,sizeof(serv));
    if(b == -1){
        perror("bind");
        return -1;
    }
    //listen
    listen(sfd,5);
    int *ret=NULL;
    //accept
    //int arr[32],i;
    for(i = 0;;i++){
        cli_len=sizeof(client);
        int cfd = accept(sfd,(struct sockaddr*)&client,&cli_len);
        if(cfd == -1){
            perror("accept");
            return -1;
        }
        printf("%s\n",inet_ntop(AF_INET,&client.sin_addr,IP    ,32));
        arr[i] = cfd;
    
        pthread_t tid;
        pthread_create(&tid,NULL,doit,&arr[i]);
        sleep(1);
    }
    return 0;
}
