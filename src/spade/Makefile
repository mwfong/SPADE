ifeq (, $(findstring clean, $(MAKECMDGOALS)))
_PROHIBITED_CMD = bugAll
endif

all:;		@ (cd util;              $(MAKE) $(MAKECMDGOALS))
		@ (cd test;              $(MAKE) $(MAKECMDGOALS))

clean:		all

debug:		all

##Local Variables:
##tab-width: 8
##End:
