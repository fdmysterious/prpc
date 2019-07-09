#include <stdlib.h>
#include <stdio.h>

#include <test.h>

int test_run()
{
    test_assert( 1 == 1, "Comparaison failed" );
    return EXIT_SUCCESS;
}

void test_exit(){}
