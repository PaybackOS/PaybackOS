# Building PaybackOS

## Installing deps
To install the deps first only building on linux is supported, if you get it working on another OS, make a PR for our wiki.

$ = root

### Debian
```bash
$ apt install qemu-system clang nasm xorriso grub-pc-bin grub-common
```

### Arch linux
```bash
$ pacman -S qemu clang nasm grub xorriso
```

And once you have your tools installed run this command for a 64bit ISO
```bash
make build-x86_64
```