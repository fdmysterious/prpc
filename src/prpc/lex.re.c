#include "lex.h"
#include "parse.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <sys/log.h>

const char *token_type_str( Token_Type_t type )
{
    static const char *token_str[] = {
        "TOKEN_ERROR",
        "TOKEN_EOL",
        "TOKEN_EOF",
        "TOKEN_SEPARATOR",

        "TOKEN_STRING",
        "TOKEN_INT",
        "TOKEN_FLOAT",
        "TOKEN_BOOLEAN",
        "TOKEN_IDENTIFIER",
        "TOKEN_COMMAND"
    };

    return token_str[type];
}

//////////////////////////////////////////
// Main lexer thing
//////////////////////////////////////////
void token_next( const char **ptr, Token_t *dst )
{
    const char *YYMARKER;
    const char *id, *sep, *name;

    const char *start = *ptr;

    dst->begin = NULL;
    dst->end   = NULL;

    /*!stags:re2c format = 'const char *@@;'; */
    /*!re2c
        re2c:define:YYCTYPE  = char;
        re2c:define:YYCURSOR = (*ptr);
        re2c:yyfill:enable   = 0;

        end        = "\x00";
        eol        = "[\r\n]+";
        wh         = [ \t]*;

        identifier = [a-zA-Z0-9\-_\.]+;
        bool_true  = 'yes';
        bool_false = 'no';

        int        = '-'?[0-9]+;
        float      = '-'?[0-9]+[.][0-9]+;
        str        = ["]( . \ end |[\]["])*["];
        
        str {
            dst->type  = TOKEN_STRING;
            dst->begin = start+1;
            dst->end   = (*ptr) - 1;

            return;
        }

        *   { dst->type   = TOKEN_ERROR;     return; }
        end { dst->type   = TOKEN_EOF;       return; }
        eol { dst->type   = TOKEN_EOL;       return; }
        wh  { dst->type   = TOKEN_SEPARATOR; return; }

        float {
            dst->type     = TOKEN_FLOAT;
            dst->begin    = start;
            dst->end      = (*ptr);

            dst->data.num = parse_float( dst->begin, dst->end );

            return;
        }

        int {
            dst->type      = TOKEN_INT;
            dst->begin     = start;
            dst->end       = (*ptr);
            dst->data.intg = parse_int( dst->begin, dst->end );

            return;
        }

        bool_true {
            dst->type         = TOKEN_BOOLEAN;
            dst->begin        = start;
            dst->end          = (*ptr);
            dst->data.boolean = 1;

            return;
        }

        bool_false {
            dst->type         = TOKEN_BOOLEAN;
            dst->begin        = start;
            dst->end          = (*ptr);
            dst->data.boolean = 0;

            return;
        }

        @id int @sep ':' @name identifier {
            dst->type  = TOKEN_COMMAND;
            dst->begin = start;
            dst->end   = (*ptr);
            
            dst->data.cmd.id         = parse_int( id, sep );
            dst->data.cmd.name_begin = name;
            dst->data.cmd.name_end   = (*ptr);

            return;
        }

        identifier {
            dst->type  = TOKEN_IDENTIFIER;
            dst->begin = start;
            dst->end   = (*ptr);

            return;
        }
     */
}

int token_next_except( const char **ptr, Token_t *dst, const Token_Type_t type )
{
    token_next( ptr, dst );
    if( dst->type != type ) {
        // TODO // Invalid type error
        log_error( "Invalid token : excepted %s, got %s", token_type_str(type), token_type_str(dst->type) );
        return 1;
    }

    else return 0;
}

int token_next_arg( const char **ptr, Token_t *dst, const Token_Type_t type )
{
    int ret;
    if( (ret = token_next_except( ptr, dst, TOKEN_SEPARATOR ) != 0) ) return ret;
    return token_next_except( ptr, dst, type );
}
