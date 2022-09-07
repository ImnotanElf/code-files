#include <iostream>

void test() {
    int count = 0;
    for ( int i = 0; i < 100000000; ++i ) {
        count++;
    }
    std::cout << "Test successes!" << std::endl;
}

int main( int argc, char **argv ) {
    test();
    return 0;
}