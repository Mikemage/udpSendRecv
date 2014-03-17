#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <map>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

using namespace std;

int main(int argc, char *argv[])
{

    struct sockaddr_in addr;
    int sock;
    char msgbuf[1024];

    int yes = 1;


    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    fcntl(sock, F_SETFL, fcntl(sock, F_GETFL) | O_NONBLOCK);    //set no blocking IO


    // allow multiple sockets to use the same PORT number
    if ( (setsockopt (sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof( yes )) < 0))
    {
        perror("Reusing ADDR failed");
        exit(1);
    }
    
    // setting up destination addres
    memset(&addr, 0, sizeof( addr ));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=INADDR_ANY;
    addr.sin_port=htons(8081);
    if (argc > 1 && inet_aton(argv[1], &addr.sin_addr)==0) {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    if (argc == 3 ) {
        addr.sin_port=htons(atoi(argv[2]));
    }

    sprintf(msgbuf, "{ playerId: \"80db43f3-c323-41b5-914a-000102569908\", messageId: \"1234\", smilEvent: \"some-request\", foo: \"bar\"\n");
    sendto(sock, msgbuf, strlen(msgbuf)+1, 0, (const sockaddr*)&addr, sizeof(addr));

    close(sock);
    return 0;
};
