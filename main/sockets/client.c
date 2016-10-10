/* client.c */
/* Date  : 26 September 2016
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void exit_error(char *call)
{
    fprintf(stderr, "server: %s(2) failed!\n", call);
    perror("client");
    exit(errno);
}

int main()
{
    ssize_t i, bytes;
    int sd;
    char buf[80];
    struct sockaddr_in addr;

    puts("CLIENT\n");

    if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        exit_error("socket");

    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
    inet_aton("127.0.0.1", &addr.sin_addr);

    if(connect(sd, (struct sockaddr *) &addr, sizeof(addr)))
        exit_error("connect");

    do {
        bytes = recv(sd, buf, 80, 0);
        for(i = 0; i < bytes; ++i) putchar(buf[i]);
    } while(bytes > 0);

    close(sd);

    return 0;
}
/* end of client.c */
