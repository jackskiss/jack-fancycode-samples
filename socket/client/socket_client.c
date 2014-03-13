#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <sys/un.h>

#define ENABLE_UNIX_DOMAIN_SOCKET

#ifdef ENABLE_UNIX_DOMAIN_SOCKET
const char * file_server = "/tmp/udstest";
#endif


int main(int argc, char *argv[])
{
    int sockfd = 0, n = 0;
    char recvBuff[1024];
#ifdef ENABLE_UNIX_DOMAIN_SOCKET    
    struct sockaddr_un serv_addr; 
#else
    struct sockaddr_in serv_addr; 
#endif
    if(argc != 2)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    } 

    memset(recvBuff, '0',sizeof(recvBuff));
#ifdef ENABLE_UNIX_DOMAIN_SOCKET  
    if((sockfd = socket(PF_FILE, SOCK_STREAM, 0)) < 0)
#else
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
#endif
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

#ifdef ENABLE_UNIX_DOMAIN_SOCKET    
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, file_server);
#else
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); 
#endif

#ifndef ENABLE_UNIX_DOMAIN_SOCKET        
    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 
#endif

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 

    write(sockfd, "Hello Server", 13);

    while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
    {
        recvBuff[n] = 0;
        if(fputs(recvBuff, stdout) == EOF)
        {
            printf("\n Error : Fputs error\n");
        }
    } 

    if(n < 0)
    {
        printf("\n Read error \n");
    } 

    return 0;
}
