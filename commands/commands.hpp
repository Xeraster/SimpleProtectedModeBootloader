bool parseCommand(string input)
{
    
    //help command
    //string helpQuery = input.substr(0,5);
    string temporary = input;
    printString(temporary, 0x0A);
    if (input.substr(0,4) == "help")
    //if (temporary.at(0) == 'h' && temporary.at(1) == 'e' && temporary.at(2) == 'l' && temporary.at(3) == 'p')
    {
        if (input == "help -please")
        {
            consoleNewLine(3);
            printString("Yeeeeaah no. Go to: https://github.com/Xeraster/SimpleProtectedModeOS and figure it out yourself noob", 0x0F);
            return true;
        }
        else if (input.contains("-p"))
        {
            consoleNewLine(3);
            printString("no", 0x0F);
            return true;
        }
        else if (input.contains("-f"))
        {
            consoleNewLine(3);
            printString("Nice try, but the -f switch only does this", 0x0F);
            consoleNewLine(3);
            printString("maybe try saying please?", 0x0F);
            return true;
        }
        else if (input.contains("-h"))
        {
            consoleNewLine(3);
            printString("NOPE! YOU JUST GOT PRANKED! Try 'help -f' to see the help screen for real.", 0x0F);
            return true;
        }
        else
        {
            consoleNewLine(3);
            printString("help is for losers. Git gud noob. Try 'help -h' for more information", 0x0F);
            return true;
        }
        return true;

    }

    else if (temporary.substr(0,8) == "pcicheck")
    {
        consoleNewLine(3);
        pciCheck(temporary);
        return true;
    }

    else if (input == "mem")
    {
        consoleNewLine(3);
        usedMemory(input);
        return true;
    }

    else if (input == "clear")
    {
        clearScreen(3);
        setCurPos(0, 1);
        return true;
    }

    else if (input == "colortest")
    {
        colorTest(input);
        return true;
    }

    else if (input == "substringtest")
    {
        substringTest(input);
        return true;
    }

    else if (input == "cpuinfo")
    {
        printCpuInfo();
        return true;
    }

    else if (input == "debug1")
    {
        debugCommand1(input);
        return true;
    }

    else if (input == "debug2")
    {
        debugCommand2(input);
        return true;
    }

    else if (input == "debug3")
    {
        debugCommand3(input);
        return true;
    }

    else if (input == "memleak")
    {
        memLeak(1);
        return true;
    }

    else if (input == "meminfo")
    {
        consoleNewLine(3);
        memoryInfo(input);
        //consoleNewLine(3);
        return true;
    }

    else if (input.substr(0,10) == "mbrinfoset")
    {
        mbrInfoSetCommand(input.substr(10,input.length()));
        return true;
    }

    else if (input.substr(0,7) == "mbrinfo")
    {
        mbrInfoCommand(input);
        return true;
    }


    //md5 command. need help figuring out which version? the md5 command was added 10/18/2018
    else if (input.substr(0,4) == "md5 ")
    {
        md5Test(temporary.substr(4,temporary.length()));
        return true;
    }

    else if (input.substr(0,7) == "atatest")
    {
        atatestCommand(input);
        return true;
    }

    else if (temporary.substr(0,5) == "read ")
    {
        readCommand(temporary.substr(5,temporary.length()));

        return true;
    }

    //else if (temporary.substr(0, 4) == "split")
    else if (temporary == "split")
    {
        stringSplitTest("todo");
        return true;
    }

    else if (input.substr(0,2) == "ls")
    {
        lsCommand(input);
        return true;
    }

    else if (input.substr(0,6) == "mount ")
    {
        unsigned int part = input.at(6) - 48;
        if (part < 0 | part > 9)
        {
            consoleNewLine();
            printString("Bad", 0x0F);
            return false;
        }

        mountCommand(part);
        return true;
    }

    else if (input.substr(0,3) == "cd ")
    {
        consoleNewLine();
        printString("before cd", 0x0F);
        cdCommand(input.substr(3, input.length()));
        printString("after cd", 0x0F);
        //printString("the cd command", 0x0F);
        return true;
    }

    else if (input.substr(0,5) == "size ")
    {
        fileSizeCommand(input.substr(5, input.length()));       //to save cpu cycles, my substr concatenates overruns so you dont have to waste memory and cpu cycles calculating the right length to avoid going over
        return true;
    }

    else if (input == "fatlba")
    {
        consoleNewLine();
        printString("LBA of first FAT = ",0x0F);
        printInt(FATLBA(&selectedVolume.fsinfo), 0x0F);
        return true;
    }

    else if (input.substr(0,8) == "fatload ")
    {
        consoleNewLine();
        fatLoadCommand(input.substr(8,input.length()));
        return true;
    }

    else if(input.substr(0,5) == "boot ")
    {
        consoleNewLine();
        boot32(input.substr(5,input.length()));
        return true;
    }

    //reprint whatever the user typed. If memory allocation is broken even slightly, this will very obviously be wrong which makes it a great tool for troubleshooting
    //printString(temporary, 0x0D);

    //printString(input, 0x0E);
    //print32bitNumber(input, 1800);
    return false;
}

