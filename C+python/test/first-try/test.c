#include <stdio.h>
// #include <time.h>
#include <unistd.h>

void test() {
    int sum_odd = 0;
    int sum_even = 0;
    for ( int i = 0; i < 100000000; ++i ) {
        if ( i % 2 == 0 )
            sum_even += i;
        else
            sum_odd += i;
        sum_even -= sum_odd;
        sum_odd -= sum_odd;
    }
    printf( "test res: %d %d\n", sum_even, sum_odd );
}

void sleep_time( int n ) {
    sleep( n );
}

int main( int argc, char **argv ) {
    test();
    return 0;
}