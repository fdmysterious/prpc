/*************************************
 * Completely thread-unsafe logging  *
 *************************************/
// Florian Dupeyron (floolfy)
// Created april 2018 ?
// Revision july 2018

#pragma once

#define LOG_ENABLE_STDERR
//#define LOG_ENABLE_SYSLOG

#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>

//////////////////////////////////////////
// Enum
//////////////////////////////////////////
enum LogLevel {
    LOG_LVL_DEBUG,
    LOG_LVL_VERBOSE,
    LOG_LVL_NOTICE,
    LOG_LVL_WARNING,
    LOG_LVL_ERROR,
    LOG_LVL_CRITIC
};

////////////////////////////////////////// 
// Prototypes
////////////////////////////////////////// 
void log_open ();
void log_close();

void log_plog( enum LogLevel lvl, const char * file, const size_t line, const char * msg, ... );
//////////////////////////////////////////
// Preprocessor madness
//////////////////////////////////////////
// NOTE // __FILENAME__ macro should be defined by compiler for each source file
// with file basename
#define log_debug( ... )   log_plog( LOG_LVL_DEBUG  , __FILENAME__, __LINE__, __VA_ARGS__ )
#define log_verbose( ... ) log_plog( LOG_LVL_VERBOSE, __FILENAME__, __LINE__, __VA_ARGS__ )
#define log_notice( ... )  log_plog( LOG_LVL_NOTICE , __FILENAME__, __LINE__, __VA_ARGS__ )
#define log_warning( ... ) log_plog( LOG_LVL_WARNING, __FILENAME__, __LINE__, __VA_ARGS__ )
#define log_error( ... )   log_plog( LOG_LVL_ERROR  , __FILENAME__, __LINE__, __VA_ARGS__ )
#define log_critic( ... )  log_plog( LOG_LVL_CRITIC , __FILENAME__, __LINE__, __VA_ARGS__ )
