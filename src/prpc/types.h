/**********************************
 * Types definition for Petit RPC *
 **********************************/
// Florian Dupeyron
// July 2019

#pragma once

typedef enum {
    PRPC_STRING,
    PRPC_INT,
    PRPC_FLOAT,
    PRPC_BOOLEAN,
} PRPC_Arg_Type_t;

typedef struct {
    PRPC_Arg_Type_t type;
    char *v_begin;
    char *v_end;
} PRPC_Arg_t;

void    prpc_arg_free        ( PRPC_Arg_t *arg );

int     prpc_arg_create_str  ( PRPC_Arg_t *arg, const char  *v, const size_t len );
int     prpc_arg_create_int  ( PRPC_Arg_t *arg, const int    v );
int     prpc_arg_create_float( PRPC_Arg_t *arg, const float  v );
int     prpc_arg_create_bool ( PRPC_Arg_t *arg, const int8_t v );

char   *prpc_arg_get_str     ( PRPC_Arg_t *arg );
int     prpc_arg_get_int     ( PRPC_Arg_t *arg );
float   prpc_arg_get_float   ( PRPC_Arg_t *arg );
int8_t  prpc_arg_get_bool    ( PRPC_Arg_t *arg );

