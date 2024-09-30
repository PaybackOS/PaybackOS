#!/bin/sh

qemu-system-i386 -cdrom PaybackOS.iso -S -s &

gdb PaybackOS.elf \
        -ex 'target remote localhost:1234' \
        -ex 'layout src' \
        -ex 'layout regs' \
        -ex 'break _start' \
        -ex 'continue'

