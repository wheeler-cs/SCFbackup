/**
 * @file filesystem.h
 * @author wheeler-cs
 *
 * @brief Provides functionality of program requried to interface with an operating system's file
 * storage system.
 *
 * # TODO: Add more in-depth description of filesystem interface.
 *
*/

#ifndef SCF_FILESYSTEM_H
#define SCF_FILESYSTEM_H

#include "list.h"

#include <time.h>

struct file_record
{
    char *file_name;
    time_t modified_time;
};

#if defined(__linux__) // If on Linux systems

#include "dirent.h"
#include "sys/stat.h"

#elif defined(__WIN32) // If on Windows systems

#include <Windows.h>

#else // Unsupported OS
#error "Unsupported OS!"
#endif

void generate_file_database (char *, struct string_list *);

#endif
