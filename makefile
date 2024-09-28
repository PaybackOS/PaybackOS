include make.config

# Define variables
SRC_DIR = src
OBJ_DIR = obj
TARGET = PaybackOS.elf

# Automatically find all source files
SRCS := $(shell find $(SRC_DIR) -name '*.cpp' -o -name '*.s' -o -name '*.asm')
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(patsubst $(SRC_DIR)/%.s,$(OBJ_DIR)/%.o,$(patsubst $(SRC_DIR)/%.asm,$(OBJ_DIR)/%.o,$(SRCS))))

# Ensure the object directory exists
$(shell mkdir -p $(OBJ_DIR))

# Define the build rules
build: $(OBJS)
	$(LD) -T linker.ld -o $(TARGET) $(LDFLAGS) $(OBJS)

# Pattern rules to build .o files from .s, .asm, and .cpp files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	mkdir -p $(dir $@)  # Create the target directory
	$(AS) -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm
	mkdir -p $(dir $@)  # Create the target directory
	$(AS) -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)  # Create the target directory
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create the GRUB iso
iso: build
	mkdir -p iso/boot/grub/
	cp grub.cfg iso/boot/grub/
	cp $(TARGET) iso/boot/
	grub-mkrescue iso/ -o PaybackOS.iso
	rm -rf iso

# Run the OS
run:
	qemu-system-x86_64 -cdrom PaybackOS.iso \
	    -d int -no-shutdown -no-reboot

# Clean rule to remove generated files
clean:
	rm -rf obj $(TARGET) iso *.iso

.PHONY: all build clean iso run
