#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include <sys/un.h>


#define ENABLE_UNIX_DOMAIN_SOCKET

#ifdef ENABLE_UNIX_DOMAIN_SOCKET
const char * file_server = "/tmp/udstest";
#endif

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
#ifdef ENABLE_UNIX_DOMAIN_SOCKET    
    struct sockaddr_un serv_addr; 
#else
    struct sockaddr_in serv_addr; 
#endif
    char sendBuff[1025];
    time_t ticks;

#ifdef ENABLE_UNIX_DOMAIN_SOCKET
    listenfd = socket(PF_FILE, SOCK_STREAM, 0);
#else
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
#endif

    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

#ifndef ENABLE_UNIX_DOMAIN_SOCKET        
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
#endif
    
#ifdef ENABLE_UNIX_DOMAIN_SOCKET
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, file_server);
#else
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); 
#endif

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 

    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 

        read(connfd, sendBuff, sizeof(sendBuff));
        
        printf("%s\n", sendBuff);

        ticks = time(NULL);
        snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
        write(connfd, sendBuff, strlen(sendBuff)); 

        close(connfd);
        sleep(1);
     }
}
