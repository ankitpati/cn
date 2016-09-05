/* dec2bin.c */
/* Date  : 22 August 2016
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdbool.h>

typedef unsigned long decint;

void putdec2bin(decint d)
{
    bool lzero;
    decint mask;
    for(lzero = true, mask = (decint)1 << (8*sizeof(mask)-1); mask; mask >>= 1)
        if(d & mask || !lzero || mask == 1)
            lzero = false, putchar(d & mask ? '1' : '0');
}

int main()
{
    decint d;
    puts("Decimal Number?");
    scanf(" %lu%*c", &d);
    printf("= ");
    putdec2bin(d);
    printf(" (binary)\n");
    return 0;
}
/* end of dec2bin.c */

/* OUTPUT

Decimal Number?
43
= 101011 (binary)

*/
