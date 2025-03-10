g++ -c -march=i486 -mtune=i486 -m32 -mfpmath=387 -fno-pie -nodefaultlibs -nostdlib -fno-exceptions -fno-stack-protector -O1 -o system.o system.cpp

nasm -g -f elf32 -o bootloader.o bootloader.asm
nasm -g -f elf32 -o misc_tools.o misc_tools.asm

g++ -w -march=i486 -mtune=i486 -m32 -mfpmath=387 -fno-pie -nodefaultlibs -nostdlib -O1 -fstack-usage -o disk.bin -T link.ld system.o misc_tools.o bootloader.o
# add -lgcc to the end of that last command if getting errors
#simply replace g++ with the location of your cross compiler's g++ executable. I replaced that with g++ in the github repo for readability reasons
#note that it doesn't seem to make a difference on real hardware or emulators if you use a cross compiler but I want to get this working on a 486 pc which is why all those parameters are in there

#get the bootloader intalled to fat32test.bin
sh bootloaderInstall.sh
