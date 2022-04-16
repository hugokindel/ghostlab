#include <common/string.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <common/array.h>
#include <common/utils.h>
#include "log.h"
#include "memory.h"

uint8_t *gl_string_create_from_cstring(const char *src) {
    uint8_t *dst = 0;
    
    for (uint32_t i = 0; i < strlen(src); i++) {
        gl_array_push(dst, (uint8_t)(src)[i]);
    }
    
    return dst;
}

uint8_t *gl_string_create_from_number(const char *src, uint8_t size) {
    // `src` is not null and not too big.
    if (!src || strlen(src) > size) {
        return 0;
    }
    
    // Every char of `src` is a number.
    for (uint32_t i = 0; i < strlen(src); i++) {
        if (!isdigit(src[i])) {
            return 0;
        }
    }
    
    uint8_t *dst = 0;
    
    for (uint32_t i = 0; i < size - strlen(src); i++) {
        gl_array_push(dst, '0');
    }
    
    for (uint32_t i = 0; i < strlen(src); i++) {
        gl_array_push(dst, (uint8_t)(src)[i]);
    }
    
    return dst;
}

uint8_t *gl_string_create_from_ip(const char *src) {
    // `src` is not null and not too big.
    if (!src || strlen(src) > 15) {
        return 0;
    }
    
    // The format of `src` is a valid IP address.
    int32_t distance_from_last_point = 0;
    int32_t total_num_points = 0;
    for (uint32_t i = 0; i < strlen(src); i++) {
        if (isdigit(src[i]) && distance_from_last_point < 3) {
            distance_from_last_point++;
            continue;
        } else if (src[i] == '.' && distance_from_last_point > 0 && total_num_points < 3) {
            distance_from_last_point = 0;
            total_num_points++;
            continue;
        } else {
            return 0;
        }
    }
    
    uint8_t *dst = 0;
    
    for (uint32_t i = 0; i < strlen(src); i++) {
        gl_array_push(dst, (uint8_t)(src)[i]);
    }
    
    for (uint32_t i = 0; i < 15 - strlen(src); i++) {
        gl_array_push(dst, '#');
    }
    
    return dst;
}

char *gl_cstring_create_from_string(const uint8_t *src) {
    if (!src) {
        return 0;
    }
    
    char *str = gl_malloc(gl_array_get_size(src));
    
    for (uint32_t i = 0; i < gl_array_get_size(src); i++) {
        str[i] = (char)src[i];
    }
    
    return str;
}

char *gl_cstring_create_from_ip(const uint8_t *src) {
    if (!src) {
        return 0;
    }
    
    uint32_t end_idx;
    for (end_idx = 0; end_idx < gl_array_get_size(src); end_idx++) {
        if (src[end_idx] == '#') {
            break;
        }
    }
    
    char *str = gl_malloc(end_idx + 1);
    str[end_idx] = 0;
    
    for (uint32_t i = 0; i < end_idx; i++) {
        str[i] = (char)src[i];
    }
    
    return str;
}

int32_t gl_write_string(uint8_t **buf, const uint8_t **n) {
    for (uint32_t i = 0; i < gl_array_get_size(*n); i++) {
        gl_uint8_write(buf, &(*n)[i]);
    }
    
    return gl_array_get_size(*n);
}

int32_t gl_write_cstring(uint8_t **buf, const char **n) {
    for (uint32_t i = 0; i < strlen(*n); i++) {
        gl_uint8_write(buf, (const uint8_t *)&(*n)[i]);
    }
    
    return (int)strlen(*n);
}

void gl_string_printf(uint8_t **str) {
    for (uint32_t i = 0; i < gl_array_get_size(*str); i++) {
        gl_log_push("%c", (*str)[i]);
    }
}