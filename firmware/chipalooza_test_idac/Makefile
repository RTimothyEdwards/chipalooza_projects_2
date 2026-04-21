#-----------------------------------------------
# Makefile for Caravel projects
#-----------------------------------------------
#TOOLCHAIN_PATH=/usr/local/bin/
TOOLCHAIN_PATH=/opt/riscv32i/bin/

# Set the prefix for `riscvXX-unknown-elf-*`
# On installations using `multilib`, this will be `riscv64` even for compiling to 32-bit targets
#TOOLCHAIN_PREFIX=riscv64-unknown-elf
TOOLCHAIN_PREFIX=riscv32-unknown-elf
ARCH=rv32i_zicsr

INCLUDES=-I$(shell pwd) -I../ -I../vex -I../vex/generated/

# ---- Test patterns for chipalooza test chip 2 ----

.SUFFIXES:

# Note:  If the testbench .c file name does not match the directory name, set
#	 PATTERN to the base name of the .c file.
PATTERN := $(shell basename $(CURDIR))

SRCS = ../vex/crt0_vex.S ../vex/isr.c ../vex/stub.c ../chipalooza_util.c
CFLAGS = -ffreestanding -nostdlib -mabi=ilp32 -march=$(ARCH) -DRISCV

hex:  ${PATTERN:=.hex}

%.elf: %.c $(SRCS) ../vex/sections.lds
	$(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-gcc -I../ -I../vex/ -I../vex/generated/ $(CFLAGS) -O0 -Wl,-Bstatic,-T,../vex/sections.lds,--strip-debug -o $@ $(SRCS) $<
	${TOOLCHAIN_PATH}$(TOOLCHAIN_PREFIX)-objdump -D $(PATTERN).elf > $(PATTERN).lst

%.hex: %.elf
	$(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-objcopy -O verilog $< $@
	sed -ie 's/@1000/@0000/g' $@

%.bin: %.elf
	$(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-objcopy -O binary $< $@

flash: $(PATTERN).hex
	python3 ../util/caravel_hkflash.py $(PATTERN).hex

# ---- Clean ----

clean:
	rm -f *.elf *.hex *.bin *.vvp *.vcd *.hexe *.lst

.PHONY: clean hex all flash

