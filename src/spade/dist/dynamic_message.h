#ifndef __DYNAMIC_MESSAGE_H__
#define __DYNAMIC_MESSAGE_H__

#include <stdlib.h>			// size_t


typedef struct DynamicMessage *DynamicMessagePtr;

extern DynamicMessagePtr DynMsgNew	 (DynamicMessagePtr pDynMsg);
extern DynamicMessagePtr DynMsgInit	 (DynamicMessagePtr pDynMsg);
extern DynamicMessagePtr DynMsgFree	 (DynamicMessagePtr pDynMsg);
extern DynamicMessagePtr DynMsgCapacity	 (DynamicMessagePtr pDynMsg,
					  size_t numAdd);
extern size_t		 DynMsgSize	 (DynamicMessagePtr _pDynMsg);
extern DynamicMessagePtr DynMsg_addchar	 (DynamicMessagePtr pDynMsg,
					  char aChar);
extern DynamicMessagePtr DynMsg_addint	 (DynamicMessagePtr _pDynMsg,
					  int anInt);
extern char *		 DynMsg_strncat	 (DynamicMessagePtr pDynMsg,
					  const char *aString, size_t lenStr);
extern char *		 DynMsgGet	 (DynamicMessagePtr pDynMsg);
extern char		 DynMsg_lastChar (DynamicMessagePtr pDynMsg);

#endif  /* __DYNAMIC_MESSAGE_H__ */

//Local Variables:
//tab-width: 8
//End:
