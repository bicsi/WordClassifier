#ifndef DEBUG_H_
#define DEBUG_H_


#define debug(fmt, ...) \
            do { if (DEBUG) fprintf(stderr, fmt, __VA_ARGS__); } while (0)

#endif // DEBUG_H_