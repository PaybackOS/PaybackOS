include make.config

# Define the build rules
build: $(OBJ)
	$(LD) -T linker.ld -o $(TARGET) $(LDFLAGS) $(OBJ)

# Pattern rule to build .o files from .s files
src/%.o: src/%.s
	$(AS) -o $@ $<

# Pattern rule to build .o files from .asm files
src/%.o: src/%.asm
	$(AS) -o $@ $<

# Pattern rule to build .o files from .c files
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create the GRUB iso
iso:
	mkdir -p iso/boot/grub/
	cp grub.cfg iso/boot/grub/
	mv $(TARGET) iso/boot/
	grub-mkrescue iso/ -o PaybackOS.iso
	rm -rf iso

# Run the OS
run:
	qemu-system-x86_64 -cdrom PaybackOS.iso 

# Clean rule to remove generated files
clean:
	rm -rf $(OBJ) $(TARGET) iso *.iso

.PHONY: ALL build clean