bool usedMemory(string input)
{
    //get amount of used dynamic memory
    //unsigned int usedMemory = 0;
	//for (int i = 0; i < memf.getSize(); i++)
	//{   
        //some cross compilers don't do nullptr
	//	usedMemory += getSizeOfMemBlock((void*)memf.at(i), nullptr);
        //usedMemory += getSizeOfMemBlock((void*)memf.at(i), 0);
	//}

    //printInt(usedMemory, 0x0F);
    printString("liballoc not supported",0x0F);
    return true;
}

bool pciCheck(string input)
{
    if (input.contains("-a"))
    {
        for (int i = 0; i < 10; i++)
        {
            char device = 0;

            //I am hardcoding the pci bus to zero because on qemu and the ms4144 socket 3 motherboard I have, bios interrupt 1A, BX=0101 reports "last pci bus index" to be zero despite having 3 pci slots
            unsigned int vendor = pciCheckVendor(0, i, &device);

            //now print that garbage to the screen
            printInt(i, 0x0E, true);
            printString(": Vendor: 0x", 0x0F);
            printInt(vendor, 0x0F, true);
            printString("   Device: 0x", 0x0F);
            printInt(device, 0x0F, true);
            consoleNewLine(3);
        }
    }
    else
    {
        //subtract the ascii value by 48. This means as long as the user only enters 0-9 in position index 10, it will work fine
        char checkSlot = (input[10])-48;
        char device = 0;

        //I am hardcoding the pci bus to zero because on qemu and the ms4144 socket 3 motherboard I have, bios interrupt 1A, BX=0101 reports "last pci bus index" to be zero despite having 3 pci slots
        unsigned int vendor = pciCheckVendor(0, checkSlot, &device);

        //now print that garbage to the screen
        printString("Vendor: 0x", 0x0F);
        printInt(vendor, 0x0F, true);

        consoleNewLine(3);
        printString("Device: 0x", 0x0F);
        printInt(device, 0x0F, true);
    }

    return true;

}

bool clearScreenCommand(string input)
{
    clearScreen(3);

    return true;
}

bool colorTest(string input)
{
    for (int i = 0; i < 16; i++)
    {
        consoleNewLine(3);
        printInt(i, 0x0F, true);
        printString(" color", i);
    }
    consoleNewLine(3);
    printString("vga mode: 3h text", 0x0F);
    consoleNewLine(3);
    return true;
}

//substring very obviosuly showcases any problems with memory allocation
bool substringTest(string input)
{
    //a panagram that teaches you a science lesson
    string testString1 = "A quart far of oil mixed with zinc oxide makes a very bright paint";
    string testString2 = testString1.substr(0, testString1.length() - 4);

    printString(testString2, 0x04);
    consoleNewLine(3);

    printString("paint jars.substr(0,6)=", 0x0F);
    string aTest = "paint jars";
    //printString("k", 0x0F);
    printString(aTest.substr(0, 6), 0x0F);
    printString(aTest, 0x0F);
    consoleNewLine(3);
    return true;
}

