# Getting tools

## Installing the tools (debian and arch based)
Note:
All of these can likely be found on other distros.

To install the deps first only building on linux is supported, if you get it working on another OS, make a PR for our wiki.

$ = root

### Debian
```bash
$ apt install qemu-system nasm xorriso grub-pc-bin grub-common
```

### Arch linux
```bash
$ pacman -S qemu nasm grub xorriso
```

Now one thing we did not install is our cross compiler, this will require either building it from source or using brew.

## Cross compiler
### Brew
First install [brew](https://brew.sh) then run this command
```bash
brew install x86_64-elf-gcc
```
This will install our cross compiler
### Build from source
If you decide to build from source you need to follow these [instructions](https://wiki.osdev.org/GCC_Cross-Compiler) please note that you MUST compile it for x86_64-elf instead of i686-elf.