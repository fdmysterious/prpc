/**********************
 * Testing the parser *
 **********************/
// Florian Dupeyron
// July 2019

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include <test.h>
#include <parse.h>

void test_parse_int()
{
    int num[] = {
        0, -100, 100
    };

    const char *num_str[] = { "0", "-100", "100" };

    size_t n_nums = sizeof(num)/sizeof(int);

    size_t i;
    for( i = 0 ; i < n_nums ; i++ ) {
        test_assert( parse_int( num_str[i], num_str[i] + strlen(num_str[i]) ) == num[i], "Invalid parsed int" );
    }
}

void test_parse_float()
{
    float num[] = {
        8283.382f, -8283.382f,
        1.2983f, -1.2983f
    };

    const char *num_str[] = { "8283.382", "-8283.382", "1.2983", "-1.2983" };

    size_t n_nums = sizeof(num)/sizeof(int);

    size_t i;
    for( i = 0 ; i < n_nums ; i++ ) {
        test_assert( parse_float( num_str[i], num_str[i] + strlen(num_str[i]) ) == num[i], "Invalid parsed float" );
    }
}

//////////////////////////////////////////

int test_run()
{
    test_parse_int();
    test_parse_float();
    return EXIT_SUCCESS;
}

void test_exit(){}