bool printCpuInfo()
{
    consoleNewLine(3);
    printString("cpuid=", 0x0D);

    int result = cpu_ident();
    printInt(result, 0x0F, true);
    consoleNewLine(3);
    printString("model=",0x0D);
    int model = (result >> 4) & 0xF;
    printInt(model, 0x0F, true);
    consoleNewLine(3);

    printString("family=",0x0D);
    int family = (result >> 8) & 0xF;
    printInt(family, 0x0F, true);
    consoleNewLine(3);

    printString("type=",0x0D);
    int type = (result >> 12) & 0x3;
    printInt(type, 0x0F, true);
    consoleNewLine(3);

    //printInt(getCpuVendor(), 0x0F, true);
    printString(cpuModelToString(getCpuVendor(), model, family), 0x0F);

    consoleNewLine(3);

    /*printString("extended model=",0x0D);
    int exmodel = (result >> 16) & 0xF;
    printInt(exmodel, 0x0F, true);
    consoleNewLine(3);

    printString("extended family=",0x0D);
    int exfamily = (result >> 20) & 0xFF;
    printInt(exfamily, 0x0F, true);*/
    return true;
}

bool debugCommand1(string input)
{
    printString("this is a debug command", 0x0D);
    consoleNewLine(3);
    vga_editPaletteReg(0, blue);
    return true;
}

bool debugCommand2(string input)
{
    printString("this is a debug command", 0x0C);
    consoleNewLine(3);
    vga_editPaletteReg(0, black);
    return true;
}

bool debugCommand3(string input)
{
    /*printString("this is a debug command", 0x0B);
    printInt(getvgamode(), 0x0E, true);
    int x;
    int y;
    resOfVGAMode(&x, &y);
    printInt(x, 0x0F, false);
    printChar('x', 0x0F);
    printInt(y, 0x0F, false);*/
    //commenting this out for string debugging
    
    //print newline for the string shenanigans
    /*consoleNewLine(3);
    printString("creating a string named var1 = '-123';", 0x0F);
    string var1 = "-123";
    breakpointHack();
    printString(var1, 0x0D);
    consoleNewLine(3);
    printString(var1, 0x0D);
    printString(var1.substr(0, 2), 0x0D);
    printString(var1, 0x0D);
    breakpointHack();
    printString("..", 0x0D);
    breakpointHack();
    printString(var1, 0x0E);
    breakpointHack();*/


    /*consoleNewLine();
    unsigned int test = (unsigned int)malloc(100);
    printInt(test, 0x0F);
    consoleNewLine();
    printInt(currentSize, 0x0F);
    consoleNewLine();
    printInt((unsigned int)malloc(100), 0x0F);
    consoleNewLine();
    printInt(currentSize, 0x0F);
    consoleNewLine();
    printInt(getMaxSizeMMT()/sizeof(memData), 0x0F);*/
    unsigned int *data = (unsigned int*)malloc(3000);
    for (int p = 0; p < 3000; p++)
    {
        data[p] = betterRand(p + 3);
    }

    consoleNewLine();
    for (int u = 0; u < 500; u++)
    {
        for (int i = 0; i < 6; i++)
        {
            printInt(data[u+(u*i)], 0x0F, false);
        }
        consoleNewLine();
    }

    //huh, most of the cpu time is spent printing the ints, not calculating the numbers
    free(data);

    return true;
}

//create a memory leak of the specified size. Allocates memory but doesn't free. Potentially useful for debugging
bool memLeak(int size=1)
{
    //alloca(size, 1);
}

bool memoryInfo(string input)
{
    printMemoryManagement();
    return true;
}

bool stringSplitTest(string input)
{
    string testString = "ha ad je";
    rarray<string> dammit = rarray<string>();
    split(testString, ' ', &dammit);    //changing it all to * instead of & didn't make the bug go away
    
    for (int i = 0; i < dammit.getSize(); i++)
    {
        printString(dammit.at(i), 0x0F);
        consoleNewLine(3);
    }

    //delete all the strings to avoid memory leaks. I can't figure out how to make it automatically do that in the rarray deletion functions although in theory it *should* be possible
    for(int i = 0; i < dammit.getSize(); i++)
    {
        dammit.at(i).~string(); //fucking finally, fixed the memory leak created in the aftermath of fixing The C++ Bug
    }
    dammit.clear();

    /*asmOutb('\n', 0xE9);
    intToE9((unsigned int)poop, false);
    asmOutb('\n', 0xE9);

    if (!allocationExists(poop))
    {
        asmOutb('e', 0xE9);
        asmOutb('r', 0xE9);
        asmOutb('r', 0xE9);
        asmOutb('o', 0xE9);
        asmOutb('r', 0xE9);
    }
    asmOutb('y', 0xE9);
    asmOutb('a', 0xE9);
    asmOutb('y', 0xE9);*/

    //printInt(poop.getSize(), 0x0F, false);
    printMemInfo(true);
    return true;
}

