TARGET = pspuartprx
OBJS = main.o

INCDIR =
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = (CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = (CFLAGS)

BUILD_PRX = 1
PRX_EXPORTS = pspuartprx.exp

USE_KERNEL_LIBC=1
USE_KERNEL_LIBS=1

LIBDIR =
LDFLAGS = -nostartfiles
LIBS = 

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build_prx.mak

LIBS += -lpsphprm_driver