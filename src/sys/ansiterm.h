/************************************
 * Basic ANSI escape codes handling *
 ************************************/
// Florian Dupeyron
// Around april 2018, revision july 2018

#pragma once

//////////////////////////////////////////
#include <stdbool.h>
#include <stdio.h>
//////////////////////////////////////////

//////////////////////////////////////////
// COLOR DEFINES
//////////////////////////////////////////
// Usage tip // Using these define and the ## operator
// to pre-compute color definitions strings


#define ANSITERM_ESCAPE_BASE        "\x1b["
#define ANSITERM_ESCAPE_SEP         ";"
#define ANSITERM_GFX_END            "m"

#define ANSITERM_STR( mode, fg ) \
    ANSITERM_ESCAPE_BASE mode ANSITERM_ESCAPE_SEP fg ANSITERM_GFX_END

#define ANSITERM_GFX_RESET ANSITERM_ESCAPE_BASE ANSITERM_GFX_MODE_NORMAL ANSITERM_GFX_END

// -- GFX commands
#define ANSITERM_GFX_MODE_NORMAL    "0"
#define ANSITERM_GFX_MODE_BOLD      "1"
#define ANSITERM_GFX_MODE_UNDERLINE "4"
#define ANSITERM_GFX_MODE_REVERSE   "7"

// -- colors
#define ANSITERM_FG_BLACK           "30"
#define ANSITERM_FG_RED             "31"
#define ANSITERM_FG_GREEN           "32"
#define ANSITERM_FG_YELLOW          "33"
#define ANSITERM_FG_BLUE            "34"
#define ANSITERM_FG_MAGENTA         "35"
#define ANSITERM_FG_CYAN            "36"
#define ANSITERM_FG_WHITE           "37"

#define ANSITERM_BG_BLACK           "40"
#define ANSITERM_BG_RED             "41"
#define ANSITERM_BG_GREEN           "42"
#define ANSITERM_BG_YELLOW          "43"
#define ANSITERM_BG_BLUE            "44"
#define ANSITERM_BG_MAGENTA         "45"
#define ANSITERM_BG_CYAN            "46"
#define ANSITERM_BG_WHITE           "47"

//////////////////////////////////////////
// Utils
//////////////////////////////////////////
bool ansiterm_color_support( FILE * f ); // Checks for color support for stderr output
