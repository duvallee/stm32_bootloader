###############################################################################
#
#  	    File        : Makefile
#
#       Abstract    : Example Makefile for a C Project
#
#       Environment : Atollic TrueSTUDIO(R)
#
###############################################################################

SHELL                            = cmd

# -----------------------------------------------------------------------------
DEBUG 					            = 1
TARGET					            = stm32h743xi_bootloader

# Define output directory
OBJECT_DIR                       = Debug
BIN_DIR                          = $(OBJECT_DIR)

# -----------------------------------------------------------------------------
USB_BULK                         = 1
USB_CDC                          = 2
USB_DEVICE                       = USB_BULK

# -----------------------------------------------------------------------------
# System configuration
CC                               = arm-atollic-eabi-gcc
OBJCOPY 					            = arm-atollic-eabi-objcopy
SIZE    					            = arm-atollic-eabi-size

RM							            = rm -rf

# -----------------------------------------------------------------------------
# Link script file
LINK_SCRIPT                      = "stm32h7_flash.ld"

# -----------------------------------------------------------------------------
# COMMON FLAGS
INSTRUCTION                      := -mthumb
FLOAT				                  := -mhard-float
CPU						            := -mcpu=cortex-m7
FPU						            := -mfpu=fpv5-sp-d16
CHIP_DEF                         := -D"STM32H743xx"

#
MCU						            := $(INSTRUCTION) $(FLOAT) $(CPU) $(FPU)

# -----------------------------------------------------------------------------
# Assembler
A_INCLUDE				            :=
A_FLAGS				               := -c $(MCU) $(AS_INCLUDE) $(CHIP_DEF)
A_FLAGS				               += -specs=nano.specs -x assembler-with-cpp

ifeq ($(DEBUG), 1)
AFLAGS					            += -g -O0
else
AFLAGS					            += -O3
endif

# -----------------------------------------------------------------------------
# C
C_INCLUDE				            := -Iinc
C_INCLUDE				            += -Isrc/common/inc
ifeq ($(USB_DEVICE), $(USB_BULK))
C_INCLUDE				            += -Isrc/usb/bulk/inc
endif
ifeq ($(USB_DEVICE), $(USB_CDC))
C_INCLUDE				            += -Isrc/usb/cdc/inc
endif
C_INCLUDE				            += -IDrivers/STM32F4xx_HAL_Driver/Inc 
C_INCLUDE				            += -IDrivers/STM32F4xx_HAL_Driver/Inc/Legacy
C_INCLUDE				            += -IDrivers/CMSIS/Device/ST/STM32F4xx/Include
C_INCLUDE				            += -IDrivers/CMSIS/Include

C_DEFS					            := $(CHIP_DEF)
ifeq ($(USB_DEVICE), $(USB_BULK))
C_DEFS					            += -DSTM32F401_USB_BULK_DEVICE
endif
ifeq ($(USB_DEVICE), $(USB_CDC))
C_DEFS					            += -DSTM32F401_USB_CDC_DEVICE
endif

CFLAGS					            := -c $(MCU) $(C_INCLUDE) $(C_DEFS) 
CFLAGS					            += -Wall -ffunction-sections -fdata-sections -specs=nano.specs

ifeq ($(DEBUG), 1)
CFLAGS					            += -g -O0
else
CFLAGS					            += -O3
endif

ifeq ($(USB_DEVICE), $(USB_BULK))
C_DEFS					            += -DSTM32F401_USB_BULK_DEVICE
endif
ifeq ($(USB_DEVICE), $(USB_CDC))
C_DEFS					            += -DSTM32F401_USB_CDC_DEVICE
endif

# -----------------------------------------------------------------------------
L_FLAGS                          := -lm $(MCU) -Wl,--gc-sections -T$(LINK_SCRIPT) -static 
L_FLAGS                          += -Wl, --start-group -lc -lm -Wl,--end-group -specs=nano.specs
L_FLAGS                          += -specs=nosys.specs -Wl,-cref
L_FLAGS                          += "-Wl,-Map=$(BIN_DIR)/$(TARGET).map" -Wl,--defsym=malloc_getpagesize_P=0x1000


# --------------------------------------------------------------------
# C Source

# System Source
SYSTEM_SOURCE			            := ./src/system_stm32h7xx.c
SYSTEM_SOURCE			            += ./src/stm32h7xx_hal_msp.c
SYSTEM_SOURCE			            += ./src/stm32h7xx_it.c

# HAL Library Source
HAL_LIBRARY_SOURCE 	            := ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
HAL_LIBRARY_SOURCE 	            +=

# USB Device Driver
ifeq ($(USB_DEVICE), $(USB_BULK))
USB_DRIVER				            := 
USB_DRIVER				            += 
endif

ifeq ($(USB_DEVICE), $(USB_CDC))
USB_DRIVER				            := 
USB_DRIVER				            += 
endif

# User Source
USER_SOURCE				            := ./src/main.c
USER_SOURCE				            += 


C_SRC 						         := $(SYSTEM_SOURCE) $(HAL_LIBRARY_SOURCE) $(USB_DRIVER) $(USB_DRIVER)

# --------------------------------------------------------------------
# ASM Source
A_SRC 					            := ./startup/startup_stm32h753xx.s

# --------------------------------------------------------------------
OBJS 						            := $(C_SRC:%.c=$(OBJECT_DIR)/%.o) $(A_SRC:%.s=$(OBJECT_DIR)/%.o)
OBJS 						            := $(OBJS:%.S=$(OBJECT_DIR)/%.o)  


# --------------------------------------------------------------------
###############
# Build project
# Major targets
###############
all: $(TARGET)

$(TARGET): $(OBJS) 
	$(CC) -o "$(BIN_DIR)/$(TARGET).elf" $(OBJS) $(L_FLAGS)
	$(OBJCOPY) -O ihex "$(BIN_DIR)/$(TARGET).elf" "$(BIN_DIR)/$(TARGET).hex"
	$(OBJCOPY) -O binary "$(BIN_DIR)/$(TARGET).elf" "$(BIN_DIR)/$(TARGET).bin"
	$(SIZE) "$(BIN_DIR)/$(TARGET).elf"

clean:
	$(RM) $(OBJS) "$(BIN_DIR)/$(TARGET).elf" "$(BIN_DIR)/$(TARGET).map"


##################
# Implicit targets
##################
$(OBJECT_DIR)/%.o: %.c
	@mkdir $(subst /,\,$(dir $@)) 2> NUL || echo off
	$(CC) $(C_FLAGS) $< -o $@

$(OBJECT_DIR)/%.o: %.s
	@mkdir $(subst /,\,$(dir $@)) 2> NUL || echo off
	$(CC) $(A_FLAGS) $< -o $@
	
$(OBJECT_DIR)/%.o: %.S
	@mkdir $(subst /,\,$(dir $@)) 2> NUL || echo off
	$(CC) $(A_FLAGS) $< -o $@
 
 