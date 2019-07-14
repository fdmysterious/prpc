/*****************************
 * Test command parser thing *
 *****************************/
// Florian Dupeyron
// July 2019

#pragma once

#include <stdlib.h>

typedef void (*PRPC_Parse_Function_t)(const size_t id, const char **ptr, char *resp_buff, const size_t max_resp_len);
void prpc_process_line( const char *line, char *resp_buf, const size_t max_resp_len );
