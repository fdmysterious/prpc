#include "cmds.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "msg.h"
#include "lex.h"

PRPC_Parse_Function_t prpc_cmd_parser_get( const char **ptr );
PRPC_CMD( has )
{
    Token_t tk;
    if( token_next_arg( ptr, &tk, TOKEN_IDENTIFIER ) == 0 ) {
        const char *cursor = tk.begin;
        PRPC_Parse_Function_t cmd = prpc_cmd_parser_get(&cursor);
        prpc_build_result_boolean( resp_buf, max_resp_len, id, cmd != NULL );
    }

    else prpc_build_error( resp_buf, max_resp_len, id, "Unexcepted token" );
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

PRPC_Parse_Function_t prpc_cmd_parser_get( const char **ptr )
{
    const char *YYMARKER;

    /*!re2c
        re2c:define:YYCTYPE  = char;
        re2c:define:YYCURSOR = (*ptr);
        re2c:yyfill:enable   = 0;

        *       { return NULL;           }
        'has'   { return prpc_cmd_has;   }
        'hello' { return prpc_cmd_hello; }
        'funky' { return prpc_cmd_funky; }
     */
}

void prpc_process_line( const char *line, char *resp_buf, const size_t max_resp_len )
{
    const char *ptr    = line;
    const char *cursor = NULL;
    Token_t tk;
    PRPC_Parse_Function_t cmd;

    memset( resp_buf, 0, max_resp_len );

    do {
        token_next( &ptr, &tk );
        switch( tk.type ) {
            default:break; // TODO // Throw error
            case TOKEN_EOL:case TOKEN_EOF:break; // End of stream

            case TOKEN_COMMAND:
            cursor = tk.data.cmd.name_begin;
            cmd    = prpc_cmd_parser_get(&cursor);
            if( cmd != NULL ) {
                cmd( &ptr, resp_buf, max_resp_len, tk.data.cmd.id );
            }

            else {
                prpc_build_error( resp_buf, max_resp_len, tk.data.cmd.id, "Uknown method" );
            }
            break;
        }
    } while( (tk.type != TOKEN_ERROR) && (tk.type != TOKEN_EOL) && (tk.type != TOKEN_EOF) );
}
