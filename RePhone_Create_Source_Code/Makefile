# Makefile setup to mimic file source/destination locations for the Windows Eclipse IDE

# Set your toolchain path
TOOLCHAIN=/usr

# Set your LinkIt sdk path
LINKIT_ASSIST_SDK_PATH=/home/scriven/eclipse/cpp-mars/eclipse

# Set your LinkIt pack/push tools path
# https://github.com/mandl/LinkIt_Assist_2502
LINKIT_TOOLS_PATH=/home/scriven/eclipse/LinkIt_Assist_2502

CC=$(TOOLCHAIN)/bin/arm-none-eabi-gcc
AS=$(TOOLCHAIN)/bin/arm-none-eabi-as
LD=$(TOOLCHAIN)/bin/arm-none-eabi-gcc
OBJCOPY=$(TOOLCHAIN)/bin/arm-none-eabi-objcopy
OBJDUMP=$(TOOLCHAIN)/bin/arm-none-eabi-objdump
SIZE=$(TOOLCHAIN)/bin/arm-none-eabi-size
OBJDIR=./ARM

OBJECTS = $(addprefix $(OBJDIR)/, $(patsubst %.c, %.o, $(wildcard *.c)))
OBJECTS += $(OBJDIR)/gccmain.o

PROJECT = $(OBJDIR)/RePhone_Create_Source_Code_default

WORKSPACE_PATH = ./

SYS_OBJ_SRC += $(LINKIT_ASSIST_SDK_PATH)/LINKIT_ASSIST_SDK/lib/LINKIT10/src
INCLUDE_PATHS += -I. -I$(LINKIT_ASSIST_SDK_PATH)/LINKIT_ASSIST_SDK/include -I$(WORKSPACE_PATH)
LIBRARY_PATHS += -L$(LINKIT_ASSIST_SDK_PATH)/LINKIT_ASSIST_SDK/lib/LINKIT10/armgcc
LIBRARIES += $(LINKIT_ASSIST_SDK_PATH)/LINKIT_ASSIST_SDK/lib/LINKIT10/armgcc/percommon.a -lm
LINKER_SCRIPT = $(LINKIT_ASSIST_SDK_PATH)/LINKIT_ASSIST_SDK/lib/LINKIT10/armgcc/scat.ld

###############################################################################


CPU = -mcpu=arm7tdmi-s -mthumb -mlittle-endian
CC_FLAGS = $(CPU) -mthumb-interwork -c -fvisibility=hidden -gdwarf-2 -gstrict-dwarf -fpic -O2 -fno-exceptions -fno-non-call-exceptions
CC_SYMBOLS += -D__HDK_LINKIT_ASSIST_2502__ -D__COMPILER_GCC__

LD_FLAGS = $(CPU) -O2 -Wl,--gc-sections --specs=nosys.specs -fpic -pie -Wl,-Map=$(PROJECT).map  -Wl,--entry=gcc_entry -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-unresolved-symbols
LD_SYS_LIBS =

# the pack tool https://github.com/mandl/LinkIt_Assist_2502
PACK= $(LINKIT_TOOLS_PATH)/merge_mtk.py

# the uploader tool https://github.com/mandl/LinkIt_Assist_2502
PUSH= $(LINKIT_TOOLS_PATH)/uploader.py

all: $(OBJDIR) $(PROJECT).vxp size

clean:
	rm -f $(PROJECT).vxp $(PROJECT).bin $(PROJECT).elf $(PROJECT).hex $(PROJECT).map $(PROJECT).lst $(OBJECTS)

$(OBJDIR)/*.s.o:
	$(AS) $(CPU) -o $@ $<

$(OBJDIR)/gccmain.o: $(SYS_OBJ_SRC)/gccmain.c
	$(CC)  $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu99   $(INCLUDE_PATHS) -o $@ $<

$(OBJDIR)/%.o: %.c
	$(CC)  $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu99   $(INCLUDE_PATHS) -o $@ $<

$(PROJECT).elf: $(OBJECTS)
	$(LD) $(LD_FLAGS) -T$(LINKER_SCRIPT) $(LIBRARY_PATHS) -o $@ -Wl,--start-group $^ $(LIBRARIES) $(LD_SYS_LIBS) -Wl,--end-group

$(PROJECT).bin: $(PROJECT).elf
	@$(OBJCOPY) -O binary $< $@

$(PROJECT).hex: $(PROJECT).elf
	@$(OBJCOPY) -O ihex $< $@

$(PROJECT).vxp: $(PROJECT).elf
	@$(OBJCOPY) --strip-debug $<
	@$(PACK) $< $@

$(PROJECT).lst: $(PROJECT).elf
	@$(OBJDUMP) -Sdh $< > $@

lst: $(PROJECT).lst

size: $(PROJECT).elf
	$(SIZE) $(PROJECT).elf

flash: $(PROJECT).vxp
	$(PUSH)

$(OBJDIR):
	mkdir $(OBJDIR)
