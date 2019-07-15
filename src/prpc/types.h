/**************
 * PRPC Types *
 **************/
// Florian Dupeyron
// July 2019

#pragma once

#include "lex.h"

typedef int PRPC_ID_t;
typedef void (*PRPC_Parse_Function_t)(const char **ptr, char *resp_buff, const size_t max_resp_len, const PRPC_ID_t id );

#define PRPC_ID_NOTIFY -1

typedef enum {
    PRPC_STRING     = TOKEN_STRING,
    PRPC_INT        = TOKEN_INT,
    PRPC_FLOAT      = TOKEN_FLOAT,
    PRPC_BOOLEAN    = TOKEN_BOOLEAN,
    PRPC_IDENTIFIER = TOKEN_IDENTIFIER
} PRPC_Type_t;

#define PRPC_CMD( name ) void prpc_cmd_ ## name( const char **ptr, char *resp_buf, const size_t max_resp_len, PRPC_ID_t id )
