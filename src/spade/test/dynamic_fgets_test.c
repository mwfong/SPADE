#include <errno.h>
#include <stdio.h>	// fprintf
#include <string.h>	// strerror

#include "dynamic_fgets.h"


  int
main (int argc, char **argv)
{
  FILE		  *pFile = stdin;
  DynamicFgetsPtr  pDynFgets;
  int		   i = 0;

  --argc; ++argv;

  if (argc /* > 0 */) {
    pFile = fopen (*argv, "r");

    if (pFile == (FILE *) NULL) {
      (void) fprintf (stderr, "Failed to open %s: %s\n", *argv, strerror (errno));
      return 1;
    }
  }

  pDynFgets = DynFgetsNew (pFile);

  while (1) {
    char *pString = DynFgets_get (pDynFgets);

    if (pString /* != (char *) NULL */)
      (void) printf ("%3d. %s", ++i, pString);
    else {
      int status = DynFgets_status (pDynFgets);

      if (status /* != 0 */)
	perror ("Unexpected error");

      break;
    }
  }

  pDynFgets = DynFgetsFree (pDynFgets);

  return 0;
}

//Local Variables:
//tab-width: 8
//End:
