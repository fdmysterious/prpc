/**********
 * main.c *
 **********
 Author      : Florian Dupeyron (Floolfy)
 Description : Program cycle handling here
*/

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <inttypes.h>
#include <stdbool.h>

#include "sys/log.h"

//////////////////////////////////////////
// App functions prototypes
//////////////////////////////////////////
bool    app_init( const int argc, const char * argv[] );
uint8_t app_run();
void    app_exit();

//////////////////////////////////////////
// Signal handler
//////////////////////////////////////////
void sig_handler( int sig )
{
    int ret = EXIT_FAILURE;
    // TODO // Logging with proper routines
    switch( sig ) {
        case SIGSEGV:
        log_error( "Caught segfault signal" );
        break;

        case SIGINT:
        log_warning( "Caught interruption signal" );
        ret = EXIT_SUCCESS;
        break;

        case SIGTERM:
        log_warning( "Caught termination signal" );
        break;

        case SIGALRM:
        log_warning( "Caught alarm signal" );
        break;

        default: // TODO // Add SIGALRM handling
        log_error( "Uknown signal, leaving" );
        break;
    }

    app_exit();
    log_close();
    exit( ret );
}

void setup_signal( const int s )
{
    signal( s, &sig_handler );
}

int main( const int argc, const char * argv[] )
{
    uint8_t status = EXIT_SUCCESS;

    log_open( "app" );
    
    // Signal setup //
    setup_signal( SIGABRT );
    setup_signal( SIGINT  );
    setup_signal( SIGILL  );
    setup_signal( SIGINT  );
    setup_signal( SIGSEGV );
    setup_signal( SIGTERM );
    // End of section //

    // App init and run //
    if( !app_init( argc, argv ) ) {
        log_critic( "Error at app init" );
        exit( EXIT_FAILURE );
    }
    status = app_run();
    // End of section //

    // App closing //
    app_exit();
    log_close();
    // End of section //

    return status;
}
