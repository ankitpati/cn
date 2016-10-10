/* server.c */
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

void exit_error(char *call)
{
    fprintf(stderr, "server: %s(2) failed!\n", call);
    perror("server");
    exit(errno);
}

int main()
{
    ssize_t bytes;
    int sd, con_sd;
    char buf[80];
    socklen_t addrlen;
    struct sockaddr_in addr;

    puts("SERVER\n");

    if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        exit_error("socket");

    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
    addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(sd, (struct sockaddr *) &addr, sizeof(addr)))
        exit_error("bind");

    if(listen(sd, 5))
        exit_error("listen");

    addrlen = sizeof(addr);

    for(;;) {
        if((con_sd = accept(sd, (struct sockaddr *) &addr, &addrlen)) < 0)
            exit_error("accept");

        if(!fork()) {
            close(sd);

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
