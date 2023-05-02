TARGET = BluetoothController
OBJS = main.o pspuartprx.o

#USE_PSPSDK_LIBC = 1


PSP_FW_VERSION = 500
INCDIR =
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

BUILD_PRX = 1

LIBDIR =
LIBS = 
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = BluetoothController
PSP_EBOOT_ICON="icon0.png"
#PSP_EBOOT_PIC1="pic1.png"
#PSP_EBOOT_SND0="snd0.at3"

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
