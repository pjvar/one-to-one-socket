#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
int main(void){
    //IPV4
    struct sockaddr_in serv;
    char buf[128],msg[128];
    //socket
    int sfd = socket(AF_INET,SOCK_STREAM,0);
    if(sfd == -1){
        perror("socket");
        return -1;
    }
    //zero
    serv.sin_family = AF_INET;
    serv.sin_port = htons(6000);
    inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr);
    //connect
    int c = connect(sfd,(struct sockaddr *)&serv,sizeof(serv));
    if(c == -1){
        perror("connect");
        return -1;
    }
    while(1){
        int r = read(sfd,buf,128);
        //write(1,buf,r);
        printf("%s\n",buf);
        gets(msg);
        write(sfd,msg,strlen(msg) + 1);
    }
    return 0;
}
