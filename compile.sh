#!/bin/bash

export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

rm *.o
rm os.bin
rm -r -f isodir

nasm -felf32 boot.asm -o boot.o
nasm -felf32 gdt.asm -o gdt.o
nasm -felf32 interrupt.asm -o interrupt.o
for i in `ls *.c | sed 's/\.c//'` 
do
i686-elf-gcc -c $i.c -o $i.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
done
#i686-elf-gcc -c main.c -o main.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
#i686-elf-gcc -c isr.c -o isr.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
#i686-elf-gcc -c idt.c -o idt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
#i686-elf-gcc -c entry.c entry.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
#i686-elf-gcc -c gdt.c gdt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
#i686-elf-gcc -c vfs.c vfs.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
#i686-elf-gcc -c common.c -o common.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

i=`ls *\.o`
i686-elf-gcc -T link.ld -o os.bin -ffreestanding -nostdlib -O2 $i -lgcc

#i686-elf-gcc -T linker_adv.ld -o os.bin -ffreestanding -O2 -nostdlib boot_adv.o kernel_adv.o isr.o descriptor_tables.o common.o -lgcc

grub-file --is-x86-multiboot os.bin
if grub-file --is-x86-multiboot os.bin; then
 echo multiboot confirmed
else
 echo the file is not multiboot
fi

rm -r isodir
mkdir -p isodir/boot/grub
cp os.bin isodir/boot/os.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o os.iso isodir --xorriso=./xorriso/xorriso-1.4.6/xorriso/xorriso

rm *.o
rm -r -f isodir

qemu-system-i386 -cdrom os.iso -soundhw pcspk
