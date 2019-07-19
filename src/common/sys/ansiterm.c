#include "ansiterm.h"
#include <unistd.h>

bool ansiterm_color_support( FILE * f )
{
    return isatty( fileno( f ) );
}
