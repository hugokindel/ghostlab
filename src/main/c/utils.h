#ifndef GHOSTLAB_UTILS_H
#define GHOSTLAB_UTILS_H

#include "types.h"

struct gl_message_t;

// Checks `errno` to call `perror` if needed and returns `EXIT_FAILURE`.
int gl_get_error();

int gl_write_uint8(gl_buffer_t *buf, const uint8_t *n);

int gl_write_uint16(gl_buffer_t *buf, const uint16_t *n);

int gl_read_uint8(int fd, uint8_t *n);

int gl_read_uint16(int fd, uint16_t *n);

int gl_read_string(int fd, uint8_t **dst, uint8_t *last_c, uint16_t max_size, bool precise_size);

int gl_read_message(int fd, struct gl_message_t *dst);

#endif /* GHOSTLAB_UTILS_H */
