
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand_int(int a, int b)
{
    return a + rand() % (b-a+1);
}

char *rand_str(int len)
    #define SIGMA                               \
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"    \
                "abcdefghijklmnopqrstuvwxyz"    \
                "0123456789"
{
    char *str;
    int j;

    if ( (str=malloc(len+1)) == NULL )
    {
        printf( "rand_str--malloc\n" );
        exit( 1 );
    }
    for ( j=0; j<len; ++j )
    {
        /* do not include NULL byte */
        str[j] = SIGMA[rand_int(0, sizeof(SIGMA)-2)];
    }
    str[j] = '\0';

    return str;
}

int main(int argc, char **argv)
{
    srand( (long) clock() );
    int j, k;

    for ( j=0; j<10; ++j )
    {
        for ( k=0; k<5; ++k )
        {
            printf( "%10s ", rand_str(rand_int(5, 10)) );
        }
        printf("\n");
    }

    return 0;
}
