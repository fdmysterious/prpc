#include "cmds.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "types.h"
#include "msg.h"
#include "lex.h"

void prpc_process_line( const char *line, char *resp_buf, const size_t max_resp_len )
{
    const char *ptr  = line;
    const char *name = NULL;
    Token_t tk;

    memset( resp_buf, 0, max_resp_len );

    do {
        token_next( &ptr, &tk );
        switch( tk.type ) {
            default:break; // TODO // Throw error
            case TOKEN_EOL:case TOKEN_EOF:break; // End of stream

            case TOKEN_COMMAND:
            name = tk.data.cmd.name_begin;
            if( tk.data.cmd.id == PRPC_ID_NOTIFY ) prpc_process_notification( resp_buf, max_resp_len, name, &ptr );
            else                                   prpc_process_cmd( resp_buf, max_resp_len, tk.data.cmd.id, name, &ptr );
            break;
        }
    } while( (tk.type != TOKEN_ERROR) && (tk.type != TOKEN_EOL) && (tk.type != TOKEN_EOF) );
}

//////////////////////////////////////////
// Parse arguments
//////////////////////////////////////////
PRPC_Status_t prpc_cmd_parse_args( const char **ptr, const size_t id, const size_t n_args, ... )
{
    PRPC_Status_t ret = { .status = PRPC_OK };
    Token_Type_t tt; // Excepted token type
    Token_t tk;      // Parsed token

    va_list args;

    va_start( args, n_args );
    size_t i;
    for( i = 0 ; (i < n_args) && (ret.status == PRPC_OK) ; i++ ) {
        tt = va_arg( args, Token_Type_t );
        
        ret = token_next_arg( ptr, &tk, tt );
        if( ret.status == PRPC_OK ) {
            if( (tt == TOKEN_STRING) || (tt == TOKEN_IDENTIFIER) ) {
                const char **begin, **end;
                begin = va_arg( args, const char** );
                end   = va_arg( args, const char** );

                (*begin) = tk.begin;
                (*end)   = tk.end;
            }
            
            else if( tt == TOKEN_INT ) {
                int *intg = va_arg( args, int* );
                (*intg) = tk.data.intg;
            }

            else if( tt == TOKEN_FLOAT ) {
                float *ff = va_arg( args, float* );
                (*ff) = tk.data.num;
            }

            else if( tt == TOKEN_BOOLEAN ) {
                uint8_t *bb = va_arg( args, uint8_t* );
                (*bb) = tk.data.boolean;
            }

            else { // Should not go here
                ret.status = PRPC_ERROR_UNKNOWN;
            }
        }
    }
    va_end( args );

    return ret;
}
