#ifndef __DYNAMIC_FGETS_H__

#include "dynamic_message.h"


typedef struct DynamicFgets *DynamicFgetsPtr;


extern DynamicFgetsPtr	 DynFgetsNew	 (FILE *fp);
extern DynamicFgetsPtr	 DynFgetsFree	 (DynamicFgetsPtr pDynFgets);
extern char		*DynFgets_get	 (DynamicFgetsPtr pDynFgets);
extern int		 DynFgets_status (DynamicFgetsPtr pDynFgets);

#endif  /* __DYNAMIC_FGETS_H__ */

//Local Variables:
//tab-width: 8
//End:
