/* Generated by re2c 1.1.1 on Mon Jul 15 20:10:04 2019 */
#line 1 "src/prpc/cmds.re.c"
#include "cmds.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "msg.h"
#include "lex.h"

#define PRPC_CMD( name ) void prpc_cmd_ ## name( const size_t id, const char **ptr, char *resp_buf, const size_t max_resp_len )

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

    
#line 44 "src/prpc/cmds.c"
{
	char yych;
	yych = *(*ptr);
	switch (yych) {
	case 'F':
	case 'f':	goto yy4;
	case 'H':
	case 'h':	goto yy5;
	default:	goto yy2;
	}
yy2:
	++(*ptr);
yy3:
#line 45 "src/prpc/cmds.re.c"
	{ return NULL;           }
#line 60 "src/prpc/cmds.c"
yy4:
	yych = *(YYMARKER = ++(*ptr));
	switch (yych) {
	case 'U':
	case 'u':	goto yy6;
	default:	goto yy3;
	}
yy5:
	yych = *(YYMARKER = ++(*ptr));
	switch (yych) {
	case 'A':
	case 'a':	goto yy8;
	case 'E':
	case 'e':	goto yy9;
	default:	goto yy3;
	}
yy6:
	yych = *++(*ptr);
	switch (yych) {
	case 'N':
	case 'n':	goto yy10;
	default:	goto yy7;
	}
yy7:
	(*ptr) = YYMARKER;
	goto yy3;
yy8:
	yych = *++(*ptr);
	switch (yych) {
	case 'S':
	case 's':	goto yy11;
	default:	goto yy7;
	}
yy9:
	yych = *++(*ptr);
	switch (yych) {
	case 'L':
	case 'l':	goto yy13;
	default:	goto yy7;
	}
yy10:
	yych = *++(*ptr);
	switch (yych) {
	case 'K':
	case 'k':	goto yy14;
	default:	goto yy7;
	}
yy11:
	++(*ptr);
#line 46 "src/prpc/cmds.re.c"
	{ return prpc_cmd_has;   }
#line 112 "src/prpc/cmds.c"
yy13:
	yych = *++(*ptr);
	switch (yych) {
	case 'L':
	case 'l':	goto yy15;
	default:	goto yy7;
	}
yy14:
	yych = *++(*ptr);
	switch (yych) {
	case 'Y':
	case 'y':	goto yy16;
	default:	goto yy7;
	}
yy15:
	yych = *++(*ptr);
	switch (yych) {
	case 'O':
	case 'o':	goto yy18;
	default:	goto yy7;
	}
yy16:
	++(*ptr);
#line 48 "src/prpc/cmds.re.c"
	{ return prpc_cmd_funky; }
#line 138 "src/prpc/cmds.c"
yy18:
	++(*ptr);
#line 47 "src/prpc/cmds.re.c"
	{ return prpc_cmd_hello; }
#line 143 "src/prpc/cmds.c"
}
#line 49 "src/prpc/cmds.re.c"

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
                cmd( tk.data.cmd.id, &ptr, resp_buf, max_resp_len );
            }

            else {
                prpc_build_error( resp_buf, max_resp_len, tk.data.cmd.id, "Uknown method" );
            }
            break;
        }
    } while( (tk.type != TOKEN_ERROR) && (tk.type != TOKEN_EOL) && (tk.type != TOKEN_EOF) );
}
