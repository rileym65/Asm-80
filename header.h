#ifndef _HEADER_H
#define _HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef MAIN
#define LINK
#else
#define LINK extern
#endif

typedef unsigned char byte;
typedef unsigned short word;

LINK byte    a1,a2;
LINK word    address;
LINK char    arg1[256];
LINK char    arg2[256];
LINK char    baseName[1024];
LINK byte    c1,c2;
LINK int     codeGenerated;
LINK int     createListFile;
LINK char  **defines;
LINK char  **defineValues;
LINK int     errors;
LINK int     evalErrors;
LINK int    *externals;
LINK int     fileNumber;
LINK word    fixups[10000];
LINK char    fixupTypes[10000];
LINK byte    fixupLowOffset[10000];
LINK word    i1,i2;
LINK int     inProc;
LINK int     instructionBytes;
LINK char    label[256];
LINK int    *labelLine;
LINK char  **labelNames;
LINK char  **labelProcs;
LINK word   *labelValues;
LINK int     lineCount;
LINK int     lineNumber[100];
LINK FILE   *listFile;
LINK char    listLine[1024];
LINK char    listName[1024];
LINK char    module[256];
LINK char    nests[100];
LINK int     noReloc;
LINK int     numDefines;
LINK int     numExternals;
LINK int     numFixups;
LINK int     numLabels;
LINK int     numNests;
LINK int     numOpcodes;
LINK int     numPublics;
LINK int     numSourceFiles;
LINK char    opcode[256];
LINK char    opcodes[256][3][10];
LINK word    outAddress;
LINK byte    outBytes[16];
LINK int     outCount;
LINK FILE   *outFile;
LINK char    outName[1024];
LINK int     pass;
LINK int    *publics;
LINK int     showList;
LINK int     showSymbols;
LINK FILE   *sourceFile[100];
LINK char    sourceLine[1024];
LINK char  **sourceNames;
LINK word    startAddress;
LINK char    translations[256][40];
LINK int     usedExternal;
LINK int     usedLocal;


#endif

