#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdbool.h>

#include <sys/log.h>

#include <pthread.h>

#include <prpc/lex.h>
#include "cmds.h"

#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

//static const char *test_cmds[] = {
//    "0:hello",
//    "1:has hello",
//    "1928:has goodbye",
//    "0:funky",
//    "0:replicate fuck",
//    "0:replicate 10 10.0 yes"
//};


static const char fifo_path[] = "test_fifo";
static int fd;

bool app_init( const int argc, const char * argv[] )
{
    cmds_init();

    mkfifo(fifo_path, 0666);
    fd = open( fifo_path, O_RDONLY );
    if( fd < 0 ) {
        log_error("Failed to open fifo : %s", strerror(errno) );
        return false;
    }

    return true;
}

uint8_t app_run()
{
    char line[2048];
    char resp[2048];
    //const size_t n_cmds = sizeof(test_cmds)/sizeof(char*);
    //size_t i;
    //for( i = 0 ; i < n_cmds ; i++ ) {
    //    log_notice( "Processing command : %s", test_cmds[i] );
    //    prpc_process_line( test_cmds[i], resp, 2048 );
    //    log_notice(" >> %s", resp );
    //}
 
    char      c    = 0;
    ssize_t rcount = 0;
    size_t  idx    = 0;

    do {
        idx = 0;
        memset( line, 0, 2048 );
        c = 0;
        do {
            rcount = read( fd, &c, 1 );
            switch( c ) {
                default:
                line[idx++] = c;
                if( idx >= 2048 ) {
                    idx = 0; // Aborting line
                    break;
                }
                break;

                case '\0':
                idx=0; // Aborting line
                break;

                case'\n':case'\r':break;
            }
        } while( (rcount > 0) && (c != '\n') );

        if( idx > 0 ) {
            log_notice("Processing command : %s", line );
            prpc_process_line( line, resp, 2048 );
            log_notice(" >> %s", resp );
        }
    } while( 1 );

    return EXIT_SUCCESS;
}

void app_exit()
{
    log_notice("Leaving app");
}
