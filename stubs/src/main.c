/**
 * @file main.c
 * @author Gerald Weatherup (gerald.weatherup@sky.uk)
 * @brief Main control application for wifi unit testing
 * @version 0.1
 * @date 2022-05-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/* Stdlib includes */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

#define TEST_INFO(x) printf x;
#define TRUE  (true)
#define FALSE (false)
#define MAX_STRING_SIZE (32)
#define DEFAULT_FILENAME "wifi_hal"


static void usage( void )
{
    TEST_INFO(( "-h - Help\n" ));
}

static bool decodeOptions( int argc, char **argv )
{
    int opt;


    memset(&gOptions,0,sizeof(gOptions));

    gOptions.testMode = TEST_MODE_CONSOLE;
    strcpy( gOptions.filenameRoot, DEFAULT_FILENAME );
    while((opt = getopt(argc, argv, "cabhf:l")) != -1)
    {
        switch(opt)
        {
            case 'c':
            case 'h':
                TEST_INFO(("Help\n"));
                usage();
                exit(0);
                break;
            case '?':
            case ':':
                TEST_INFO(("unknown option: %c\n", optopt));
                break;
        }
    }

    // optind is for the extra arguments 
    // which are not parsed 
    for(; optind < argc; optind++)
    {
        TEST_INFO(("unknown arguments: %s\n", argv[optind]));
    }

    return TRUE;
}

int main(int argc, char** argv) 
{
    /* Decode the options */
    if ( decodeOptions( argc, argv ) == FALSE )
    {
        return -1;
    }

    return 0;
}

