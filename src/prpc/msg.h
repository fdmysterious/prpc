/***************************
 * Build messages for PRPC *
 ***************************/
// Florian Dupeyron
// July 2019

#include <stdlib.h>
#include <stdint.h>

#include "lex.h"

#pragma once

void prpc_build_ok            ( const size_t id, char *buf, const size_t max_len );
void prpc_build_error         ( const size_t id, char *buf, const size_t max_len, const char *msg    );

void prpc_build_msg           ( const size_t id, char *buf, const size_t max_len, const char *cmd, const size_t nvals, ... );

void prpc_build_result        ( const size_t id, char *buf, const size_t max_len, const size_t nvals,  ... );
void prpc_build_result_boolean( const size_t id, char *buf, const size_t max_len, const uint8_t val  );
void prpc_build_result_int    ( const size_t id, char *buf, const size_t max_len, const int     intg );
