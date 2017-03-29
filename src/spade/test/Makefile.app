CONFIGURATION	= application DEBUG

ifneq (, $(findstring debug, $(MAKECMDGOALS)))
  CONFIGURATION += DEBUG
endif

ifneq (, $(findstring clean, $(MAKECMDGOALS)))
  _TARGET = clean
else
  _TARGET = clean
endif

ifneq (, $(findstring message, $(MAKECMDGOALS)))
  PNAME = dynamic_message_test
endif

ifneq (, $(findstring fgets, $(MAKECMDGOALS)))
  PNAME = dynamic_fgets_test
endif

.ALWAYS_EVAL	+= $(shell if test -f /dev/tty ; then			\
		     echo ...building PNAME $(PNAME) >> /dev/tty ;	\
		     fi)

PROGRAM_NAME	= $(PNAME)

SRCS		= $(PNAME).c

LDFLAGS		= -L../util/$(OS_DIR) -lutil

CPPFLAGS	= -I. -I.. -I../util -Wall -pthread

ifneq (, $(findstring DEBUG, $(CONFIGURATION)))
  CPPFLAGS     += -DDEBUG
endif

LDFLAGS.dyn	= -pthread -lz

TOOL_DIR	= ..

include ../Makefile.base

message:	$(_TARGET)

fgets:		$(_TARGET)

debug:		all

##Local Variables:
##tab-width: 8
##End:
