include make.config

# Define variables
SRC_DIR = src
OBJ_DIR = obj
TARGET = PaybackOS.elf

# Automatically find all source files excluding userspace unless specified
SRCS := $(shell find $(SRC_DIR) -name '*.cpp' -o -name '*.s' -o -name '*.asm' -not -path "$(SRC_DIR)/userspace/*")
USERSPACE_SRCS := $(shell find $(SRC_DIR)/userspace/ -name 'userspace_*.cpp' -o -name 'userspace_*.s' -o -name 'userspace_*.asm')

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(patsubst $(SRC_DIR)/%.s,$(OBJ_DIR)/%.o,$(patsubst $(SRC_DIR)/%.asm,$(OBJ_DIR)/%.o,$(SRCS))))
USERSPACE_OBJS := $(patsubst $(SRC_DIR)/userspace/%.cpp,$(OBJ_DIR)/userspace/%.o,$(patsubst $(SRC_DIR)/userspace/%.s,$(OBJ_DIR)/userspace/%.o,$(patsubst $(SRC_DIR)/userspace/%.asm,$(OBJ_DIR)/userspace/%.o,$(USERSPACE_SRCS))))

# Ensure the object directory exists
$(shell mkdir -p $(OBJ_DIR))

# Define the build rules
build: $(OBJS) $(USERSPACE_OBJS)
	$(LD) -T linker.ld -o $(TARGET) $(LDFLAGS) $(OBJS) $(USERSPACE_OBJS)

# Pattern rules to build .o files from .s, .asm, and .cpp files
# These rules will only match files in their respective directories
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	mkdir -p $(dir $@)  # Create the target directory
	$(AS) -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm
	mkdir -p $(dir $@)  # Create the target directory
	$(AS) -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)  # Create the target directory
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Pattern rule to build .o files from .s, .asm, and .cpp files in userspace
$(OBJ_DIR)/%.o: $(SRC_DIR)/userspace/%.s
	mkdir -p $(dir $@)  # Create the target directory
	$(AS) -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/userspace/%.asm
	mkdir -p $(dir $@)  # Create the target directory
	$(AS) -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/userspace/%.cpp
	mkdir -p $(dir $@)  # Create the target directory
	$(CXX) $(USERCXXFLAGS) -c $< -o $@

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