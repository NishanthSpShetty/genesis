
#include "../include/string.h"

/*Implementaion of string functions
 * */
size_t str_len(const char *str)
{
    size_t len = 0;
    while (str[len]) {
        len++;
    }
    return len;
}

short int str_cmp(const char *str1, const char *str2)
{
    size_t i = -1;
    // loop until both string contains same character
    do {
        i++;
    } while (str1[i] == str2[i] && str1[i] && str2[i]);
    return str1[i] - str2[i];
}

void str_cpy(const char *str1, char *str2)
{
    size_t i = 0;
    while (str1[i]) {
        str2[i] = str1[i];
        i++;
    }
    str2[i] = 0;
}

// mem setter
void memset(void *mem_loc, uint8_t value, uint16_t size)
{
    int end = 0;
    uint8_t *_mem_loc = (uint8_t *)mem_loc;

    while (end < size) {
        *(_mem_loc + end++) = value;
    }
}

// mem copy
void memcpy(void *src_loc, void *dest_loc, uint16_t till)
{
    uint16_t end = 0;
    uint8_t *_dest_loc = (uint8_t *)dest_loc;
    uint8_t *_src_loc = (uint8_t *)src_loc;

    while (end < till) {
        *(_dest_loc + end) = *(_src_loc + end);
        end++;
    }
}

