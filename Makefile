# ARM GCC COMPILER CALL
CC		    := arm-none-eabi-gcc		# c compiler
AS			:= arm-none-eabi-as			# assembler
LD 			:= arm-none-eabi-ld 		# linker
OBJ 		:= arm-none-eabi-objcopy	# Object Copy

# -Os				Optimize for Size
# -mcpu=cortex-m4	Compile for the ARM M4 Processor
# mthumb			Target the MTHUMB Instruction Set
CFLAGS	  	:= -Os -mcpu=cortex-m4 -mthumb
ASFLAGS		:= -mcpu=cortex-m4 -mthumb
LDFLAGS 	:= -T 
OBJFLAGS	:= -O binary

SRC_DIR   	:= ./src
HAL_DIR   	:= ./src/hal
I2C_DRI   	:= ./src/driver/i2c
BLD_DIR 	:= ./build
SRC_DIR   	:= ./src
LINK_DIR 	:= ./linker
START_DIR	:= ./startup

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

OBJS =	$(OBJ_DIR)main.o

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
release: bin/main.bin

# Build An ELF 
build/main.bin: build/main.elf
	$(OBJ) $(OBJFLAGS) $^ $@

# Build An ELF 
build/main.elf: $(LINK_DIR)/gcc_arm.ld bin/main.o $(BLD_DIR)startup.o
	$(LD) -Os -s $(LDFLAGS) $^ -o $@

# Build An Single Object 
bin/main.o: $(OBJS)
	$(LD) -r $^ -o $@

# Build Dependances
$(BLD_DIR)startup.o: $(START_DIR)/startup_ARMCM4.S
	$(AS) $< $(ASFLAGS) -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	$(CC) $(CFLAGS) -c  $< -o $@

clean:
	rm -f $(OBJ_DIR)*.o
	rm -f $(BIN_DIR)*.o
	rm -f $(BIN_DIR)*.elf
	rm -f $(BIN_DIR)*.bin

flash:
	st-flash write $(BIN_DIR)main.bin 0x08000000

