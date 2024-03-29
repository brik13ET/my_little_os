#ifndef ASSERT_H
#define ASSERT_H

#include <boot.h>

#ifdef DEBUG_SERIAL
#include <serial.h>

#define assert(x)  \
(void)(x == 0 ? \
( \
    serial_write(__FILE__); \
    serial_write(":\0"); \
    serial_write(__FUNCTION__); \
    serial_write("\n\0");\
    error_handler(); \
) : \
    (void)(0); \
)
#define debug(x) \
serial_write(#x); \
serial_write(":\0"); \
serial_write_len(&x, sizeof(x))
#else
#define assert(x)  \
(void)(x == 0 ? \
( error_handler(); ) : \
    (void)(0); \
)
#endif

#define assert_reached() error_handler()

#endif