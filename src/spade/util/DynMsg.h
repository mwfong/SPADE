#ifndef __DYNMSG_H__
#define __DYNMSG_H__

#include <string.h>		// strlen ()
#include "dynamic_message.h"

// Dynamic message global variable macros

#define GMsg_declare()		static DynamicMessagePtr _pGDynMsg = (DynamicMessagePtr) NULL
#define GMsg_init()		_pGDynMsg = DynMsgNew (_pGDynMsg)
#define GMsg_strcat(_pStr)	DynMsg_strncat 	(_pGDynMsg, _pStr, strlen (_pStr))
#define GMsg_strncat(_pStr, _n)	DynMsg_strncat 	(_pGDynMsg, _pStr, _n)
#define GMsg_addchar(_aChar)	DynMsg_addchar 	(_pGDynMsg, _aChar)
#define GMsg_addint(_anInt)	DynMsg_addint  	(_pGDynMsg, _anInt)
#define GMsg_addlong(_aLong)	DynMsg_addlong 	(_pGDynMsg, _aLong)
#define GMsg_sprintf(...)	DynMsg_sprintf  (_pGDynMsg, __VA_ARGS__)
#define GMsg_length()		DynMsg_length  	(_pGDynMsg)
#define GMsg_get()		DynMsgGet       (_pGDynMsg)	// performs init ()
#define GMsg_lastchar()		DynMsg_lastChar (_pGDynMsg)
#define GMsg_free()		DynMsgFree      (_pGDynMsg)

// Dynamic message local variable macros

#define LMsg_var		_pLDynMsg
#define LMsg_arg		DynamicMessagePtr LMsg_var
#define LMsg_declare()		LMsg_arg = DynMsgNew ((DynamicMessagePtr) NULL)
#define LMsg_init()		DynMsgInit     	(LMsg_var)
#define LMsg_strcat(_pStr)	DynMsg_strncat 	(LMsg_var, _pStr, strlen (_pStr))
#define LMsg_strncat(_pStr, _n)	DynMsg_strncat 	(LMsg_var, _pStr, _n)
#define LMsg_addchar(_aChar)	DynMsg_addchar 	(LMsg_var, _aChar)
#define LMsg_addint(_anInt)	DynMsg_addint  	(LMsg_var, _anInt)
#define LMsg_addlong(_aLong)	DynMsg_addlong 	(LMsg_var, _aLong)
#define LMsg_sprintf(...)	DynMsg_sprintf  (LMsg_var, __VA_ARGS__)
#define LMsg_length()		DynMsg_length  	(LMsg_var)
#define LMsg_get()		DynMsgGet      	(LMsg_var)	// performs init ()
#define LMsg_lastchar()		DynMsg_lastChar (LMsg_var)
#define LMsg_free()		DynMsgFree      (LMsg_var)

#endif  /* __DYNMSG_H__ */

//Local Variables:
//tab-width: 8
//End:
