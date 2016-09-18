/* bitstuff.c */
/* Date  : 12 September 2016
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <string.h>

#define EOT "01111110"
/* EOT: End Of Transmission */

void stuff(char *stream)
{
    size_t i;
    char *s;

    for(s = stream; (s = strstr(s, EOT)); s[1] = '0', s += 2)
        for(i = strlen(s); i - 1; --i) s[i] = s[i - 1];

    printf("%s%s%s\n", EOT, stream, EOT);
}

void unstuff(char *stream)
{
    size_t i;
    char *s;

    if(strlen(stream) < 16) {
        putchar('\n');
        return;
    }

    stream[strlen(stream) - 8] = '\0';
    s = stream += 8;

    while((s = strstr(s, "0"EOT)))
        for(i = 0; i < strlen(s); ++i) s[i] = s[i + 1];

    printf("%s\n", stream);
}

int main()
{
    char s[200];

    puts("Transmitted Stream?");
    fgets(s, 80, stdin);
    s[strlen(s) - 1] = '\0';

    puts("Bit Stuffed:");
    stuff(s);

    putchar('\n');

    puts("Received Stream?");
    fgets(s, 80, stdin);
    s[strlen(s) - 1] = '\0';

    puts("Bit Unstuffed:");
    unstuff(s);

    return 0;
}
/* end of bitstuff.c */

/* OUTPUT

Transmitted Stream?
101010110101011001111110101011011111101010110101
Bit Stuffed:
011111101010101101010110001111110101011001111110101011010101111110

Received Stream?
011111101010101101010110001111110101011001111110101011010101111110
Bit Unstuffed:
101010110101011001111110101011011111101010110101

*/
