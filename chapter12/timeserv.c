#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

#include "socklib.h"

#define     PORTNUM     12345
#define     oops(msg)   {perror(msg); exit(1);}
int main(int argc, char const *argv[])
{
    int serv_sock, sock_id;
    FILE* sock_fp;
    time_t cur_time;

    serv_sock = make_server_socket_q(PORTNUM, 3);

    while(1){
        if((sock_id = accept(serv_sock, NULL, NULL)) == -1) oops("accept");
        printf("get a call\n");

        if((sock_fp = fdopen(sock_id, "w")) == NULL) oops("fdopen");

        cur_time = time(NULL);
        fprintf(sock_fp, "The time here is ..");
        fprintf(sock_fp, "%s", ctime(&cur_time));
        fclose(sock_fp);
    }
    
    
    return 0;
}


