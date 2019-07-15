/*****************************
 * Test command parser thing *
 *****************************/
// Florian Dupeyron
// July 2019

#pragma once

#include <stdlib.h>
#include "types.h"

void prpc_process_line( const char *line, char *resp_buf, const size_t max_resp_len );
