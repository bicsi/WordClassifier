#ifndef DEBUG_H_
#define DEBUG_H_

#define DEBUG 1
#define debug(...) \
            do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

#endif // DEBUG_H_