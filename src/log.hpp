#ifndef DEMAROK_LOG_H
#define DEMAROK_LOG_H

#include <cstdio>


#define demarok_log_err(format, ...)    \
    (void)fprintf(stderr, "[ERROR] %s: " format, __FUNCTION__, __VA_ARGS__)

#define demarok_log_info(format, ...)    \
    (void)fprintf(stderr, "[INFO] %s: " format, __FUNCTION__, __VA_ARGS__)


#endif // DEMAROK_LOG_H
