#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdbool.h>

#include <sys/log.h>

#include <pthread.h>

#include <lex.h>

static char *test_str = "0293:dfkjsdf This is yes no yess nooo \"yessaiiiiii 923:loo\\\"ooooooliiii\" DEAD 23 -28 -382.49 99.33";

bool app_init( const int argc, const char * argv[] )
{
    return true;
}

uint8_t app_run()
{
    log_notice("Parsing string :");
    char *ptr = test_str;
    Token_t tok;

    do {
        ptr = token_next(ptr, &tok);
        if( tok.type == TOKEN_SEPARATOR ) continue;
        log_notice( ">> Got token type : %s ; \"%.*s\"", token_type_str(tok.type), tok.end-tok.begin, tok.begin );
        switch( tok.type ) {
            case TOKEN_STRING    : log_verbose(">> string : %.*s", tok.data.str.end-tok.data.str.begin, tok.data.str.begin ); break;
            case TOKEN_INT       : log_verbose(">> int    : %d"  , tok.data.intg    ); break;
            case TOKEN_FLOAT     : log_verbose(">> float  : %f"  , tok.data.num     ); break;
            case TOKEN_BOOLEAN   : log_verbose(">> bool   : %d"  , tok.data.boolean ); break;
            case TOKEN_COMMAND   : log_verbose(">> ID : %d, name : %.*s", tok.data.cmd.id, tok.data.cmd.name_end-tok.data.cmd.name_begin, tok.data.cmd.name_begin); break;
            default:break;
        }
    } while( (tok.type != TOKEN_EOF) && (tok.type != TOKEN_ERROR) );

    return EXIT_SUCCESS;
}

void app_exit()
{
    log_notice("Leaving app");
}
