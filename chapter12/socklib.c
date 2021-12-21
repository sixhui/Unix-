#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>
#include <netdb.h>
#include "socklib.h"

#define     HOSTLEN     256
#define     BACKLOG     1



int make_server_socket(int portnum){
    make_server_socket_q(portnum, BACKLOG);
}

int make_server_socket_q(int portnum, int backlog){
    int sock_id;
    struct sockaddr_in saddr;
    struct hostent *hp;
    char hostname[HOSTLEN];

    // socket
    if((sock_id = socket(PF_INET, SOCK_STREAM, 0)) == -1) return -1;

    // bind
    bzero((void*)&saddr, sizeof(saddr));
    gethostname(hostname, HOSTLEN);
    hp = gethostbyname(hostname);

    saddr.sin_family        = AF_INET;
    // saddr.sin_addr.s_addr   = htonl(INADDR_ANY);
    saddr.sin_addr.s_addr   = inet_addr("172.29.22.82");
    // bcopy((void*)hp->h_addr, (void*)&saddr.sin_addr, hp->h_length);
    saddr.sin_port          = htons(portnum);

    if(bind(sock_id, (struct sockaddr*)&saddr, sizeof(saddr)) != 0) return -1;

    // listen
    if(listen(sock_id, backlog) != 0) return -1;

    return sock_id;
}

int connect_to_server(char* host, int portnum){
    int                 sock_id;
    struct sockaddr_in  servaddr;
    struct hostent      *hp;

    // socket
    if((sock_id = socket(AF_INET, SOCK_STREAM, 0)) == -1) return -1;

    // bind
    bzero(&servaddr, sizeof(servaddr));
    if((hp = gethostbyname(host)) == NULL) return -1;

    servaddr.sin_family = AF_INET;
    bcopy(hp->h_addr, (struct sockaddr*)&servaddr.sin_addr, hp->h_length);
    servaddr.sin_port = htons(portnum);
    
    // connect
    if(connect(sock_id, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) return -1;
    return sock_id;
}

// int main(int argc, char const *argv[])
// {
//     printf("%d\n", INADDR_ANY);
//     char hostname[HOSTLEN];
//     gethostname(hostname, HOSTLEN);
//     struct hostent* p = gethostbyname(hostname);
//     printf("%s\n", p->h_addr_list[0]);
    
//     printf("%d\n", inet_addr("172.29.22.82"));
//     return 0;
// }


