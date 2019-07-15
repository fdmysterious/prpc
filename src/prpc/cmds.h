/*****************************
 * Test command parser thing *
 *****************************/
// Florian Dupeyron
// July 2019

#pragma once

#include <stdlib.h>
#include "types.h"

void prpc_process_line( const char *line, char *resp_buf, const size_t max_resp_len );

// User implemented
void prpc_process_cmd(
    char *resp_buf, const size_t max_resp_len,
    const PRPC_ID_t id, const char *cmd_name,
    const char **args_ptr
);

// User implemented
void prpc_process_notification(
    char *resp_buf, const size_t max_resp_len,
    const char *notify_name,
    const char **args_ptr
);
