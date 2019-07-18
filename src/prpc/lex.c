/* Generated by re2c 1.1.1 on Thu Jul 18 21:04:50 2019 */
#line 1 "src/prpc/lex.re.c"
#include "lex.h"
#include "parse.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#include "msg.h"

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

    const char *yyt1;const char *yyt2;
    
#line 48 "src/prpc/lex.c"
{
	char yych;
	unsigned int yyaccept = 0;
	yych = *(*ptr);
	switch (yych) {
	case 0x00:	goto yy2;
	case '\t':
	case ' ':	goto yy6;
	case '"':	goto yy9;
	case '*':
		yyt1 = (*ptr);
		goto yy10;
	case '-':
		yyt1 = (*ptr);
		goto yy11;
	case '.':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'z':	goto yy13;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		yyt1 = (*ptr);
		goto yy15;
	case 'N':
	case 'n':	goto yy18;
	case 'Y':
	case 'y':	goto yy19;
	case '[':	goto yy20;
	default:	goto yy4;
	}
yy2:
	++(*ptr);
#line 70 "src/prpc/lex.re.c"
	{ dst->type   = TOKEN_EOF;       return; }
#line 137 "src/prpc/lex.c"
yy4:
	++(*ptr);
yy5:
#line 69 "src/prpc/lex.re.c"
	{ dst->type   = TOKEN_ERROR;     return; }
#line 143 "src/prpc/lex.c"
yy6:
	yych = *++(*ptr);
	switch (yych) {
	case '\t':
	case ' ':	goto yy6;
	default:	goto yy8;
	}
yy8:
#line 72 "src/prpc/lex.re.c"
	{ dst->type   = TOKEN_SEPARATOR; return; }
#line 154 "src/prpc/lex.c"
yy9:
	yyaccept = 0;
	yych = *(YYMARKER = ++(*ptr));
	switch (yych) {
	case 0x00:
	case '\n':	goto yy5;
	default:	goto yy22;
	}
yy10:
	yyaccept = 0;
	yych = *(YYMARKER = ++(*ptr));
	switch (yych) {
	case ':':	goto yy27;
	default:	goto yy5;
	}
yy11:
	yych = *++(*ptr);
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy15;
	default:	goto yy14;
	}
yy12:
#line 125 "src/prpc/lex.re.c"
	{
            dst->type  = TOKEN_IDENTIFIER;
            dst->begin = start;
            dst->end   = (*ptr);

            return;
        }
#line 194 "src/prpc/lex.c"
yy13:
	yych = *++(*ptr);
yy14:
	switch (yych) {
	case '-':
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy13;
	default:	goto yy12;
	}
yy15:
	yyaccept = 1;
	yych = *(YYMARKER = ++(*ptr));
	switch (yych) {
	case '-':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy13;
	case '.':	goto yy28;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy15;
	case ':':	goto yy27;
	default:	goto yy17;
	}
yy17:
#line 84 "src/prpc/lex.re.c"
	{
            dst->type      = TOKEN_INT;
            dst->begin     = start;
            dst->end       = (*ptr);
            dst->data.intg = parse_int( dst->begin, dst->end );

            return;
        }
#line 348 "src/prpc/lex.c"
yy18:
	yych = *++(*ptr);
	switch (yych) {
	case 'O':
	case 'o':	goto yy29;
	default:	goto yy14;
	}
yy19:
	yych = *++(*ptr);
	switch (yych) {
	case 'E':
	case 'e':	goto yy31;
	default:	goto yy14;
	}
yy20:
	yyaccept = 0;
	yych = *(YYMARKER = ++(*ptr));
	switch (yych) {
	case '\r':	goto yy32;
	default:	goto yy5;
	}
yy21:
	yych = *++(*ptr);
yy22:
	switch (yych) {
	case 0x00:
	case '\n':	goto yy23;
	case '"':	goto yy24;
	default:	goto yy21;
	}
yy23:
	(*ptr) = YYMARKER;
	switch (yyaccept) {
	case 0: 	goto yy5;
	case 1: 	goto yy17;
	default:	goto yy26;
	}
