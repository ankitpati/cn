/* bytestuff.c */
/* Date  : 12 September 2016
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <string.h>

void stuff(char *stream)
{
    size_t i, at_count;

    putchar('@');

    for(i = 0; stream[i]; ++i) {
        putchar(stream[i]);

        for(at_count = 0; stream[i + at_count] == '@'; ++at_count);
        if(at_count) {
            i += at_count - 1;
            while(at_count--) putchar('@');
        }
    }

    puts("@");
}

void unstuff(char *stream)
{
    size_t i, at_count;

    for(i = 1; stream[i]; ++i) {
        for(at_count = 0; stream[i + at_count] == '@'; ++at_count);
        if(at_count) {
            i += at_count - 1;
            if(!stream[i + 1] && !--at_count) continue;
            while(--at_count) putchar('@');
        }
        else putchar(stream[i]);
    }
}

int main()
{
    char s[80];

    puts("Transmitted Stream?");
    fgets(s, 80, stdin);
    s[strlen(s) - 1] = '\0';

    puts("Byte Stuffed:");
    stuff(s);

    putchar('\n');

    puts("Received Stream?");
    fgets(s, 80, stdin);
    s[strlen(s) - 1] = '\0';

    puts("Byte Unstuffed:");
    unstuff(s);

    return 0;
}
/* end of bytestuff.c */

/* OUTPUT

Transmitted Stream?
@ankit@@@pati@@
Byte Stuffed:
@@@ankit@@@@pati@@@@

Received Stream?
@@@ankit@@@@pati@@@@
Byte Unstuffed:
@ankit@@@pati@@

*/
