
#include "libBBID.h" 
void
_bbid_linear(void) {
    static BBID_T cnt = 0 ;
    BBID_T prefix   = 0;
    BBID_T id = (prefix + (cnt++)); 
}


