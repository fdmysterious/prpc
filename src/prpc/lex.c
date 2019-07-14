/* Generated by re2c 1.1.1 on Sun Jul 14 09:06:40 2019 */
#line 1 "src/prpc/lex.re.c"
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

    const char *yyt1;const char *yyt2;
    
#line 47 "src/prpc/lex.c"
{
	char yych;
	unsigned int yyaccept = 0;
	yych = *(*ptr);
	switch (yych) {
	case 0x00:	goto yy2;
	case '\t':
	case ' ':	goto yy6;
	case '"':	goto yy9;
	case '-':
		yyt1 = (*ptr);
		goto yy10;
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
	case 'z':	goto yy12;
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
		goto yy14;
	case 'N':
	case 'n':	goto yy17;
	case 'Y':
	case 'y':	goto yy18;
	case '[':	goto yy19;
	default:	goto yy4;
	}
yy2:
	++(*ptr);
#line 69 "src/prpc/lex.re.c"
	{ dst->type   = TOKEN_EOF;       return; }
#line 133 "src/prpc/lex.c"
yy4:
	++(*ptr);
yy5:
#line 68 "src/prpc/lex.re.c"
	{ dst->type   = TOKEN_ERROR;     return; }
#line 139 "src/prpc/lex.c"
yy6:
	yych = *++(*ptr);
	switch (yych) {
	case '\t':
	case ' ':	goto yy6;
	default:	goto yy8;
	}
yy8:
#line 71 "src/prpc/lex.re.c"
	{ dst->type   = TOKEN_SEPARATOR; return; }
#line 150 "src/prpc/lex.c"
yy9:
	yyaccept = 0;
	yych = *(YYMARKER = ++(*ptr));
	switch (yych) {
	case 0x00:
	case '\n':	goto yy5;
	default:	goto yy21;
	}
yy10:
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
	case '9':	goto yy14;
	default:	goto yy13;
	}
yy11:
#line 122 "src/prpc/lex.re.c"
	{
            dst->type  = TOKEN_IDENTIFIER;
            dst->begin = start;
            dst->end   = (*ptr);

            return;
        }
#line 183 "src/prpc/lex.c"
yy12:
	yych = *++(*ptr);
yy13:
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
	case 'z':	goto yy12;
	default:	goto yy11;
	}
yy14:
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
	case 'z':	goto yy12;
	case '.':	goto yy26;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy14;
	case ':':	goto yy27;
	default:	goto yy16;
	}
yy16:
#line 83 "src/prpc/lex.re.c"
	{
            dst->type      = TOKEN_INT;
            dst->begin     = start;
            dst->end       = (*ptr);
            dst->data.intg = parse_int( dst->begin, dst->end );

            return;
        }
#line 337 "src/prpc/lex.c"
yy17:
	yych = *++(*ptr);
	switch (yych) {
	case 'O':
	case 'o':	goto yy28;
	default:	goto yy13;
	}
yy18:
	yych = *++(*ptr);
	switch (yych) {
	case 'E':
	case 'e':	goto yy30;
	default:	goto yy13;
	}
yy19:
	yyaccept = 0;
	yych = *(YYMARKER = ++(*ptr));
	switch (yych) {
	case '\r':	goto yy31;
	default:	goto yy5;
	}
yy20:
	yych = *++(*ptr);
yy21:
	switch (yych) {
	case 0x00:
	case '\n':	goto yy22;
	case '"':	goto yy23;
	default:	goto yy20;
	}
yy22:
	(*ptr) = YYMARKER;
	switch (yyaccept) {
	case 0: 	goto yy5;
	case 1: 	goto yy16;
	default:	goto yy25;
	}
yy23:
	yyaccept = 2;
	yych = *(YYMARKER = ++(*ptr));
	switch (yych) {
	case 0x00:
	case '\n':	goto yy25;
	case '"':	goto yy23;
	default:	goto yy20;
	}
yy25:
#line 60 "src/prpc/lex.re.c"
	{
            dst->type  = TOKEN_STRING;
            dst->begin = start+1;
            dst->end   = (*ptr) - 1;

            return;
        }
#line 393 "src/prpc/lex.c"
yy26:
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
	case '9':	goto yy32;
	default:	goto yy13;
	}
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
		goto yy35;
	default:	goto yy22;
	}
yy28:
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
	case 'z':	goto yy12;
	default:	goto yy29;
	}
yy29:
#line 101 "src/prpc/lex.re.c"
	{
            dst->type         = TOKEN_BOOLEAN;
            dst->begin        = start;
            dst->end          = (*ptr);
            dst->data.boolean = 0;

            return;
        }
#line 561 "src/prpc/lex.c"
yy30:
	yych = *++(*ptr);
	switch (yych) {
	case 'S':
	case 's':	goto yy38;
	default:	goto yy13;
	}
yy31:
	yych = *++(*ptr);
	switch (yych) {
	case '\n':	goto yy40;
	default:	goto yy22;
	}
yy32:
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
	case 'z':	goto yy12;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy32;
	default:	goto yy34;
	}
yy34:
#line 73 "src/prpc/lex.re.c"
	{
            dst->type     = TOKEN_FLOAT;
            dst->begin    = start;
            dst->end      = (*ptr);

            dst->data.num = parse_float( dst->begin, dst->end );

            return;
        }
#line 656 "src/prpc/lex.c"
yy35:
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
	case 'z':	goto yy35;
	default:	goto yy37;
	}
yy37:
	id = yyt1;
	name = yyt2;
	sep = yyt2 - 1;
#line 110 "src/prpc/lex.re.c"
	{
            dst->type  = TOKEN_COMMAND;
            dst->begin = start;
            dst->end   = (*ptr);
            
            dst->data.cmd.id         = parse_int( id, sep );
            dst->data.cmd.name_begin = name;
            dst->data.cmd.name_end   = (*ptr);

            return;
        }
#line 743 "src/prpc/lex.c"
yy38:
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
	case 'z':	goto yy12;
	default:	goto yy39;
	}
yy39:
#line 92 "src/prpc/lex.re.c"
	{
            dst->type         = TOKEN_BOOLEAN;
            dst->begin        = start;
            dst->end          = (*ptr);
            dst->data.boolean = 1;

            return;
        }
#line 824 "src/prpc/lex.c"
yy40:
	yych = *++(*ptr);
	switch (yych) {
	case ']':	goto yy41;
	default:	goto yy22;
	}
yy41:
	yych = *++(*ptr);
	switch (yych) {
	case '+':	goto yy42;
	default:	goto yy22;
	}
yy42:
	++(*ptr);
#line 70 "src/prpc/lex.re.c"
	{ dst->type   = TOKEN_EOL;       return; }
#line 841 "src/prpc/lex.c"
}
#line 129 "src/prpc/lex.re.c"

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
