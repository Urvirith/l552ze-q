# ARM GCC COMPILER CALL

# Toolchain To Use
TOOLCHAIN	:= arm-none-eabi-
CC		    := $(TOOLCHAIN)gcc		# c compiler
AS			:= $(TOOLCHAIN)as		# assembler
LD 			:= $(TOOLCHAIN)ld 		# linker
OBJ 		:= $(TOOLCHAIN)objcopy	# Object Copy

# -Os				Optimize for Size
# -mcpu=cortex-m4	Compile for the ARM M4 Processor
# mthumb			Target the MTHUMB Instruction Set
TARGET_ARCH := -mcpu=cortex-m33
CFLAGS	  	:= -Os $(TARGET_ARCH) -mthumb
ASFLAGS		:= $(TARGET_ARCH) -mthumb
LDFLAGS 	:= -T 
OBJFLAGS	:= -O binary

SRC_DIR   	:= ./src
HAL_DIR   	:= ./src/hal
I2C_DRI   	:= ./src/driver/i2c
LINK_DIR 	:= ./src/linker
START_DIR	:= ./src/startup
OBJ_DIR		:= ./obj
BIN_DIR	  	:= ./bin

#ONLY ONE
STARTUP		:= startup_ARMCM33.s

#ONLY ONE
LINKER		:= gcc_arm.ld

#	EXAMPLE OF AUTOMATIC VARIABLES
#	%.o: %.c %.h common.h
#		$(CC) $(CFLAGS) -c $<
#
#	$@ Looks at the target
#	(Target)
#	%.o: 			%.c %.h common.h
#	
#	$< Looks at the first source
#			(First Source)
#	%.o: 	%.c 					%.h common.h
#		$(CC) $(CFLAGS) -c $<
#	$^ Looks at the first source
#			(All Source)
#	%.o: 	%.c %.h common.h
#		$(CC) $(CFLAGS) -c $^

OBJS =	$(OBJ_DIR)/common.o \
			$(OBJ_DIR)/gpio.o \
				$(OBJ_DIR)/rcc.o \
					$(OBJ_DIR)/timer.o \
						$(OBJ_DIR)/usart.o \
							$(OBJ_DIR)/spi.o \
								$(OBJ_DIR)/nvic.o \
									$(OBJ_DIR)/main.o

#	EXAMPLE OF AUTOMATIC VARIABLES
#	%.o: %.c %.h common.h
#		$(CC) $(CFLAGS) -c $<
#
#	$@ Looks at the target
#	(Target)
#	%.o: 			%.c %.h common.h
#	
#	$< Looks at the first source
#			(First Source)
#	%.o: 	%.c 					%.h common.h
#		$(CC) $(CFLAGS) -c $<
#	$^ Looks at the first source
#			(All Source)
#	%.o: 	%.c %.h common.h
#		$(CC) $(CFLAGS) -c $^
release: $(BIN_DIR)/main.bin

# Build An ELF 
$(BIN_DIR)/main.bin: $(BIN_DIR)/main.elf
	$(OBJ) $(OBJFLAGS) $^ $@

# Build An ELF 
$(BIN_DIR)/main.elf: $(LINK_DIR)/$(LINKER) $(OBJS) $(BIN_DIR)/startup.o
	$(LD) -Os -s $(LDFLAGS) $^ -o $@

# Build Dependances
$(BIN_DIR)/startup.o: $(START_DIR)/$(STARTUP)
	$(AS) $< $(ASFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	$(CC) $(CFLAGS) -c  $< -o $@

$(OBJ_DIR)/%.o: $(HAL_DIR)/%.c $(HAL_DIR)/%.h $(HAL_DIR)/common.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(BIN_DIR)/*.o
	rm -f $(BIN_DIR)/*.elf
	rm -f $(BIN_DIR)/*.bin

flash:
	STM32_Programmer_CLI -c port=SWD -w $(BLD_DIR)/main.bin 0x08000000

info:
	STM32_Programmer_CLI -c port=SWD

reset:
	STM32_Programmer_CLI -c port=SWD -rst

hard_reset:
	STM32_Programmer_CLI -c port=SWD -hardRst

setup:
	mkdir obj
	mkdir bin

# To Move The Rules
#sudo cp ./rules/*.rules /etc/udev/rules.d/