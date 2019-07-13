#include <stdlib.h>
#include "types.h"

void prpc_arg_free( PRPC_Arg_t *arg )
{
    free( arg->v );
}

static int prpc_arg_create( PRPC_Arg_t *arg, size_t vsize )
{
    arg->v = malloc(vsize);
    return arg->v == NULL;
}

int prpc_arg_create_str( PRPC_Arg_t* arg, const char *v, const size_t len )
{
    if( prpc_arg_create(arg, sizeof(char) * (len+1)) ) return 1;
    memcpy( arg->v, (void*)v, len );
    arg->v[len] = 0;

    return 0;
}

#define __CREATE_SIMPLE( tt, nn ) \
    int prpc_arg_create_ ## nn (PRPC_Arg_t *arg, const tt v ) \
    {\
        if( prpc_arg_create(arg, sizeof(tt)) ) return 1; \
        memcpy( arg->v, (void*)&v, sizeof(tt) ); \
        return 0;\
    }

#define __GET_SIMPLE(tt, nn) \
    tt prpc_arg_get_ ## nn ( PRPC_Arg_t *arg ) \
    {\
        tt r; \
        tt *v_arg = (tt*)arg->v; \
        if( v_arg ) r = *v_arg; \
        return r; \
    }

__CREATE_SIMPLE(int   , int  )
__CREATE_SIMPLE(float , float)
__CREATE_SIMPLE(int8_t, bool )

char *prpc_arg_get_str( PRPC_Arg_t *arg )
{
    char *v = (char*)arg->v;
    return v;
}

__GET_SIMPLE(int   , int  )
__GET_SIMPLE(float , float)
__GET_SIMPLE(int8_t, bool )