yy24:
	yyaccept = 2;
	yych = *(YYMARKER = ++(*ptr));
	switch (yych) {
	case 0x00:
	case '\n':	goto yy26;
	case '"':	goto yy24;
	default:	goto yy21;
	}
yy26:
#line 61 "src/prpc/lex.re.c"
	{
            dst->type  = TOKEN_STRING;
            dst->begin = start+1;
            dst->end   = (*ptr) - 1;

            return;
        }
#line 404 "src/prpc/lex.c"
yy27:
	yych = *++(*ptr);
	switch (yych) {
	case '-':
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':
		yyt2 = (*ptr);
		goto yy33;
	default:	goto yy23;
	}
yy28:
	yych = *++(*ptr);
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy36;
	default:	goto yy14;
	}
yy29:
	yych = *++(*ptr);
	switch (yych) {
	case '-':
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy13;
	default:	goto yy30;
	}
yy30:
#line 102 "src/prpc/lex.re.c"
	{
            dst->type         = TOKEN_BOOLEAN;
            dst->begin        = start;
            dst->end          = (*ptr);
            dst->data.boolean = 0;

            return;
        }
#line 572 "src/prpc/lex.c"
yy31:
	yych = *++(*ptr);
	switch (yych) {
	case 'S':
	case 's':	goto yy39;
	default:	goto yy14;
	}
yy32:
	yych = *++(*ptr);
	switch (yych) {
	case '\n':	goto yy41;
	default:	goto yy23;
	}
yy33:
	yych = *++(*ptr);
	switch (yych) {
	case '-':
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy33;
	default:	goto yy35;
	}
yy35:
	id = yyt1;
	name = yyt2;
	sep = yyt2 - 1;
#line 111 "src/prpc/lex.re.c"
	{
            dst->type  = TOKEN_COMMAND;
            dst->begin = start;
            dst->end   = (*ptr);
            
            if( *id == '*' ) dst->data.cmd.id = PRPC_ID_NOTIFY;
            else            dst->data.cmd.id = parse_int( id, sep );

            dst->data.cmd.name_begin = name;
            dst->data.cmd.name_end   = (*ptr);

            return;
        }
#line 674 "src/prpc/lex.c"
yy36:
	yych = *++(*ptr);
	switch (yych) {
	case '-':
	case '.':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy13;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy36;
	default:	goto yy38;
	}
yy38:
#line 74 "src/prpc/lex.re.c"
	{
            dst->type     = TOKEN_FLOAT;
            dst->begin    = start;
            dst->end      = (*ptr);

            dst->data.num = parse_float( dst->begin, dst->end );

            return;
        }
#line 756 "src/prpc/lex.c"
yy39:
	yych = *++(*ptr);
	switch (yych) {
	case '-':
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy13;
	default:	goto yy40;
	}
yy40:
#line 93 "src/prpc/lex.re.c"
	{
            dst->type         = TOKEN_BOOLEAN;
            dst->begin        = start;
            dst->end          = (*ptr);
            dst->data.boolean = 1;

            return;
        }
#line 837 "src/prpc/lex.c"
yy41:
	yych = *++(*ptr);
	switch (yych) {
	case ']':	goto yy42;
	default:	goto yy23;
	}
yy42:
	yych = *++(*ptr);
	switch (yych) {
	case '+':	goto yy43;
	default:	goto yy23;
	}
yy43:
	++(*ptr);
#line 71 "src/prpc/lex.re.c"
	{ dst->type   = TOKEN_EOL;       return; }
#line 854 "src/prpc/lex.c"
}
#line 132 "src/prpc/lex.re.c"

}

PRPC_Status_t token_next_except( const char **ptr, Token_t *dst, const Token_Type_t type )
{
    PRPC_Status_t r = { .status = PRPC_OK };

    token_next( ptr, dst );
    if( dst->type != type ) {
        r.status = PRPC_ERROR_UNEXCEPTED_TOKEN;
        r.token.excepted = type;
        r.token.got      = dst->type;
    }

    return r;
}

PRPC_Status_t token_next_arg( const char **ptr, Token_t *dst, const Token_Type_t type )
{
    PRPC_Status_t r = token_next_except( ptr, dst, TOKEN_SEPARATOR );
    if( r.status != PRPC_OK ) return r;
    return token_next_except( ptr, dst, type );
}

