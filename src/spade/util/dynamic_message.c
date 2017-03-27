#include <stdarg.h>		// va_list, va_start (), va_end ()
#include <stdio.h>		// vsnprintf ()

#include "dist/dynamic_message.c"


  size_t
DynMsg_length (DynamicMessagePtr _pDynMsg) {
  return ((_DynamicMessagePtr) _pDynMsg)->lMessage;
}


  DynamicMessagePtr
DynMsg_addint (DynamicMessagePtr _pDynMsg, int anInt) {
  if (anInt < 0) {
    DynMsg_addchar (_pDynMsg, '-');
    anInt = -anInt;
  }

  if (anInt >= 10)
    (void) DynMsg_addint (_pDynMsg, anInt / 10);

  DynMsg_addchar (_pDynMsg, '0' + (anInt % 10));

  return _pDynMsg;
}


  DynamicMessagePtr
DynMsg_addlong (DynamicMessagePtr _pDynMsg, long aLong) {
  if (aLong < 0L) {
    DynMsg_addchar (_pDynMsg, '-');
    aLong = -aLong;
  }

  if (aLong >= 10L)
    (void) DynMsg_addlong (_pDynMsg, aLong / 10L);

  DynMsg_addchar (_pDynMsg, '0' + (aLong % 10L));

  return _pDynMsg;
}


  DynamicMessagePtr
DynMsg_sprintf (DynamicMessagePtr _pDynMsg, const char *format, ...) {
  _DynamicMessagePtr pDynMsg = (_DynamicMessagePtr) _pDynMsg;

  while (1) {
    va_list args;
    size_t  nFree = pDynMsg->lMsgMax - pDynMsg->lMessage - 1L;
    size_t  nWrote;
        
    va_start (args, format);

    nWrote = vsnprintf (pDynMsg->pMessage + pDynMsg->lMessage, nFree, format, args);

    va_end (args);

    if (nWrote < nFree) {
      pDynMsg->lMessage += nWrote;
      break;
    }
    else
      DynMsgCapacity (_pDynMsg, nWrote);
  }

  return _pDynMsg;
}

//Local Variables:
//tab-width: 8
//End:
