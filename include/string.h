/*Header defining the string functions
 * */

#ifndef _STRING_H
#define _STRING_H

#include "stdtypes.h"
//returns the length of the string
size_t str_len(const char *str);

//Compare two string
short int str_cmp(const char *str1,const char *str2);

//copy one string to another
void str_cpy(const char *str1,char*str2);

#endif /*string.h*/
