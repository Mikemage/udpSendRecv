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
    int sock, nbytes,addrlen;
    char msgbuf[1024];

    int yes = 1;


    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
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

    // bind to receive address
    if (bind (sock, (struct sockaddr *) &addr, sizeof( addr )) < 0)
    {
        perror("bind");
        exit(1);
    }



    // now just enter a read-print loop
    while(1) {
    
    addrlen=sizeof(addr);
//        if ((nbytes = recvfrom(sock, msgbuf, sizeof( msgbuf ), 0, (struct sockaddr *) &addr, (socklen_t*) &addrlen)) < 0)
        if ((nbytes = recvfrom(sock, msgbuf, sizeof( msgbuf ), 0, NULL, NULL)) < 0)
        {
            if(!errno == EAGAIN && !errno == EWOULDBLOCK) {
                perror("NON: recvfrom");
                exit(1);
            }
            else
            {
                cout <<" got nothing "<<endl;
            }
    
        }//Closes the if
        else
        {
                cout <<" got something "<<endl;
                exit(1);
        }
    }
};
