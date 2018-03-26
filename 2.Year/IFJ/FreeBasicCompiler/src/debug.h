#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
#define debug_print(fmt, ...) \
do { fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
			__LINE__, __func__, __VA_ARGS__); } while (0)
#define debug_puts(str) \
do { fprintf(stderr, "%s:%d:%s(): %s", __FILE__, \
			__LINE__, __func__, str); } while (0)
#else /* ifdef DEBUG */
#define debug_print(fmt, ...) do { } while (0)
#define debug_puts(str) do { } while (0)
#endif /* DEBUG */

#endif /* DEBUG_H */
