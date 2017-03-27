CONFIGURATION	= library DEBUG

ifneq (, $(findstring debug, $(MAKECMDGOALS)))
  CONFIGURATION += DEBUG
endif

LIBRARY_NAME	= libutil.a

SRCS		= dynamic_message.c

CPPFLAGS	= -I. -I.. -Wall -pthread

ifneq (, $(findstring DEBUG, $(CONFIGURATION)))
  CPPFLAGS     += -DDEBUG
endif

LDFLAGS.dyn	= -pthread -lz

TOOL_DIR	= ..

include ../Makefile.base

debug:		all

##Local Variables:
##tab-width: 8
##End:
