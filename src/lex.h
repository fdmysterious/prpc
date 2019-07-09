/*************************
 * Dumb easy lexer thing *
 *************************/
// Florian Dupeyron
// July 2019

#pragma once

#include <stdlib.h>
#include <stdint.h>

typedef enum {
    TOKEN_ERROR = 0,
    TOKEN_EOL,
    TOKEN_EOF,
    TOKEN_SEPARATOR,

    TOKEN_STRING,
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_BOOLEAN,
    TOKEN_IDENTIFIER,
    TOKEN_COMMAND
} Token_Type_t;

typedef struct {
    Token_Type_t type;
    char *begin;
    char   *end;

    union {
        struct {
            const char *begin;
            const char *end;
        } str;

        int  intg;
        float num;
        uint8_t boolean;

        struct {
            int id;
            const char *name_begin;
            const char *name_end;
        } cmd;
    } data;
} Token_t;

//////////////////////////////////////////

const char *token_type_str( Token_Type_t type );
char *token_next( char *sstr, Token_t *dst );
