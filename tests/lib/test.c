#include "test.h"

#include <signal.h>
#include <sys/log.h>


int test_run();
void test_exit();

void sig_handler( int sig )
{
    int ret = EXIT_FAILURE;
    switch( sig ) {
        case SIGSEGV : log_critic  ( "Caught SIGSEGV" ); break;
        case SIGINT  : log_warning ( "Caught SIGINT"  ); break;
        case SIGTERM : log_error   ( "Caught SIGTERM" ); break;
        case SIGALRM : log_warning ( "Caught SIGALRM" ); break;
        case SIGABRT : log_error   ( "Aborting"       ); break;

        default : log_error("Sighandler called with uknown signo %d", sig ); break;
    }

    test_exit();
    log_close();
    exit( ret );
}

void sig_setup( const int s )
{
    signal( s, &sig_handler );
}

int main(int argc, const char *argv[])
{
    log_open( "test" );
    sig_setup( SIGABRT );
    sig_setup( SIGINT  );
    sig_setup( SIGILL  );
    sig_setup( SIGINT  );
    sig_setup( SIGSEGV );
    sig_setup( SIGTERM );

    int ret = test_run();

    test_exit();
    log_close();

    return ret;
}
