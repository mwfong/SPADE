#ifndef __DYNAMIC_MESSAGE_PRIV_H__
#define __DYNAMIC_MESSAGE_PRIV_H__

#include <stdlib.h>			// size_t


typedef struct {

  char   *pMessage;
  size_t  lMessage;
  size_t  lMsgMax;

} _DynamicMessage, *_DynamicMessagePtr;

#endif  /* __DYNAMIC_MESSAGE_PRIV_H__ */

//Local Variables:
//tab-width: 8
//End:
