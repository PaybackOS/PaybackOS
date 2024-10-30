include make.config

# Define variables
SRC_DIR = src
USERSPACE_DIR = userspace
OBJ_DIR = obj
TARGET = PaybackOS.elf

# Automatically find all source files in src/ including .c files and excluding userspace/ unless specified
SRCS := $(shell find $(SRC_DIR) -name '*.cpp' -o -name '*.c' -o -name '*.s' -o -name '*.asm' -not -path "$(SRC_DIR)/userspace/*")

# Automatically find all source files in userspace/
USERSPACE_SRCS := $(shell find $(USERSPACE_DIR) -name '*.cpp' -o -name '*.c' -o -name '*.s' -o -name '*.asm')

# Object files for src/ and userspace/
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(patsubst $(SRC_DIR)/%.s,$(OBJ_DIR)/%.o,$(patsubst $(SRC_DIR)/%.asm,$(OBJ_DIR)/%.o,$(SRCS)))))
USERSPACE_OBJS := $(patsubst $(USERSPACE_DIR)/%.cpp,$(OBJ_DIR)/userspace/%.o,$(patsubst $(USERSPACE_DIR)/%.c,$(OBJ_DIR)/userspace/%.o,$(patsubst $(USERSPACE_DIR)/%.s,$(OBJ_DIR)/userspace/%.o,$(patsubst $(USERSPACE_DIR)/%.asm,$(OBJ_DIR)/userspace/%.o,$(USERSPACE_SRCS)))))

# Ensure the object directory exists
$(shell mkdir -p $(OBJ_DIR)/userspace)

# Define the build rules
build: $(OBJS) $(USERSPACE_OBJS)
	$(LD) -T linker.ld -o $(TARGET) $(LDFLAGS) $(OBJS) $(USERSPACE_OBJS)

# Pattern rules to build .o files from .s, .asm, .cpp, and .c files for src/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	mkdir -p $(dir $@)  # Create the target directory
	$(AS) $(ASFLAGS) -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm
	mkdir -p $(dir $@)  # Create the target directory
	$(AS) $(ASFLAGS) -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)  # Create the target directory
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)  # Create the target directory
	$(CC) $(CFLAGS) -c $< -o $@

# Pattern rules to build .o files from .s, .asm, .cpp, and .c files for userspace/
$(OBJ_DIR)/userspace/%.o: $(USERSPACE_DIR)/%.s
	mkdir -p $(dir $@)  # Create the target directory
	$(AS) $(ASFLAGS) -o $@ $<

$(OBJ_DIR)/userspace/%.o: $(USERSPACE_DIR)/%.asm
	mkdir -p $(dir $@)  # Create the target directory
	$(AS) $(ASFLAGS) -o $@ $<

$(OBJ_DIR)/userspace/%.o: $(USERSPACE_DIR)/%.cpp
	mkdir -p $(dir $@)  # Create the target directory
	$(CXX) $(USERCXXFLAGS) -c $< -o $@

$(OBJ_DIR)/userspace/%.o: $(USERSPACE_DIR)/%.c
	mkdir -p $(dir $@)  # Create the target directory
	$(CC) $(USERCFLAGS) $< -o $@

# Create the GRUB iso
iso: build
	mkdir -p iso/boot/grub/
	cp grub.cfg iso/boot/grub/
	cp $(TARGET) iso/boot/
	grub-mkrescue iso/ -o PaybackOS.iso
	rm -rf iso

# Run the OS
run:
	qemu-system-i386 -hda PaybackOS.iso

# Clean rule to remove generated files
clean:
	rm -rf obj $(TARGET) iso *.iso *.log

.PHONY: all build clean iso run
