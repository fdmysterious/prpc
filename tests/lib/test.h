/**************************
 * Some routines for unit *
 * testing                *
 **************************/
// Florian Dupeyron (floolfy)
// September 2018

//////////////////////////////////////////
#include <sys/log.h>
#include <signal.h>
//////////////////////////////////////////

//////////////////////////////////////////
// Asserts
//////////////////////////////////////////
#define test_assert( exp , ... ) \
    do { \
        if( !( exp ) ) { \
            log_plog( LOG_LVL_ERROR, __FILENAME__, __LINE__, __VA_ARGS__ ); \
            raise( SIGABRT ); \
        }\
    } while(0)
