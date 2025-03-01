#ifndef COMMANDS_H
#define COMMANDS_H

//deals with processing commands. Returns true if inputted thing was a valid command. Returns false if inputted command was something un-runnable
bool parseCommand(string input);

bool usedMemory(string input);

bool pciCheck(string input);

bool clearScreenCommand(string input);

bool colorTest(string input);

//substring very obviosuly showcases any problems with memory allocation
bool substringTest(string input);

bool printCpuInfo();

bool debugCommand1(string input);

bool debugCommand2(string input);

bool debugCommand3(string input);

bool memLeak(int size);

bool memoryInfo(string input);

bool stringSplitTest(string input);

bool md5Test(string input);

//aight, I need a basic hex reader now
bool readCommand(string input);

bool atatestCommand(string input);

bool MBR_DRIVE_MODE = 0;        //which ata drive to do the commands on
bool mbrInfoCommand(string input);
bool mbrInfoSetCommand(string input);

void printAllFiles(unsigned int LBA, unsigned int driveNum, filesystemInfo *sys);

bool printFile(char *input);

//read an address and write it to the screen. kind of like a big read only hex editor
//bool readCommand(string input);

//bool writeCommand(string input);

//bool rCommand(string input);

//string currentDirectory = "/";
dataVolumeInfo selectedVolume;
//fileInfo parentDirectory;
//let's try to make drives and partitions different things
//you can have multiple partitions on 1 drive, even on MBR
bool lsCommand(string input);

bool cdCommand(string input);

bool mountCommand(unsigned int partitionNumber);

bool fileSizeCommand(string input);

bool fatLoadCommand(string input);

//boot a binary file in protected mode. Most binary files need to be booted in real mode.
//the only purpose of this function is to boot a c++ os binary, since the bootloader and system have to be seperate
bool boot32(string input);

#include "commands.hpp"

#endif