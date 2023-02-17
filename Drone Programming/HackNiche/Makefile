
TARGET		?= PLUTOX

# Compile-time options
OPTIONS		?=

# Debugger optons, must be empty or GDB
DEBUG ?=



FLASH_SIZE ?=


NAME			 = Experience

VALID_TARGETS	 = PLUTOX 


ifeq ($(FLASH_SIZE),)
ifeq ($(TARGET),$(filter $(TARGET),PLUTOX))
FLASH_SIZE = 256
else
$(error FLASH_SIZE not configured for target)
endif
endif



ROOT		 := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))
SRC_DIR		 = $(ROOT)/src
OBJECT_DIR	 = $(ROOT)/obj
BIN_DIR		 = $(ROOT)/obj
PLATFORM_DIR = $(ROOT)/platform
CMSIS_DIR	 = $(ROOT)/lib/main/CMSIS
INCLUDE_DIRS	 = $(SRC_DIR)
LINKER_DIR	 = $(ROOT)/ld
LIB_DIR	 = $(ROOT)/libs



rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

CSOURCES        :=$(subst $(ROOT)/,,  $(call rwildcard,$(SRC_DIR)/,*.cpp))

CSOURCES        :=$(CSOURCES)\
                  $(subst $(ROOT)/,,  $(call rwildcard, $(LIB_DIR)/,*.cpp))

DIRECTORY = $(sort $(dir  $(call rwildcard, $(PLATFORM_DIR)/,*.*)))


INCLUDE_DIRS:=$(DIRECTORY)
             


DIRECTORY = $(sort $(dir  $(call rwildcard, $(SRC_DIR)/,*.*)))


INCLUDE_DIRS:=$(INCLUDE_DIRS) \
              $(DIRECTORY)







LD_SCRIPT	 = $(LINKER_DIR)/stm32_flash_f303_$(FLASH_SIZE)k.ld

ARCH_FLAGS	 = -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -Wdouble-promotion
DEVICE_FLAGS = -DSTM32F303xC -DSTM32F303
TARGET_FLAGS = -D$(TARGET)

ifneq ($(FLASH_SIZE),)
DEVICE_FLAGS := $(DEVICE_FLAGS) -DFLASH_SIZE=$(FLASH_SIZE)
endif


CC		 = arm-none-eabi-g++
C		 = arm-none-eabi-gcc
OBJCOPY		 = arm-none-eabi-objcopy
SIZE		 =arm-none-eabi-size


ifeq ($(DEBUG),GDB)
OPTIMIZE	 = -O0
LTO_FLAGS	 = $(OPTIMIZE)
else
OPTIMIZE	 = -Os
LTO_FLAGS	 = -flto -fuse-linker-plugin $(OPTIMIZE)
endif

DEBUG_FLAGS	 = -ggdb3 -DDEBUG

CFLAGS		 = $(ARCH_FLAGS) \
		   $(LTO_FLAGS) \
		   $(addprefix -D,$(OPTIONS)) \
		   $(addprefix -I,$(INCLUDE_DIRS)) \
		   $(DEBUG_FLAGS) \
		   -std=gnu99 \
		   -Wall -Wextra -Wunsafe-loop-optimizations -Wdouble-promotion \
		   -ffunction-sections \
		   -fdata-sections \
		   $(DEVICE_FLAGS) \
		   -DUSE_STDPERIPH_DRIVER \
		   $(TARGET_FLAGS) \
		   -D'__NAME__="$(NAME)"' \
		   -D'__TARGET__="$(TARGET)"' \
		   -save-temps=obj \
		   -MMD -MP


CCFLAGS		 = $(ARCH_FLAGS) \
		   $(LTO_FLAGS) \
		   $(addprefix -D,$(OPTIONS)) \
		   $(addprefix -I,$(INCLUDE_DIRS)) \
		   $(DEBUG_FLAGS) \
		   -std=gnu++98 \
		   -Wall -Wextra -Wunsafe-loop-optimizations -Wdouble-promotion \
		   -ffunction-sections \
		   -fdata-sections \
		   $(DEVICE_FLAGS) \
		   -DUSE_STDPERIPH_DRIVER \
		   $(TARGET_FLAGS) \
		   -D'__NAME__="$(NAME)"' \
		   -D'__TARGET__="$(TARGET)"' \
		  -save-temps=obj \
		   -MMD -MP

ASFLAGS		 = $(ARCH_FLAGS) \
		   -x assembler-with-cpp \
		   $(addprefix -I,$(INCLUDE_DIRS)) \
		  -MMD -MP

LDFLAGS		 = -lm \
		   -nostartfiles \
		   --specs=nosys.specs \
		   -lc \
		   -lnosys \
		   $(ARCH_FLAGS) \
		   $(LTO_FLAGS) \
		   $(DEBUG_FLAGS) \
		   -static \
		   -L$(LIB_DIR) -lpluto_0.3 \
		   -Wl,-gc-sections,-Map,$(TARGET_MAP) \
		   -Wl,-L$(LINKER_DIR) \
		   -T$(LD_SCRIPT)





ifeq ($(filter $(TARGET),$(VALID_TARGETS)),)
$(error Target '$(TARGET)' is not valid, must be one of $(VALID_TARGETS))
endif

TARGET_BIN	 = $(BIN_DIR)/$(NAME)_$(TARGET).bin
TARGET_HEX	 = $(BIN_DIR)/$(NAME)_$(TARGET).hex
TARGET_ELF	 = $(OBJECT_DIR)/$(NAME)_$(TARGET).elf
TARGET_OBJS	 =  $(addsuffix .o,$(addprefix $(OBJECT_DIR)/$(TARGET)/,$(basename $(CSOURCES))))
TARGET_DEPS	 = $(addsuffix .d,$(addprefix $(OBJECT_DIR)/$(TARGET)/,$(basename $($(TARGET)_SRC))))
TARGET_MAP	 = $(OBJECT_DIR)/$(NAME)_$(TARGET).map


$(info $(TARGET_OBJS))


$(TARGET_HEX): $(TARGET_ELF)
	$(OBJCOPY) -O ihex --set-start 0x8000000 $< $@

$(TARGET_BIN): $(TARGET_ELF)
	$(OBJCOPY) -O binary $< $@

$(TARGET_ELF): $(TARGET_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
	$(SIZE) $(TARGET_ELF) 

# Compile


$(OBJECT_DIR)/$(TARGET)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo %% $(notdir $<)
	@$(CC) -c -o $@ $(CCFLAGS) $<


$(OBJECT_DIR)/$(TARGET)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo %% $(notdir $<)
	@$(C) -c -o $@ $(CFLAGS) $<

# Assemble
$(OBJECT_DIR)/$(TARGET)/%.o: %.s
	@mkdir -p $(dir $@)
	@echo %% $(notdir $<)
	@$(CC) -c -o $@ $(ASFLAGS) $<

$(OBJECT_DIR)/$(TARGET)/%.o: %.S
	@mkdir -p $(dir $@)
	@echo %% $(notdir $<)
	@$(CC) -c -o $@ $(ASFLAGS) $<


## all         : default task; compile C code, build firmware
all: binary

## clean       : clean up all temporary / machine-generated files
clean:
	rm -f $(TARGET_BIN) $(TARGET_HEX) $(TARGET_ELF) $(TARGET_OBJS) $(TARGET_MAP)
	rm -rf $(OBJECT_DIR)/$(TARGET)
	cd src/test && $(MAKE) clean || true


binary: $(TARGET_HEX)

# rebuild everything when makefile changes
$(TARGET_OBJS) : Makefile

# include auto-generated dependencies
-include $(TARGET_DEPS)
