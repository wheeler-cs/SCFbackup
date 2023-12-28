/**
 * @file filesystem.h
 * @author wheeler-cs
 *
 * @brief Provides functionality of program requried to interface with an operating system's file storage system.
 *
 *
*/

#ifndef SCF_FILESYSTEM_H
#define SCF_FILESYSTEM_H

#include <time.h>

struct file_entry {
    char *file_name;
    struct file_entry *next_file;
};
/**
 * @struct file_entry filesystem.h
 * 
 * Member element of the file_index list. Contains a file path and pointer to the next file stored in the index.
*/

struct file_index {
    struct file_entry *list_start;
    unsigned int index_size;
};
/**
 * @struct file_index filesystem.h
 * 
 * Partially implements a singly-linked list to act as a dynamically-sizable array for file names.
*/

// === Platform-Specific Code =========================================================================================
#if defined(__linux__) // If on Linux systems

#include "dirent.h"
#include "sys/stat.h"

#elif defined(__WIN32) // If on Windows systems

#include <Windows.h>

#error Windows implementation is not yet supported.

#else // Unsupported OS
#error "Unsupported OS!"
#endif
// =====================================================================================================================

struct file_index *generate_file_index (char *);

struct file_index *create_file_index();
void append_file_to_index (struct file_index *, char *);
struct file_entry *index_tail (struct file_index *);
void merge_file_indices (struct file_index *, struct file_index *);
void traverse_print_index (struct file_index *);
void delete_index (struct file_index *);

#endif
