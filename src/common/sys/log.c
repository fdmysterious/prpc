//////////////////////////////////////////
#include "log.h"
#include "ansiterm.h"

#include <string.h>
#include <pthread.h>
#include <signal.h>

#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdatomic.h>
//////////////////////////////////////////

//////////////////////////////////////////
// Various constants
//////////////////////////////////////////
static const char * log_level_str[] = {
    "debug  ",
    "verbose",
    "notice ",
    "warning",
    "error  ",
    "critic "
};

#ifdef LOG_ENABLE_STDERR
static const char * log_colors[] = {
    ANSITERM_STR( ANSITERM_GFX_MODE_NORMAL , ANSITERM_FG_MAGENTA), // Debug
    ANSITERM_STR( ANSITERM_GFX_MODE_NORMAL , ANSITERM_FG_CYAN   ), // Verbose
    ANSITERM_STR( ANSITERM_GFX_MODE_NORMAL , ANSITERM_FG_BLUE   ), // Notice
    ANSITERM_STR( ANSITERM_GFX_MODE_BOLD   , ANSITERM_FG_YELLOW ), // Warning
    ANSITERM_STR( ANSITERM_GFX_MODE_BOLD   , ANSITERM_FG_RED    ), // Error
    ANSITERM_STR( ANSITERM_GFX_MODE_REVERSE, ANSITERM_FG_RED    )  // Critic
};

static const char * log_color_reset = ANSITERM_GFX_RESET;

static bool color_enabled = false;
#endif

#ifdef LOG_ENABLE_SYSLOG
static const int syslog_lvl[] = {
    LOG_DEBUG,
    LOG_INFO,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERR,
    LOG_CRIT
};
#endif

//////////////////////////////////////////
// Public interface
//////////////////////////////////////////
void log_open( const char * name )
{
#ifdef LOG_ENABLE_SYSLOG
	#ifdef BUILD_DEBUG
	setlogmask( LOG_UPTO(LOG_DEBUG) );
	#else
	setlogmask( LOG_UPTO(LOG_NOTICE) );
	#endif
	openlog( name, LOG_PID | LOG_NDELAY, LOG_USER );

#endif

#ifdef LOG_ENABLE_STDERR
    color_enabled = ansiterm_color_support( stderr );
#endif
}

void log_close()
{
}

void log_plog( enum LogLevel lvl, const char * file, const size_t line, const char * msg, ... )
{
    va_list args;
#ifdef LOG_ENABLE_SYSLOG
    static char syslog_buff[2048];
#endif

#ifdef LOG_ENABLE_STDERR
    if( color_enabled ) fprintf( stderr, log_colors[lvl] );
    fprintf( stderr, "%s:%ld // %s // ", file, line, log_level_str[lvl] );
#endif

    va_start( args, msg );
#ifdef LOG_ENABLE_STDERR
        vfprintf( stderr, msg, args );
#endif
#ifdef LOG_ENABLE_SYSLOG
        memset( syslog_buff, 0, 2048 * sizeof(char) );
        snprintf( syslog_buff, 2047, "%s:%ld // %s // ", file, line, log_level_str[lvl] );
        vsnprintf( syslog_buff + strlen(syslog_buff), 2047, msg, args );
        syslog( syslog_lvl[lvl], syslog_buff );
#endif
    va_end( args );
#ifdef LOG_ENABLE_STDERR
    if( color_enabled ) fprintf( stderr, log_color_reset );
    fprintf( stderr, "\n" );
#endif

}
