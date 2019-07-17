#include "cmds.h"
#include <stdio.h>
#include <prpc/lex.h>
#include <prpc/msg.h>
#include <sys/log.h>

PRPC_Parse_Function_t prpc_cmd_parser_get( const char **ptr );
PRPC_CMD( has )
{
    const char *name_begin, *name_end;
    PRPC_Status_t stat = prpc_cmd_parse_args( ptr, id, 1, TOKEN_IDENTIFIER, &name_begin, &name_end );
    if( stat.status == PRPC_OK ) {
        log_verbose(">> Looking for %.*s", name_end-name_begin, name_begin);
        PRPC_Parse_Function_t cmd = prpc_cmd_parser_get(&name_begin);
        prpc_build_result_boolean( resp_buf, max_resp_len, id, cmd != NULL );
    }
    else prpc_build_error_status( resp_buf, max_resp_len, id, stat );
}

PRPC_CMD( hello )
{
    printf("Hello world !\n");
    prpc_build_ok( resp_buf, max_resp_len, id );
}

PRPC_CMD( funky )
{
    printf("YEEEEEEEEEEEEEEEEEEEEEEEEEEEE\n");
    prpc_build_result( resp_buf, max_resp_len, id, 4, PRPC_INT, 1203, PRPC_BOOLEAN, 1, PRPC_STRING, "ARGH", PRPC_IDENTIFIER, "OOOH" );
}

PRPC_CMD( replicate )
{
    int        intg;
    float       num;
    uint8_t boolean;

    PRPC_Status_t stat = prpc_cmd_parse_args( ptr, id, 3,
        PRPC_INT, &intg,
        PRPC_FLOAT, &num,
        PRPC_BOOLEAN, &boolean
    );

    if( stat.status == PRPC_OK ) {
        prpc_build_result( resp_buf, max_resp_len, id, 3, PRPC_INT, intg, PRPC_FLOAT, num, PRPC_BOOLEAN, boolean );
    }

    else prpc_build_error_status( resp_buf, max_resp_len, id, stat );
}

PRPC_Parse_Function_t prpc_cmd_parser_get( const char **ptr )
{
    const char *YYMARKER;

    /*!re2c
        re2c:define:YYCTYPE  = char;
        re2c:define:YYCURSOR = (*ptr);
        re2c:yyfill:enable   = 0;

        *           { return NULL;           }
        'has'       { return prpc_cmd_has;   }
        'hello'     { return prpc_cmd_hello; }
        'funky'     { return prpc_cmd_funky; }
        'replicate' { return prpc_cmd_replicate; }
     */
}

void prpc_process_notification( char *resp, const size_t max_len, const char *notify_name, const char **ptr )
{
}

void prpc_process_cmd( char *resp, const size_t max_len, const PRPC_ID_t id, const char *name, const char **ptr )
{
    PRPC_Parse_Function_t cmd = prpc_cmd_parser_get(&name);
    if( cmd != NULL ) {
        cmd( ptr, resp, max_len, id );
    }

    else {
        prpc_build_error( resp, max_len, id, "Uknown method" );
    }
}
