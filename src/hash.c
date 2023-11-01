#include "hash.h"

#include <stdio.h>

/**
 * @brief Reads in the data of a file in order to calculate its corresponding CRC32 value.
 * 
 * @param file_name Name of file to be hashed.
 * 
 * @returns The calculated CRC32 hash of the provided file or 0x00000000 in the event of failure.
 * 
 * @retval 0x00000000 Unable to open file provided, for one reason or another.
 */
uint32_t calculate_file_crc32 (char *file_name)
{
    // Try to open given file for reading
    FILE *file_ptr;
	if ((file_ptr = fopen (file_name, "rb")) == NULL)
		return 0x00000000; // Error occurred, return hash of 0

	// Vars used for CRC calculation
	uint32_t crc = 0xffffffff;
	uint8_t byte_buffer = 0x00;
	unsigned int ref_idx = 0;

	// Do calculation
	while (fread (&byte_buffer, sizeof (uint8_t), 1, file_ptr))
	{
		ref_idx = (crc ^ byte_buffer) & 0xff;
		crc = (crc >> 8) ^ CRC_LOOKUP_TABLE[ref_idx];
	}

    fclose (file_ptr);
	// Flip bits and return CRC
	return (crc ^= 0xffffffff);	
}