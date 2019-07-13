#include "lex.h"
#include "parse.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

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
const char *token_next( const char *start, Token_t *dst )
{
    const char *YYMARKER;
    const char *YYCURSOR = start;

    const char *id, *sep, *name;

    dst->begin = NULL;
    dst->end   = NULL;

    /*!stags:re2c format = 'const char *@@;'; */
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:yyfill:enable=0;

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
            dst->end   = YYCURSOR-1;

            return YYCURSOR;
        }

        *   { dst->type = TOKEN_ERROR;     return YYCURSOR; }
        end { dst->type = TOKEN_EOF;       return YYCURSOR; }
        eol { dst->type = TOKEN_EOL;       return YYCURSOR; }
        wh  { dst->type = TOKEN_SEPARATOR; return YYCURSOR; }

        float {
            dst->type     = TOKEN_FLOAT;
            dst->begin    = start;
            dst->end      = YYCURSOR;

            dst->data.num = parse_float( dst->begin, dst->end );

            return YYCURSOR;
        }

        int {
            dst->type      = TOKEN_INT;
            dst->begin     = start;
            dst->end       = YYCURSOR;
            dst->data.intg = parse_int( dst->begin, dst->end );

            return YYCURSOR;
        }

        bool_true {
            dst->type         = TOKEN_BOOLEAN;
            dst->begin        = start;
            dst->end          = YYCURSOR;
            dst->data.boolean = 1;

            return YYCURSOR;
        }

        bool_false {
            dst->type         = TOKEN_BOOLEAN;
            dst->begin        = start;
            dst->end          = YYCURSOR;
            dst->data.boolean = 0;

            return YYCURSOR;
        }

        @id int @sep ':' @name identifier {
            dst->type  = TOKEN_COMMAND;
            dst->begin = start;
            dst->end   = YYCURSOR;
            
            dst->data.cmd.id         = parse_int( id, sep );
            dst->data.cmd.name_begin = name;
            dst->data.cmd.name_end   = YYCURSOR;

            return YYCURSOR;
        }

        identifier {
            dst->type  = TOKEN_IDENTIFIER;
            dst->begin = start;
            dst->end   = YYCURSOR;

            return YYCURSOR;
        }
     */
}
