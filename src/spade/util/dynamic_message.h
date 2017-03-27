#ifndef __DYNAMIC_MESSAGE_H__

#include "dist/dynamic_message.h"


extern size_t		 DynMsg_length   (DynamicMessagePtr _pDynMsg);
extern DynamicMessagePtr DynMsg_addint	 (DynamicMessagePtr _pDynMsg,
					  int anInt);
extern DynamicMessagePtr DynMsg_addlong	 (DynamicMessagePtr _pDynMsg,
					  long aLong);
extern DynamicMessagePtr DynMsg_sprintf	 (DynamicMessagePtr _pDynMsg,
					  const char *format, ...);

#endif  /* __DYNAMIC_MESSAGE_H__ */

//Local Variables:
//tab-width: 8
//End:
