#if !defined (ClearAlloc)

#include <stddef.h>			// size_t
#include <stdlib.h>			// calloc ()
#include <string.h>			// memset ()

#define ClearAlloc(_size_t)	calloc ((size_t) 1L, (size_t) (_size_t /* + 1024 */))

/**
 * Convenience memory allocation macro
 */
#define CLEARALLOC(_prefix)	(_prefix ## Ptr) ClearAlloc (sizeof (_prefix ## Rec))

/**
 * Convenience zero memory macro
 */
#define ZERO_STRUCT(_p, _s) 		\
  (void) memset (_p, 0, sizeof (_s))

/**
 * Convenience memory deallocation macro
 */
#define FREE_STRUCT(_p, _s) {		\
  ZERO_STRUCT (_p, _s);			\
  free (_p);				\
}

#endif

//Local Variables:
//tab-width: 8
//End:
