#include <stdio.h>
// #include <time.h>
#include <unistd.h>

void test() {
    printf( "testing...\n" );
}

void sleep_time( int n ) {
    sleep( n );
}

int main( int argc, char **argv ) {
    test();
    return 0;
}