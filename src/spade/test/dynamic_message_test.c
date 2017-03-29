#include <stdlib.h>	// atoi, random
#include <stdio.h>	// printf

#include "DynMsg.h"


GMsg_declare ();


  static void
_sprintfGen (const int nTimes)
{
  LMsg_declare ();
  int i;

  for (i = 0; i < nTimes; i++) {
    unsigned long r   = random ();
    int		  b   = (int) (r & 0x03L);
    int		  len = 0;

    if (GMsg_length () /* > 0 */) 
      GMsg_addchar ('|');

    LMsg_init ();

    switch (b) {
      case 0: {
	int j;

	len = (int) (r & 0x4FL);

	for (j = 0; j < len; j++) {
	  char baseChar;
	  int  offset = (int) (random () % 17L);

	  if (offset < 10)
	    baseChar = '0';
	  else {
	    offset -= 10;

	    if (offset < 6)
	      baseChar = 'A';
	    else {
	      offset   -= 6;
	      baseChar  = '_';
	    }
	  }

	  LMsg_addchar (baseChar + offset);
	}

	break;
      }

      case 1: {
	int j;

	len = (int) (r & 0x7FL);

	for (j = 0; j < len; j++) {
	  char baseChar;
	  int  offset = (int) (random () % 27L);

	  if (offset < 26)
	    baseChar = 'a';
	  else {
	    offset   -= 26;
	    baseChar  = '_';
	  }

	  LMsg_addchar (baseChar + offset);
	}

	break;
      }

      case 2: {
	int j;

	len = (int) (r & 0x7FL);

	for (j = 0; j < len; j++) {
	  char baseChar;
	  int  offset = (int) (random () % 53L);

	  if (offset < 26)
	    baseChar = 'a';
	  else {
	    offset -= 26;

	    if (offset < 26)
	      baseChar = 'A';
	    else {
	      offset   -= 26;
	      baseChar  = '_';
	    }
	  }

	  LMsg_addchar (baseChar + offset);
	}

	break;
      }

      case 3: {
	int j;

	len = (int) (r & 0xFFL);

	for (j = 0; j < len; j++) {
	  char baseChar;
	  int  offset = (int) (random () % 63L);

	  if (offset < 10)
	    baseChar = '0';
	  else {
	    offset -= 10;

	    if (offset < 26)
	      baseChar = 'a';
	    else {
	      offset -= 26;

	      if (offset < 26)
		baseChar = 'A';
	      else {
		offset   -= 26;
		baseChar  = '_';
	      }
	    }
	  }

	  LMsg_addchar (baseChar + offset);
	}

	break;
      }
    }

    DynMsg_sprintf (_pGDynMsg, "%ld, %d:%d, %s", r, b, len, LMsg_get ());
  }

  (void) printf ("%s\n", GMsg_get ());
}


  int
main (int argc, char **argv)
{
  GMsg_init ();

  --argc; ++argv;

  if (argc /* > 0 */) {
    while (argc /* > 0 */) {
      _sprintfGen (atoi (*argv));

      --argc; ++argv;
    }
  }
  else
    _sprintfGen (5);

  return 0;
}


//Local Variables:
//tab-width: 8
//End:
