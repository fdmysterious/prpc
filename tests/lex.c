/**************
 * Lexer test *
 **************/
// Florian Dupeyron
// July 2019

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <prpc/lex.h>

#include <test.h>

static const char *test_str   = "0293:test_command *:notif This yes no yess nooo \"Hello \\\" World !\" 10 -10 -10.2 10.2";
static const char *test_str_2 = " identifier \"string\" 1 1.0 no";

#define test_token_type( tk, ex ) test_assert( tk.type == ex, "Invalid token type : %s != %s", token_type_str( tk.type ), token_type_str(ex) )
void test_lexer()
{
    Token_t tk;
    const char *ptr = test_str;
    
    token_next(&ptr, &tk);
    test_token_type( tk, TOKEN_COMMAND );
    test_assert( tk.data.cmd.id == 293, "Invalid Command id : %d != %d", tk.data.cmd.id, 293 );
    test_assert(
        strncmp(tk.data.cmd.name_begin, "test_command", strlen("test_command") ) == 0,
        "Invalid cmd name, %.*s != test_command", 
        tk.data.cmd.name_end-tk.data.cmd.name_begin,
        tk.data.cmd.name_begin
    );

    token_next(&ptr, &tk);
    test_token_type( tk, TOKEN_SEPARATOR );

    token_next(&ptr, &tk);
    test_token_type( tk, TOKEN_COMMAND );
    test_assert( tk.data.cmd.id == PRPC_ID_NOTIFY, "Invalid Command id : %d != %d", tk.data.cmd.id, PRPC_ID_NOTIFY );
    test_assert(
        strncmp(tk.data.cmd.name_begin, "notif", strlen("notif") ) == 0,
        "Invalid cmd name, %.*s != notif", 
        tk.data.cmd.name_end-tk.data.cmd.name_begin,
        tk.data.cmd.name_begin
    );

    token_next(&ptr, &tk);
    test_token_type( tk, TOKEN_SEPARATOR );

    token_next(&ptr, &tk);
    test_token_type( tk, TOKEN_IDENTIFIER );
    test_assert(
        strncmp( tk.begin, "This", 4 ) == 0,
        "Invalid identifier : %.*s != This",
        tk.end-tk.begin,
        tk.begin
    );

    token_next(&ptr, &tk);
    test_token_type( tk, TOKEN_SEPARATOR );

    token_next(&ptr, &tk);
    test_token_type( tk, TOKEN_BOOLEAN );
    test_assert( tk.data.boolean == 1, "Invalid boolean, excepted 1, got 0" );

    token_next(&ptr, &tk);
    test_token_type( tk, TOKEN_SEPARATOR );

    token_next(&ptr, &tk);
    test_token_type( tk, TOKEN_BOOLEAN );
    test_assert( tk.data.boolean == 0, "Invalid boolean, excepted 1, got 0" );

    token_next(&ptr, &tk);
    test_token_type( tk, TOKEN_SEPARATOR );

    token_next(&ptr, &tk);
    test_token_type( tk, TOKEN_IDENTIFIER );
    test_assert(
        strncmp( tk.begin, "yess", 4 ) == 0,
        "Invalid identifier : %.*s != yes",
        tk.end-tk.begin,
        tk.begin
    );

    token_next(&ptr, &tk);
    test_token_type( tk, TOKEN_SEPARATOR );

    token_next(&ptr, &tk);
    test_token_type( tk, TOKEN_IDENTIFIER );
    test_assert(
        strncmp( tk.begin, "nooo", 4 ) == 0,
        "Invalid identifier : %.*s != noo",
        tk.end-tk.begin,
        tk.begin
    );

    token_next(&ptr, &tk);
    test_token_type( tk, TOKEN_SEPARATOR );

    token_next(&ptr, &tk);
    test_token_type( tk, TOKEN_STRING );
    test_assert(
        strncmp( tk.begin, "Hello \\\" World !", strlen("Hello \\\" World !")) == 0,
        "Invalid string : %.*s != \"Hello \\\" World !\"",
        tk.end-tk.begin,
        tk.begin
    );

    token_next(&ptr, &tk);
    test_token_type( tk, TOKEN_SEPARATOR );

    token_next(&ptr, &tk);
    test_token_type( tk, TOKEN_INT );
    test_assert(
        tk.data.intg == 10,
        "Invalid int : %d != 10", tk.data.intg
    );

    token_next(&ptr, &tk);
    test_token_type( tk, TOKEN_SEPARATOR );

    token_next(&ptr, &tk);
    test_token_type( tk, TOKEN_INT );
    test_assert(
        tk.data.intg == -10,
        "Invalid int : %d != -10", tk.data.intg
    );

    token_next(&ptr, &tk);
    test_token_type( tk, TOKEN_SEPARATOR );

    token_next(&ptr, &tk);
    test_token_type( tk, TOKEN_FLOAT );
    test_assert(
        tk.data.num == -10.2f,
        "Invalid float : %f != -10.2", tk.data.num
    );

    token_next(&ptr, &tk);
    test_token_type( tk, TOKEN_SEPARATOR );

    token_next(&ptr, &tk);
    test_token_type( tk, TOKEN_FLOAT );
    test_assert(
        tk.data.num == 10.2f,
        "Invalid float : %f != 10.2", tk.data.num
    );

    token_next(&ptr, &tk);
    test_token_type( tk, TOKEN_EOF );
}

void test_parse_args()
{
    char *ident_begin, *ident_end;
    char *str_begin  , *str_end;

    int intg;
    float num;

    uint8_t boolean;

    //////////////////////////////////////////
    
    const char *ptr = test_str_2;
    char resp_buf[2048];
    prpc_parse_args( resp_buf, 2048, &ptr, 0, 4,
        PRPC_IDENTIFIER,
        &ident_begin, &ident_end,
        PRPC_STRING,
        &str_begin, &str_end,
        PRPC_INT,
        &intg,
        PRPC_FLOAT,
        &num,
        PRPC_BOOLEAN,
        &boolean
    );

    test_assert(
        strncmp(ident_begin, "identifier", ident_end-ident_begin) == 0,
        "Failed parsing identifier : %.*s != %s",
        ident_end-ident_begin, ident_begin,
        "identifier"
    );


    test_assert(
        strncmp( str_begin, "string", str_end-str_begin ) == 0,
        "Failed parsing string : %.*s != %s",
        str_end-str_begin,
        "string"
    );

    test_assert( intg ==   1, "Failed parsing int : %d != %d"  , intg, 1 );
    test_assert(  num == 1.0, "Failed parsing float : %f != %f", num , 1.0 );
    test_assert( boolean == 0, "Failed parsing boolean : %d != %d", boolean, 0 );
}

int test_run()
{
    test_lexer();
    test_parse_args();
    return 0;
}

void test_exit(){}
