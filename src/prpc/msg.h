/***************************
 * Build messages for PRPC *
 ***************************/
// Florian Dupeyron
// July 2019

#include <stdlib.h>
#include <stdint.h>

#include "lex.h"

#pragma once

void prpc_build_ok            ( char *buf, const size_t max_len, const size_t id);
void prpc_build_error         ( char *buf, const size_t max_len, const size_t id, const char *msg    );

void prpc_build_msg           ( char *buf, const size_t max_len, const size_t id, const char *cmd, const size_t nvals, ... );

void prpc_build_result        ( char *buf, const size_t max_len, const size_t id, const size_t nvals,  ... );
void prpc_build_result_boolean( char *buf, const size_t max_len, const size_t id, const uint8_t val  );
void prpc_build_result_int    ( char *buf, const size_t max_len, const size_t id, const int     intg );
