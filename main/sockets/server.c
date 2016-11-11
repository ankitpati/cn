/* server.c */
/* Date  : 26 September 2016
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define DEFAULT_BACKLOG 5
#define DEFAULT_PORT    1234

static sig_atomic_t cno; /* child number for pipes */

void childeath()
{
    --cno;
}

void exit_error(char *call)
{
    fprintf(stderr, "server: %s(2) failed!\n", call);
    perror("server");
    exit(errno);
}

int main(int argc, char **argv)
{
    ssize_t i, bytes;
    int sd, con_sd, port = DEFAULT_PORT, backlog = DEFAULT_BACKLOG, pfd[5][2];
    char buf[80];
    socklen_t addrlen;
    struct sockaddr_in addr;

    switch(argc) {
    case 3:
        backlog = atoi(argv[2]);
    case 2:
        port = atoi(argv[1]);
    case 1: /* intended fall-through */
        break;
    default:
        fprintf(stderr, "Usage:\n\tserver [port] [backlog]\n");
        exit(1);
        break;
    }

    puts("SERVER\n");

    if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        exit_error("socket");

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(sd, (struct sockaddr *) &addr, sizeof(addr)))
        exit_error("bind");

    if(listen(sd, backlog))
        exit_error("listen");

    if(signal(SIGCHLD, childeath) == SIG_ERR)
        exit_error("signal");

    addrlen = sizeof(addr);

    for(;;) {
        if((con_sd = accept(sd, (struct sockaddr *) &addr, &addrlen)) < 0)
            exit_error("accept");

        if(!fork()) {
            close(sd);

            if(!fork()) {
                do {
                    bytes = recv(con_sd, buf, 80, 0);
                    for(i = 0; i < bytes; ++i) putchar(buf[i]);
                } while(bytes > 0);
                exit(0);
            }

            for(;;) {
                fgets(buf, 80, stdin);
                bytes = send(con_sd, buf, strlen(buf), 0);
                if(bytes != (ssize_t) strlen(buf)) exit_error("send");
            }

            close(con_sd);
            exit(0);
        }

        close(con_sd);
    }

    close(sd);

    return 0;
}
/* end of server.c */
