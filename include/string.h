/*Header defining the string functions
 * */

#ifndef _STRING_H
#define _STRING_H

#include "stdtypes.h"
// returns the length of the string
size_t str_len(const char *str);

// Compare two string
short int str_cmp(const char *str1, const char *str2);

// copy one string to another
void str_cpy(const char *str1, char *str2);

// mem setter
void memset(void *mem_loc, uint8_t value, uint16_t size);

// mem copy
void memcpy(void *src_loc, void *dest_loc, uint16_t till);
#endif /*string.h*/
