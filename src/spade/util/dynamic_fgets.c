#include <errno.h>
#include <stdio.h>		// 
#include "ClearAlloc.h"		// ClearAlloc ()

#include "dynamic_fgets.h"
#include "dynamic_message_priv.h"


typedef struct {

  FILE		    *pFile;
  int		     status;

  _DynamicMessagePtr pDynMsg;
  size_t	     iStart;
  int		     fIsEOF;
  size_t	     maxStrlen;
  char		     cachedChar;

} _DynamicFgets, *_DynamicFgetsPtr;


  DynamicFgetsPtr
DynFgetsNew (FILE *pFile)
{
  _DynamicFgetsPtr pDynFgets = (_DynamicFgetsPtr) ClearAlloc (sizeof (_DynamicFgets));

  if (pDynFgets /* != (_DynamicFgetsPtr) NULL */) {
    pDynFgets->pFile   = pFile;
    pDynFgets->pDynMsg = (_DynamicMessagePtr) DynMsgNew ((DynamicMessagePtr) NULL);
    if (pDynFgets->pDynMsg == (_DynamicMessagePtr) NULL)
      pDynFgets = (_DynamicFgetsPtr) DynFgetsFree ((DynamicFgetsPtr) pDynFgets);
  }

  return (DynamicFgetsPtr) pDynFgets;
}


  DynamicFgetsPtr
DynFgetsFree (DynamicFgetsPtr _pDynFgets)
{
  _DynamicFgetsPtr pDynFgets = (_DynamicFgetsPtr) _pDynFgets;

  if (pDynFgets /* != (_DynamicFgetsPtr) NULL */) {
    pDynFgets->pDynMsg = (_DynamicMessagePtr) DynMsgFree ((DynamicMessagePtr) pDynFgets->pDynMsg);
    free (pDynFgets);
    _pDynFgets = (DynamicFgetsPtr) NULL;
  }

  return _pDynFgets;
}


  char *
DynFgets_get (DynamicFgetsPtr _pDynFgets)
{
  _DynamicFgetsPtr pDynFgets = (_DynamicFgetsPtr) _pDynFgets;

  if (pDynFgets /* != (_DynamicFgetsPtr) NULL */) {
    _DynamicMessagePtr pDynMsg = (_DynamicMessagePtr) pDynFgets->pDynMsg;
    size_t	       iStart  = pDynFgets->iStart;

    if (pDynFgets->fIsEOF)
      return (char *) NULL;

    // Provisionally restore the starting character

    if (pDynFgets->cachedChar /* != '\0' */) {
      *(pDynMsg->pMessage + pDynFgets->iStart) = pDynFgets->cachedChar;
      pDynFgets->cachedChar = '\0';
    }

    // Check for a newline-terminated string

    while (1) {
      size_t nFree;
      size_t nRead;
      size_t nGrow = 0;
      size_t i;

      for (i = iStart; i < pDynMsg->lMessage; i++) {
	char *p = pDynMsg->pMessage + i;

	// Found newline

	if     (*p == '\n') {
	  size_t lenStr;

	  // Terminate string with a NULL

	  pDynFgets->cachedChar = *(p + 1);	// save the (overwritten) character
	  *(p + 1) = '\0';

	  p = pDynMsg->pMessage + pDynFgets->iStart;

	  lenStr = i - pDynFgets->iStart + 1;
	  if (lenStr > pDynFgets->maxStrlen)
	    pDynFgets->maxStrlen = lenStr;

	  pDynFgets->iStart = i + 1;		// update start of next string

	  return p;
	}

	// Check for non-ASCII characters

	else if ((*p & 0xFF) > 0x7F) {
	  pDynFgets->status = EBADMSG;
	  return (char *) NULL;
	}
      }

      // Shift the string fragment to the beginning of the buffer

      if (pDynFgets->iStart /* != 0 */) {
	size_t nChars = pDynMsg->lMessage - pDynFgets->iStart;

	if (nChars /* > 0 */) {
	  (void) memcpy (pDynMsg->pMessage, pDynMsg->pMessage + pDynFgets->iStart, nChars);

	  pDynMsg->lMessage = nChars;
	  pDynFgets->iStart = 0;
	  iStart	    = 0;
	}
      }

      // Check for EOF

      pDynFgets->fIsEOF = feof (pDynFgets->pFile);
      if (pDynFgets->fIsEOF /* != 0 */) {
	if (pDynFgets->iStart == 0)
	  return DynMsgGet ((DynamicMessagePtr) pDynMsg);
	else
	  return (char *) NULL;
      }

      // Provisionally grow the input buffer

      nFree = pDynMsg->lMsgMax - pDynMsg->lMessage - 1L;

      if      (pDynFgets->maxStrlen /* > 0 */ && nFree < pDynFgets->maxStrlen >> 1)
	nGrow = pDynFgets->maxStrlen >> 1;
      else if (nFree < pDynMsg->lMsgMax >> 1)
	nGrow = pDynMsg->lMsgMax >> 1;

      if (nGrow > 0)
	(void) DynMsgCapacity ((DynamicMessagePtr) pDynMsg, nGrow);

      // Read characters

      nFree = pDynMsg->lMsgMax - pDynMsg->lMessage - 1L;
      nRead = fread (pDynMsg->pMessage + pDynMsg->lMessage, 1, nFree, pDynFgets->pFile);

      pDynFgets->status = ferror (pDynFgets->pFile);
      if (pDynFgets->status /* != 0 */)
	break;

      if (nRead /* > 0 */)
	pDynMsg->lMessage += nRead;
      else
	break;
    }
  }

  return (char *) NULL;
}


  int
DynFgets_status (DynamicFgetsPtr _pDynFgets)
{
  _DynamicFgetsPtr pDynFgets = (_DynamicFgetsPtr) _pDynFgets;

  if (pDynFgets /* != (_DynamicFgetsPtr) NULL */)
    return pDynFgets->status;
  else
    return EPERM;
}


//Local Variables:
//tab-width: 8
//End:
