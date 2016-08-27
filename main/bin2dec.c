/* bin2dec.c */
/* Date  : 22 August 2016
 * Author: Ankit Pati
 */

#include <stdio.h>

typedef unsigned long decint;

decint getbin2dec()
{
    int c;
    size_t i;
    decint d;
    for(c = '0', i = 8 * sizeof(decint), d = 0;
        i && ((c = getchar()) == '0' || c == '1'); --i, d = 2 * d + (c - '0'));
    if(c != '0' && c != '1') ungetc(c, stdin);
    return d;
}

int main()
{
    puts("Binary Number?");
    printf("= %lu (decimal)\n", getbin2dec());
    return 0;
}
/* end of bin2dec.c */
