#include <stdlib.h>		// NULL, size_t
#include <string.h>		// strlen (), strncpy ()
#include "ClearAlloc.h"		// ClearAlloc ()


#include "dynamic_message.h"


#define _MSG_BUFF_SIZE_ 128


typedef struct {

  char   *pMessage;
  size_t  lMessage;
  size_t  lMsgMax;

} _DynamicMessage, *_DynamicMessagePtr;


  static void
FatalError (const char *format, ...) {
  va_list ap;

  va_start (ap, format);

  (void) fprintf  (stderr, "ERROR: ");
  (void) vfprintf (stderr, format, ap);
  (void) fprintf  (stderr, "Fatal Error, Quitting..\n");

  exit (1);
}


  DynamicMessagePtr
DynMsgNew (DynamicMessagePtr pDynMsg) {
  if (pDynMsg == (DynamicMessagePtr) NULL)
    pDynMsg = (DynamicMessagePtr) ClearAlloc (sizeof (_DynamicMessage));

  return DynMsgInit (pDynMsg);
}


  DynamicMessagePtr
DynMsgInit (DynamicMessagePtr _pDynMsg) {
  _DynamicMessagePtr pDynMsg = (_DynamicMessagePtr) _pDynMsg;

  /*...Conditionally initialize...*/ 
  if (pDynMsg->pMessage == (char *) NULL) {
    pDynMsg->pMessage = (char *) ClearAlloc (_MSG_BUFF_SIZE_);
    pDynMsg->lMsgMax  = _MSG_BUFF_SIZE_;
  }

  pDynMsg->lMessage = (size_t) 0L;

  return _pDynMsg;
}


  DynamicMessagePtr
DynMsgFree (DynamicMessagePtr _pDynMsg) {
  _DynamicMessagePtr pDynMsg = (_DynamicMessagePtr) _pDynMsg;

  if (pDynMsg /* != (_DynamicMessagePtr) NULL */) {
    /*...Conditionally de-allocate...*/ 
    if (pDynMsg->pMessage /* != (char *) NULL */) {
      free (pDynMsg->pMessage);
      pDynMsg->pMessage = (char *) NULL;
      pDynMsg->lMsgMax  = (size_t) 0U;
    }

    pDynMsg->lMessage = (size_t) 0L;

    free (pDynMsg);
  }
  
  return (DynamicMessagePtr) NULL;
}


  DynamicMessagePtr
DynMsgCapacity (DynamicMessagePtr _pDynMsg, size_t numAdd) {
  _DynamicMessagePtr pDynMsg = (_DynamicMessagePtr) _pDynMsg;
  size_t	     numWant = pDynMsg->lMessage + numAdd + 1L;
  char		     fDoGrow = 0;

  if (pDynMsg->lMsgMax == (size_t) 0L)
    DynMsgInit (_pDynMsg);

  /*...Double the capacity until the requisite size is achieved...*/
  while (numWant > pDynMsg->lMsgMax) {
    pDynMsg->lMsgMax <<= 1;
    fDoGrow = 1;
  }

  /*...Conditionally reallocate memory...*/
  if (fDoGrow /* != 0 */) {
    pDynMsg->pMessage = (char *) realloc (pDynMsg->pMessage, pDynMsg->lMsgMax);
    if (pDynMsg->pMessage == NULL) {
      FatalError ("Unable to re-allocate memory!"
		  "  (%lu requested)\n", pDynMsg->lMsgMax);
    }
  }

  return _pDynMsg;
}


  size_t
DynMsgSize (DynamicMessagePtr _pDynMsg) {
  _DynamicMessagePtr pDynMsg = (_DynamicMessagePtr) _pDynMsg;

  return pDynMsg->lMsgMax;
}


  DynamicMessagePtr
DynMsg_addchar (DynamicMessagePtr _pDynMsg, char aChar) {
  _DynamicMessagePtr pDynMsg = (_DynamicMessagePtr) _pDynMsg;

  DynMsgCapacity (_pDynMsg, 1);

  *(pDynMsg->pMessage + pDynMsg->lMessage) = aChar;
  (pDynMsg->lMessage)++;

  return _pDynMsg;
}


  char *
DynMsg_strncat (DynamicMessagePtr _pDynMsg, const char *aString, size_t lenStr) {
  _DynamicMessagePtr pDynMsg = (_DynamicMessagePtr) _pDynMsg;

  if (aString == (const char *) NULL)
    return pDynMsg->pMessage;

  if (lenStr == (size_t) 0)
    lenStr = strlen (aString);

  DynMsgCapacity (_pDynMsg, lenStr);

  (void) strncpy (pDynMsg->pMessage + pDynMsg->lMessage, aString, lenStr);
  pDynMsg->lMessage += lenStr;

  return pDynMsg->pMessage;
}


  char *
DynMsgGet (DynamicMessagePtr _pDynMsg) {
  _DynamicMessagePtr pDynMsg = (_DynamicMessagePtr) _pDynMsg;

  *(pDynMsg->pMessage + pDynMsg->lMessage) = '\0';

  pDynMsg->lMessage = 0UL;

  return pDynMsg->pMessage;
}


  char
DynMsg_lastChar (DynamicMessagePtr _pDynMsg) {
  _DynamicMessagePtr pDynMsg = (_DynamicMessagePtr) _pDynMsg;

  DynMsgCapacity (_pDynMsg, (size_t) 0L);

  if (pDynMsg->lMessage /* > (size_t) 0L */)
    return *(pDynMsg->pMessage + pDynMsg->lMessage - (size_t) 1L);
  else
    return '\0';
}

//Local Variables:
//tab-width: 8
//End:
