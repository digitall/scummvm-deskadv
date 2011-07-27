MODULE := engines/deskadv

MODULE_OBJS = \
	console.o \
	deskadv.o \
	detection.o \
	graphics.o \
	resource.o \
	saveload.o \
	sound.o

# This module can be built as a plugin
ifeq ($(ENABLE_DESKADV), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk
