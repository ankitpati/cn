/* client.c */
/* Date  : 26 September 2016
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define DEFAULT_HOST "127.0.0.1"
#define DEFAULT_PORT 1234

void exit_error(char *call)
{
    fprintf(stderr, "client: %s(2) failed!\n", call);
    perror("client");
    exit(errno);
}

int main(int argc, char **argv)
{
    ssize_t i, bytes;
    int sd, port = DEFAULT_PORT;
    char clname[80], buf[80], *host = DEFAULT_HOST;
    struct sockaddr_in addr;

    switch(argc) {
    case 3:
        port = atoi(argv[2]);
    case 2:
        host = argv[1];
    case 1: /* intended fall-through */
        break;
    default:
        fprintf(stderr, "Usage:\n\tclient [host] [port]\n");
        exit(1);
        break;
    }

    puts("CLIENT\n");

    puts("Client ID?");
    fgets(clname, 70, stdin);
    putchar('\n');
    clname[strlen(clname) - 1] = '\0';
    strcat(clname, ": ");

    if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        exit_error("socket");

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_aton(host, &addr.sin_addr);

    if(connect(sd, (struct sockaddr *) &addr, sizeof(addr)))
        exit_error("connect");

    if(!fork()) {
        for(;;) {
            fgets(buf, 80, stdin);
            if(send(sd, clname, strlen(clname), 0) != (ssize_t) strlen(clname))
                exit_error("send");
            if(send(sd, buf, strlen(buf), 0) != (ssize_t) strlen(buf))
                exit_error("send");
        }
        exit(0);
    }

    do {
        bytes = recv(sd, buf, 80, 0);
        for(i = 0; i < bytes; ++i) putchar(buf[i]);
    } while(bytes > 0);

    close(sd);

    return 0;
}
/* end of client.c */
