/**************
 * PRPC Types *
 **************/
// Florian Dupeyron
// July 2019

#pragma once

#include <stdint.h>

typedef int PRPC_ID_t;
typedef void (*PRPC_Parse_Function_t)(const char **ptr, char *resp_buff, const size_t max_resp_len, const PRPC_ID_t id );

#define PRPC_ID_NOTIFY -1

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
    const char *begin;
    const char   *end;

    union {
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

typedef enum {
    PRPC_STRING     = TOKEN_STRING,
    PRPC_INT        = TOKEN_INT,
    PRPC_FLOAT      = TOKEN_FLOAT,
    PRPC_BOOLEAN    = TOKEN_BOOLEAN,
    PRPC_IDENTIFIER = TOKEN_IDENTIFIER
} PRPC_Type_t;

#define PRPC_CMD( name ) void prpc_cmd_ ## name( const char **ptr, char *resp_buf, const size_t max_resp_len, PRPC_ID_t id )