bool md5Test(string input)
{
    //cool, c_str works as intended
    //string poop = "poop";
    //printCharArray(poop.c_str(), 0x0F, 160);
    consoleNewLine();
    string yeah = "You entered: ";
    yeah += input;
    printString(yeah, 0x0F);

    MD5 testmd5;
    testmd5.update(input.c_str(), input.length());
    testmd5.finalize();

    consoleNewLine();
    printString("The encrypted hash is: ", 0x0F);
    printString(testmd5.hexdigest(), 0x0F);
    return true;
}

//aight, I need a basic hex reader now
bool readCommand(string input)
{
    //get the user input address
    consoleNewLine();
    printString("input string length is ", 0x0F);
    printInt(input.length(), 0x0F);
    consoleNewLine();
    unsigned int bullshit = 0;  //does nothing but required for compatibility with gnu programs
    int num = stoi(input, &bullshit, 16);
    printInt(num, 0x0F, false);

    //now that the input address string has been parsed and converted, draw the top rows for the hex reader screen
    consoleNewLine();

    //recently moved to readMemoryHex(int) in utilities.h
    readMemoryHex(num);
    return true;
}

bool atatestCommand(string input)
{
    consoleNewLine();
    if (input.length() < 9)
    {
        printString("Error. You have to enter a number as a parameter.", 0x0F);
        return false;
    }
    int LBA = stoi(input.substr(8, input.length()));        //convert user input to a number
    printString("The LBA address you entered is: ", 0x0F);
    printInt(LBA, 0x0F);
    consoleNewLine();
    //printString("Getting ready to print LBA address 1 from ata device 0..", 0x0D);
    char *array = ata_lba_read(LBA, MBR_DRIVE_MODE);
    readMemoryHex((int)array, 16);      //32 rows to show 512 bytes
    /*for (int i = 0; i < 512; i++)
    {
        // printChar(array[i], 0x0F);
        char high = intToHexChar((array[i] & 0xF0)>>4);
        char low = intToHexChar(array[i] & 0x0F);
        //printInt(array[i], 0x0F, true);
        printChar(high, 0x0F);
        printChar(low, 0x0F);
        printChar(' ', 0x0F);
    }*/

    // no memory leaks / if the system doesn't crash when this happens, that means its extremely stable
    free(array);

    //printString("..Done", 0x0D);
    //consoleNewLine();

    return true;
}

