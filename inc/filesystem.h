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

#include <time.h>

struct file_entry {
    char *file_name;
    struct file_entry *next_file;
};

struct file_index {
    struct file_entry *list_start;
    unsigned int index_size;
};

// === Platform-Specific Code =========================================================================================
#if defined(__linux__) // If on Linux systems

#include "dirent.h"
#include "sys/stat.h"

#elif defined(__WIN32) // If on Windows systems

#include <Windows.h>

#else // Unsupported OS
#error "Unsupported OS!"
#endif
// =====================================================================================================================

struct file_index *generate_file_database (char *);

struct file_index *create_file_index();
void append_file_to_index (struct file_index *, char *);
void delete_index (struct file_index *);

#endif
