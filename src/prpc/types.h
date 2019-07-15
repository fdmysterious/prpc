/**************
 * PRPC Types *
 **************/
// Florian Dupeyron
// July 2019

#pragma once

#include "lex.h"

typedef void (*PRPC_Parse_Function_t)(const size_t id, const char **ptr, char *resp_buff, const size_t max_resp_len);

typedef enum {
    PRPC_STRING     = TOKEN_STRING,
    PRPC_INT        = TOKEN_INT,
    PRPC_FLOAT      = TOKEN_FLOAT,
    PRPC_BOOLEAN    = TOKEN_BOOLEAN,
    PRPC_IDENTIFIER = TOKEN_IDENTIFIER
} PRPC_Type_t;
