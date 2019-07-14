#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "msg.h"

void prpc_build_ok( const size_t id, char *buf, const size_t max_len )
{
    snprintf( buf, max_len, "%lu:ok\n", id );
}

void prpc_build_error( const size_t id, char *buf, const size_t max_len, const char *err )
{
    snprintf( buf, max_len, "%lu:error \"%s\"\n", id, err );
}

void prpc_build_result_boolean( const size_t id, char *buf, const size_t max_len, const uint8_t val )
{
    static const char *bool_vals[] = { "no", "yes" };
    snprintf( buf, max_len, "%lu:result %s\n", id, bool_vals[val == 1]); // == 1 to securise array access (what if val == 2 ?)
}

void prpc_build_result_int( const size_t id, char *buf, const size_t max_len, const int intg )
{
    snprintf( buf, max_len, "%lu:result %d", id, intg );
}
