CONFIGURATION	= application DEBUG

ifneq (, $(findstring debug, $(MAKECMDGOALS)))
  CONFIGURATION += DEBUG
endif

PROGRAM_NAME	= dynamic_message_test

SRCS		= dynamic_message_test.c

LDFLAGS		= -L../util/$(OS_DIR) -lutil

CPPFLAGS	= -I. -I.. -I../util -Wall -pthread

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