bool mbrInfoCommand(string input)
{   //mbrinfo 1
    int partitionNumber = 0;
    if (input.length() > 8)
    {
        if(input.at(8) > 47 && input.at(8) < 58)
        {
            partitionNumber = input.at(8) - 48;
        }
    }
    consoleNewLine();
    printString("Selected partition number = ", 0x0F);
    printInt(partitionNumber, 0x0F);
    consoleNewLine();
    //char *partitionEntry = getMbrPartition(partitionNumber, MBR_DRIVE_MODE);

    filesystemInfo what = partitionInformationMBR(MBR_DRIVE_MODE, partitionNumber);
    printString("status byte: 0x", 0x0F);
    print8BitHexInt(what.partitionType);

    /*consoleNewLine();
    printString("head: 0x", 0x0F);
    print8BitHexInt((char)partitionEntry[1]);
    consoleNewLine();
    printString("sector/cyl: 0x", 0x0F);
    print8BitHexInt((char)partitionEntry[2]);
    consoleNewLine();
    printString("cylinder: 0x", 0x0F);
    print8BitHexInt((char)partitionEntry[3]);*/
    consoleNewLine();
    printString("partition type: 0x", 0x0F);
    print8BitHexInt(what.partitionType);

    //do checks of known filesystem types
    if (what.partitionType == 0x06)
    {
        printString("  FAT16, ms-dos bootable", 0x0F);
    }
    else if(what.partitionType == 0x0B)
    {
        printString("  FAT32 with CHS addressing", 0x0F);
    }
    else if(what.partitionType == 0x0C)
    {
        printString("  FAT32 with LBA addressing", 0x0F);
    }

    consoleNewLine();
    printString("Number of sectors in partition: ",0x0F);
    /*print8BitHexInt((char)partitionEntry[0x0F]);
    print8BitHexInt((char)partitionEntry[0x0E]);
    print8BitHexInt((char)partitionEntry[0x0D]);
    print8BitHexInt((char)partitionEntry[0x0C]);*/
    printInt(what.numSectors, 0x0F, true);

    consoleNewLine();
    printString("LBA of first absolute sector in the partition: 0x", 0x0F);
    //unsigned int theNumber = *(unsigned int*)(partitionEntry+8);        //huh, it doesn't work if I do partitionEntry[8] instead. Weird.
    printInt(what.startingLBA, 0x0F, true);

    //char *result = ata_lba_read(what.startingLBA, MBR_DRIVE_MODE);
    
    consoleNewLine();
    //readMemoryHex((int)result, 8);

    //print some information about the partition
    consoleNewLine();
    //short bytesPerSector = *(short*)(result+0x0B);
    //char sectorsPerCluster = *(char*)(result+0x0D);
    //short reservedSectors = *(short*)(result+0x0E);
    printString("Bytes per sector: ", 0x0F);
    printInt(what.bytesPerSector, 0x0F);
    printString("    Sectors per cluster: ", 0x0F);
    printInt(what.sectorsPerCluster, 0x0F);

    //print some more information about the partition
    consoleNewLine();
    printString("Sectors per FAT: ", 0x0F);
    printInt(what.sectorsPerFat, 0x0F);
    printString("    Num reserved sectors: ", 0x0F);
    printInt(what.reservedSectors, 0x0F, false);
    //unsigned int sectorsPerFat = *(unsigned int*)(result+0x24);//was0x24
    //short fsInfoSector = *(short*)(result+0x30);
    //unsigned int serialNumber = *(unsigned int*)(result+0x43);
    
    if (what.partitionType == 0x0B || what.partitionType == 0x0C)
    {
        //this stuff is only valid on fat32
        printString("    FS Info location: ", 0x0F);
        printInt(what.fsInfoSectorLocation, 0x0F), true;

        consoleNewLine();
        printString("Volume serial number: ", 0x0F);
        printInt(what.volumeSerialNumber, 0x0F, true);
    }
    consoleNewLine();
    printString("Number of FATs: ", 0x0F);
    printInt(what.numFats, 0x0F);

    //the same information required to calculate this stuff SHOULD be present in both FAT16 and FAT32
    consoleNewLine();
    unsigned int data = what.startingLBA + (what.reservedSectors) + (what.sectorsPerFat * 2);
    printString("The LBA address of the first file is likely: 0x", 0x0F);
    printInt(data, 0x0F, true);

    //free(partitionEntry);       //no memory leaks. done with mbr partition entry by this point
    //free(result);

    //unsigned int
    //printString("The files should be at: ", 0x0F);
    /*consoleNewLine();
    char *fileData = ata_lba_read(data, MBR_DRIVE_MODE);
    consoleNewLine();
    printAllFiles(data, MBR_DRIVE_MODE, what);
    free(fileData);*/
    /*readMemoryHex((int)fileData,4);*/


    return true;
}

bool mbrInfoSetCommand(string input)
{
    consoleNewLine();
    if (input.at(1) == '1')
    {
        MBR_DRIVE_MODE = 1;
        printString("ata drive set to 1", 0x0F);

    }
    else if (input.at(1) == '0')
    {
        MBR_DRIVE_MODE = 0;
        printString("ata drive set to 0", 0x0F);
    }
    else
    {
        printString("Whatever you typed in was invalid but the selected drive is currently set to: ", 0x0F);
        printInt(MBR_DRIVE_MODE, 0x0F);
    }
    return true;
}

void printAllFiles(unsigned int LBA, unsigned int driveNum, filesystemInfo *sys)
{
    //32 bytes per file I think
    /*char *theSector = ata_lba_read(LBA, driveNum);

    for (int i = 0; i < 16; i++)
    {
        if (printFile((char*)(theSector + (i * 32))))
        {
            consoleNewLine();
        }
    }*/

    rarray<fileInfo> *files = getFilesInDirectory(LBA, driveNum, sys);
    printFileList(files, sys);

    //we have to erase each string before clearing the rarray because strings contain char arrays
    for (int i = 0; i < files->getSize(); i++)
    {
        files->at(i).~fileInfo();
    }

    //now do all the other auxillary memory leak prevention stuff
    files->manual_delete();
    free(files);

    //there, no memory leaks
}

