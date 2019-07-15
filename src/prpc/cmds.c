#include "cmds.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "msg.h"
#include "lex.h"

// TODO // Some kind of evil macro to not restrict attributes to gcc ?

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
