/************************
 * Message builder test *
 ************************/
// Florian Dupeyron
// July 2019

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <prpc/msg.h>

#include <test.h>

int test_run()
{
    const char *msg_ref = "0:hello_world identifier \"string\" yes no 1 -1 1.000000 -1.000000\n";
    char buf[2048];

    prpc_build_msg( buf, 2048,
        0, "hello_world", 8,
        TOKEN_IDENTIFIER, "identifier",
        TOKEN_STRING    , "string",
        TOKEN_BOOLEAN   ,    1,
        TOKEN_BOOLEAN   ,    0,
        TOKEN_INT       ,    1,
        TOKEN_INT       ,   -1,
        TOKEN_FLOAT     ,  1.0,
        TOKEN_FLOAT     , -1.0
    );

    test_assert( strncmp( msg_ref, buf, strlen(msg_ref)) == 0, "Invalid generated string : %s", buf );

    return 0;
}

void test_exit(){}
