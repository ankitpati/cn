/* tradcksum.c */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

char *getstr()
{
    int c;
    size_t n;
    char *s, *t;
    if(!(s = t = malloc(1))) return NULL;
    for(n=0; (c=getchar())!=EOF && c-'\n' && (t=realloc(s, n+2)); s[n++]=c) s=t;
    if(!t){
        free(s);
        return NULL;
    }
    s[n] = '\0';
    return s;
}

void tradcksum(char *filename)
{
    uint16_t word;
    uint32_t sum;

    FILE *fin;

    if(!(fin = fopen(filename, "rb"))) {
        fprintf(stderr, "file-not-opened  %s", filename);
        return;
    }

    sum = 0;

    while(!feof(fin) && !ferror(fin)) {
        fread(&word, sizeof(word), 1, fin);
        sum += word;
    }

    while(sum >> 16) sum = (sum >> 16) + (sum & 0x0000ffff);
    sum = ~sum;
    sum = (uint16_t)sum;

    fclose(fin);

    printf("%.5u  %s\n", sum, filename);
}

int main(int argc, char **argv)
{
    int i;

    if(argc < 2) {
        fprintf(stderr, "Usage:\n\ttradcksum <filename> [<filename>, ...]");
        exit(1);
    }

    for(i = 1; i < argc; ++i) tradcksum(argv[i]);

    return 0;
}
/* end of tradcksum.c */
