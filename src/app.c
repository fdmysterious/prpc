#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdbool.h>

#include <sys/log.h>

#include <pthread.h>

#include <prpc/lex.h>
#include <cmds.h>

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

bool app_init( const int argc, const char * argv[] )
{
    cmds_init();

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
 
    char *ptr;
    do {
        memset( line, 0, 2048 );

        ptr = fgets( line, 2048, stdin );
        if( ptr ) {
            line[strlen(line)-1]=0;
            log_notice( "Processing line %s", line );
            prpc_process_line( line, resp, 2048 );
            log_notice( ">> %s", resp );
            
        }
        log_debug("%d", ptr != NULL);
    } while( ptr != NULL );

    return EXIT_SUCCESS;
}

void app_exit()
{
    log_notice("Leaving app");
}
