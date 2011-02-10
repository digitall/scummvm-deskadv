MODULE := engines/deskadv

MODULE_OBJS = \
	console.o \
	deskadv.o \
	detection.o

# This module can be built as a plugin
ifdef BUILD_PLUGINS
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk
