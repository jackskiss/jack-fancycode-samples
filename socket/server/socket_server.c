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

#define BOOL    char
#define true    1
#define false   0

#define ENABLE_UNIX_DOMAIN_SOCKET

#ifdef ENABLE_UNIX_DOMAIN_SOCKET
const char * file_server = "/tmp/udstest";
#endif

static void * readloop(void * data);

static    int listenfd = 0, connfd = 0, n = 0;
#ifdef ENABLE_UNIX_DOMAIN_SOCKET    
static    struct sockaddr_un serv_addr; 
#else
static    struct sockaddr_in serv_addr; 
#endif

static    char sendBuff[1025];
static    char recvBuff[1025];
static    time_t ticks;

static    pthread_t readThreadId;

static    BOOL running; 

int main(int argc, char *argv[])
{


#ifdef ENABLE_UNIX_DOMAIN_SOCKET

    if ( access(file_server, F_OK) == 0 )
        unlink( file_server );

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

    listen(listenfd, 5); 
    
    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 

    pthread_create(&readThreadId, 0, readloop, 0);

    while(1)
    {
        fgets(sendBuff, sizeof(sendBuff), stdin);

        write(connfd, sendBuff, strlen(sendBuff)+1);

        sleep(1);

    }

    running = false;

    close(connfd);
}

static void * readloop(void * data)
{
    running = true;

    while(running)
    {
        n = read(connfd, recvBuff, sizeof(sendBuff));
        
        if(n > 0)
            printf("%s\n", recvBuff);

/*        ticks = time(NULL);
        snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
        write(connfd, sendBuff, strlen(sendBuff)); 
*/
             
        sleep(1);     
        
    }

    pthread_exit(NULL);
}