bool printFile(char *input)
{
    if (input[0] < 34)
    {
        return false;
    }

    for (int i = 0; i < 8; i++)
    {
        if (input[i] > 32)
        {
            printChar(input[i], 0x0F);
        }
    }

    char attrib = input[0x0B];
    if ((attrib & 0x10)==1)
    {
        //don't print the file extension if it's a directory
    }
    else if ((attrib & 0xD2)==0)
    {
        printChar('.', 0x0F);
        printChar(input[8], 0x0F);
        printChar(input[9], 0x0F);
        printChar(input[10], 0x0F);
    }

    //0x14 = high two bytes of cluster location in FAT32
    //0x1A = low two bytes of cluster location in FAT32 and FAT16

    return true;
}

bool lsCommand(string input)
{
    if (selectedVolume.mounted)
    {
        consoleNewLine();
        //print entire directory for the user to see
        //printAllFiles(rootLBA(selectedVolume.fsinfo), MBR_DRIVE_MODE, selectedVolume.fsinfo);
        printAllFiles(selectedVolume.currentDirectoryLBA, MBR_DRIVE_MODE, &selectedVolume.fsinfo);
    }
    else
    {
        printString("Error. Drive not mounted.", 0x0F);
    }
    return true;
}

bool cdCommand(string input)
{
    if (selectedVolume.mounted)
    {
        printString("step1", 0x0F);
        fileInfo foundFile = getFileByName(selectedVolume.currentDirectoryLBA, MBR_DRIVE_MODE, &selectedVolume.fsinfo, input);
        printString("step2", 0x0F);
        if (foundFile.isValidFile && foundFile.isDirectory)
        {
            printString("Found file has an LBA address of ", 0x0F);
            selectedVolume.currentDirectoryLBA = LBAofFile(&foundFile, &selectedVolume.fsinfo);
            printInt(selectedVolume.currentDirectoryLBA, 0x0F, true);   //update the parent directory LBA pointer
        }
        else if (foundFile.isValidFile)
        {
            //prevent the user from messing up the entire system. cd into files is disallowed
            printString("You can't cd into a file, it has to be a directory.",0x0F);
        }
        else
        {
            printString("Directory named '", 0x0F);
            printString(input, 0x0F);
            printString("' not found", 0x0F);
        }
        return true;
    }
    else
    {
        printString("Error. Drive not mounted.", 0x0F);
        return true;
    }
    return true;
}

bool mountCommand(unsigned int partitionNumber)
{
    //information about the partition we want to mount
    //dataVolumeInfo dsInfo;
    
    //first, generate a filesystem info
    selectedVolume.fsinfo = partitionInformationMBR(MBR_DRIVE_MODE, partitionNumber);

    consoleNewLine();
    printString("partition number ", 0x0F);
    printInt(partitionNumber, 0x0F);
    printString(" on drive #", 0x0F);
    printInt(MBR_DRIVE_MODE, 0x0F);
    consoleNewLine();

    selectedVolume.mounted = true;
    selectedVolume.currentDirectoryLBA = rootLBA(&selectedVolume.fsinfo);        //since this is a newly mounted volume, reset the folder location LBA to the root directory

    return true;
}

bool fileSizeCommand(string input)
{
    consoleNewLine();       //get this part out of the way since I have to do it sooner or later

    fileInfo foundFile = getFileByName(selectedVolume.currentDirectoryLBA, MBR_DRIVE_MODE, &selectedVolume.fsinfo, input);
    if (foundFile.isValidFile)
    {
        //directories don't have valid data in their filesize offset
        if (!foundFile.isDirectory)
        {
            printString("Size: ", 0x0F);
            printInt(foundFile.size, 0x0F);
        }
        printString(". Size on filesystem: ",0x0F);
        printInt(sizeOfFile(&foundFile, &selectedVolume.fsinfo, MBR_DRIVE_MODE), 0x0F);

        /*consoleNewLine();
        printString("fats: ", 0x0F);
        rarray<unsigned int> *blocks = fileClusters(foundFile, selectedVolume.fsinfo, MBR_DRIVE_MODE);
        for (int i = 0; i < blocks->getSize(); i++)
        {
            consoleNewLine();
            printInt(blocks->at(i), 0x0F, true);
        }
        consoleNewLine();
        printInt(blocks->getSize(), 0x0F);
        printString(" blocks.", 0x0F);
        //now do all the other auxillary memory leak prevention stuff
        blocks->manual_delete();
        //free(blocks);
        */



    }
    else
    {
        printString("Not found", 0x0F);
    }
    foundFile.~fileInfo();//delete the file dynamic memory

    return true;
}

