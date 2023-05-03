TARGET = pspuartprx
OBJS = main.o

PSPSDK=$(shell psp-config --pspsdk-path)

INCDIR =
#CFLAGS = -O2 -G0 -Wall
CFLAGS = -Os -G0 -Wall -fno-builtin-printf -I$(PSPSDK)/include # copy settings from psplink libs?
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

PSP_LARGE_MEMORY = 1
BUILD_PRX = 1
PRX_EXPORTS = pspuartprx.exp

#USE_KERNEL_LIBC=1
USE_KERNEL_LIBS=1

LIBDIR =
LDFLAGS = -nostartfiles
LIBS = 

include $(PSPSDK)/lib/build_prx.mak

LIBS += -lpsphprm_driver

all: #create .S file and copy to user folder
	psp-build-exports -s $(PRX_EXPORTS)
	move pspuartprx.S "../user/"
	copy pspuartprx.prx "../user/."
