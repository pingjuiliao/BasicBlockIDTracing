#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void
s0(char* s) {

    if ( s[0] == 'a' ) {
        puts("hello");
    } else if ( s[0] == 'b' ) {
        puts("hi");
    } else {
        puts("boujour\n");
    }
}

void
s1(char* s) {
    if ( strlen(s) < 2 ) return ;

    if ( s[1] == 'a' ) {
        puts("Alice") ;
    } else if ( s[1] == 'b' ) {
        puts("Bob") ;
    } else {
        puts("Cindy");
    }
}

void
check_string(void) { 
    int r = 0 ;
    char buf[128];
    if ( (r = read(0, buf, sizeof(buf))) == 0 ) {
        fprintf(stderr, "Error: read failed\n") ;
        exit(-1) ;
    }
    s0(buf) ;
    s1(buf) ;
}

int
main(int argc, char** argv) {
    check_string() ;
    return 0 ;
}