bool fatLoadCommand(string input)
{
    //printString(input, 0x0E);
    consoleNewLine();
    fileInfo foundFile = getFileByName(selectedVolume.currentDirectoryLBA, MBR_DRIVE_MODE, &selectedVolume.fsinfo, input);
    if (foundFile.isValidFile)
    {
        /*//get a list of clusters that the file takes up
        rarray<unsigned int> *blocks = fileClusters(&foundFile, &selectedVolume.fsinfo, MBR_DRIVE_MODE);

        //allocate a spot in memory to store the file
        char *fileStore = (char *)malloc(sizeOfFile(&foundFile, &selectedVolume.fsinfo, MBR_DRIVE_MODE));
        unsigned int debugInt = 0;
        for (int i = 0; i < blocks->getSize(); i++)
        {
            char poop[3];
            *(unsigned int*)poop = blocks->at(i);
            if (!isExitCodeFAT(poop, &selectedVolume.fsinfo))
            {
                for (int s = 0; s < selectedVolume.fsinfo.sectorsPerCluster; s++)
                {
                    unsigned int lbaOfFileCluster = ((blocks->at(i)-2) * selectedVolume.fsinfo.sectorsPerCluster) + rootLBA(&selectedVolume.fsinfo) + s;
                    //lbaOfFileCluster-=2;     //you need to do this for some reason. I'm sure FAT16 will need other special handling but I already had to give up on FAT16 in fileClusters
                    //*(char*)(fileStore+(i*512)) = ata_lba_read(lbaOfFileCluster, MBR_DRIVE_MODE);
                    char *bytes = ata_lba_read(lbaOfFileCluster, MBR_DRIVE_MODE);
                    memcpy((fileStore+(((i*selectedVolume.fsinfo.sectorsPerCluster)+s) * 512)), (bytes), 512);        //memcpy is the most optimized memory copy right now
                    debugInt++;
                    free(bytes); // don't need this anymore
                }
            }
        }
        consoleNewLine();
        printInt(debugInt, 0x0F);
        consoleNewLine();

        //print the raw contents to the screen
        //consoleNewLine();
        unsigned int count = 0;
        while (count < foundFile.size)
        {
            readMemoryHex((unsigned int)fileStore + count);
            consoleNewLine();
            //printString("Press any key to view the next 256 bytes. You are on byte ",0x0F);
            printInt(count, 0x0F);
            consoleNewLine();
            //waitChar();
            count += 256;
        }

        //before any freeing happens, display how much memory is in use
        printMemoryManagement();

        free(fileStore);    //avoid memory leak
        //if forgetting to free this doesn't cause major memory leaks then something is really wrong
        
        blocks->manual_delete();
        free(blocks);*/
        void *storedFile = loadFile(&foundFile, MBR_DRIVE_MODE, &selectedVolume.fsinfo);
        printMemoryManagement();
        free(storedFile);    //avoid memory leak
    }
    else
    {
        printString("Not found", 0x0F);
    }

    foundFile.~fileInfo();//delete the file dynamic memory

    return true;
}

//boot a binary file in protected mode. Most binary files need to be booted in real mode.
//the only purpose of this function is to boot a c++ os binary, since the bootloader and system have to be seperate
bool boot32(string input)
{
    consoleNewLine();
    printString("Loading file: ", 0x0F);
    printString(input, 0x0F);
    fileInfo systemFile = getFileByName(selectedVolume.currentDirectoryLBA, MBR_DRIVE_MODE, &selectedVolume.fsinfo, input);
    consoleNewLine();
    printString("File found. Loading...", 0x0F);
    void* systemData = loadFile(&systemFile, MBR_DRIVE_MODE, &selectedVolume.fsinfo);
    consoleNewLine();
    printString("File loaded. Copying to boot position..",0x0F);
    memcpy((void*)0x100000, systemData, systemFile.size);
    consoleNewLine();
    printString("Copied. Jumping to 0x100000...",0x0F);
    //waitChar();
    bootFromHighMem();      //ta-ta
    return true;
}