![Alt text](screenshot.png?raw=true "a screenshot of the system when it boots")

This is a stripped-down version of C++ OS meant to act as a bootloader. It fits in the roughly 64kb of extra unused data between the MBR sector and the start of the first partition. The bootloader image itself compiles to around 62.5kb so I have to be really careful about modifying stuff to prevent the filesize from getting too large.

This was made before I had fixed *every* memory bug in C++ OS, and still has some old string resize bugs. Since this doesn't do anything besides find a file on a fat32 partition, load it into ram and then jump to it, this doesn't really matter.

I needed a way to simply boot my simple c++ kernel thingy. I couldn't figure out how to get grub or syslinux to do what I needed in any reasonable amount of effort and it ended up being better to make my own bootloader.

**If anyone finds a way to boot C++ OS using syslinux instead, let me know**

Works on bochs or qemu as well as a few motherboards with legacy ata controllers.

# Requirements
- gcc/g++
- nasm
- dd
dd is used by the bootloaderInstall.sh script to install the bootloader to a drive image that:
- has a MBR partition table
- has a FAT32 partition. I can't remember exactly what all the requirements are, but 1 FAT32 partition on a 2GB drive definitely works.

# How to use
- step 1 (optional): get a drive image with MBR and a FAT32 filesystem and put it in the directory of this project and call it "fat32test.bin".
- step 2: run "sh cross-buildLinkScript.sh"
- step 3: to test the bootloader standalone in qemu, do "qemu-system-i386 disk.bin". To test boot the drive image you just created, use "qemu-system-i386 -drive file=fat32test.bin,format=raw,index=0". Note that you will need a C++ OS kernel file named "SYS.BIN" at the root directory in order for it to get past the bootloader.

