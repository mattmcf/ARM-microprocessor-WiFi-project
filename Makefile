# Where to find the CodeSourcery tools
BINDIR = /opt/CodeSourcery/bin/

# Which assembler and linker to use
AS = $(BINDIR)/arm-none-eabi-as
CC = $(BINDIR)/arm-none-eabi-gcc
LD = $(BINDIR)/arm-none-eabi-ld

# 
# Flags for the different tools:
#

# Assembler:
# -c              : create intermediate object file only
# -g              : generate debugging information in object file
# -mthumb         : generate thumb code (vs. ARM code - not supported on M4)
# -mcpu=cortex-m4 : target the Cortex-M4 processor
ASFLAGS = -c -g -mthumb -mcpu=cortex-m4

# Compiler
# -c              : create intermediate object file only
# -g              : generate debugging information in object file
# -nostdinc       : do not use standard include files
# -MD 			  : Generate build rules based on #included header dependencies
# -MP             : Generate a phony target for each dependency other than make
#                 : (this works around make errors if a header file is removed)
# -mthumb         : generate thumb code (vs. ARM code - not supported on M4)
# -mcpu=cortex-m4 : target the Cortex-M4 processor
CFLAGS = -c -g -nostdinc -I. -MD -MP -mcpu=cortex-m4 -mthumb

# Linker
# -T<script>      : Use the linker script <script> - for memory layout
# -nostdlib       : do not link in the standard libraries
# -nostartfiles   : do not link in CodeSourcery initialization code
# -g              : generate debugging information in output file
LDFLAGS = -TSTM32F407VG.ld -nostdlib -nostartfiles -g 

# 
# Declare some generic build rules to automatically build:
# NOTE: -o $@ $< means "generate output file with name matching input filename + .o"
# 
# .o from .S (Assembler)
%.o : %.S
	$(AS) $(ASFLAGS) -o $@ $<
# .o from .c, (Compiler)
%.o : %.c 
	$(CC) $(CFLAGS) -o $@ $<
	
# Assume all .c and .S files in the current directory should be built and that
# they are dependencies for the target
S_SRCS = $(shell find . -maxdepth 1 -name "*.S")
C_SRCS = $(shell find . -maxdepth 1 -name "*.c")
# Rename .S->.o, .c->.o to create object file names
S_OBJS = $(S_SRCS:.S=.o)
C_OBJS = $(C_SRCS:.c=.o)
# Combine .S and .c based object files into "OBJS" variable
OBJS = $(notdir $(S_OBJS) $(C_OBJS))

# For each object file, look for an associated ".d" dependency file indicating which
# (if any) header files the object file depends on.  The dependency file contains 
# rules for building the objects if any of the header files change...
# "-"include will continue even if the *.d file doesn't exist...
-include $(OBJS:.o=.d)
	
# Eclipse calls "make all" when a project build is requested
all: lab3

#
# All header 
lab3: $(OBJS)
	$(LD) $(LDFLAGS) -o lab3.elf $(OBJS) 

# Eclipse calls "make clean" when a project clean is requested	
clean:
	rm -f *.o *.d *.elf


