#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void func( char *str ) {
    printf( "%s\n", str );
    str = ( char * )malloc( 10 );
    str = "tr";
    // sprintf( str, "abcd" );
    return;
}

int main() {
    char *tmp = "s";
    func( tmp );

    if ( tmp )
        printf( "tmp is %s\n", tmp );
    else
        printf( "tmp is NULL\n" );
    return 0;
}