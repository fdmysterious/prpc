#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/log.h>

#include "lex.h"
#include "msg.h"

void prpc_build_ok( char *buf, const size_t max_len, const size_t id )
{
    snprintf( buf, max_len, "%lu:ok\n", id );
}

void prpc_build_error( char *buf, const size_t max_len, const size_t id, const char *err )
{
    snprintf( buf, max_len, "%lu:error \"%s\"\n", id, err );
}

static void _prpc_build_msg_va( char *buf, const size_t max_len, const size_t id, const char *cmd, const size_t nvals, va_list args )
{
    static const char *bool_vals[] = { "no", "yes" };

    char          *ptr  = buf;
    size_t         len  = max_len;
    size_t      written = 0;

    Token_Type_t ntoken = 0; // EOF for waiting type, then data

    len -= (written = snprintf( ptr, len, "%lu:%s", id, cmd ));
    ptr += written;

    size_t i;
    for( i = 0 ; i < nvals ; i++ ) {
        ntoken = va_arg(args, Token_Type_t);
        switch( ntoken ) {
            case PRPC_IDENTIFIER:
             len -= (written = snprintf( ptr, len, " %s", va_arg(args, const char*) ));
            break;

            case PRPC_STRING:
             len -= (written = snprintf( ptr, len, " \"%s\"", va_arg(args, const char*) ));
            break;

            case PRPC_INT:
             len -= (written = snprintf( ptr, len, " %d", va_arg(args, int) ));
            break;

            case PRPC_FLOAT:
             len -= (written = snprintf( ptr, len, " %f", va_arg(args, double) ));
            break;

            case PRPC_BOOLEAN:
             len -= (written = snprintf( ptr, len, " %s", bool_vals[va_arg(args, int) == 1] ));
            break;
            default:break; // TODO // ERROR ?
        }
        //log_verbose("written = %ld", written);

        if( len > max_len ) len = 0; // Intg overflow protection
        ptr += written;
    }

    if( len <= 1 ) {
        log_error("Not enough place !");
        len -= 1 + (len == 0);
    }

    // Closing resp string
    *(ptr  ) = '\n';
    *(ptr+1) =    0;
}

void prpc_build_msg( char *buf, const size_t max_len, const size_t id, const char *cmd, const size_t nvals, ... )
{
    va_list args;
    va_start( args, nvals );
    _prpc_build_msg_va( buf, max_len, id, cmd, nvals, args );
    va_end( args );
}

void prpc_build_result( char *buf, const size_t max_len, const size_t id, const size_t nvals, ... )
{
    va_list args;
    va_start( args, nvals );
    _prpc_build_msg_va( buf, max_len, id, "result", nvals, args );
    va_end( args );
}

void prpc_build_result_boolean( char *buf, const size_t max_len, const size_t id, const uint8_t val )
{
    //snprintf( buf, max_len, "%lu:result %s\n", id, bool_vals[val == 1]); // == 1 to securise array access (what if val == 2 ?)
    prpc_build_result( buf, max_len, id, 1, PRPC_BOOLEAN, val );
}

void prpc_build_result_int( char *buf, const size_t max_len, const size_t id, const int intg )
{
    //snprintf( buf, max_len, "%lu:result %d", id, intg );
    prpc_build_result( buf, max_len, id, 1, PRPC_INT, intg );
}
