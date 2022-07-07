#define MAIN

#include "header.h"

#define OP_STOP     0xff
#define OP_DIV      0x71
#define OP_MUL      0x70
#define OP_SUB      0x61
#define OP_ADD      0x60
#define OP_SHR      0x51
#define OP_SHL      0x50
#define OP_LT       0x45
#define OP_LE       0x44
#define OP_GT       0x43
#define OP_GE       0x42
#define OP_NE       0x41
#define OP_EQ       0x40
#define OP_XOR      0x32
#define OP_OR       0x31
#define OP_AND      0x30
#define OP_LAND     0x20
#define OP_LOR      0x10
#define OP_OP       0x09
#define OP_CP       0x08
#define OP_END      0x01

typedef union {
  float f;
  unsigned int i;
  } FTOI;

void addOpcode(char* op, char* arg1, char* arg2, char* trans) {
  strcpy(opcodes[numOpcodes][0], op);
  strcpy(opcodes[numOpcodes][1], arg1);
  strcpy(opcodes[numOpcodes][2], arg2);
  strcpy(translations[numOpcodes], trans);
  numOpcodes++;
  }

void initOpcodes() {
  numOpcodes = 0;
  addOpcode("ADC",    "A",        "[r]",      "x=2 y=1 z=[2]");
  addOpcode("ADC",    "A",        "[nn]",     "x=3 y=1 z=6");
  addOpcode("ADD",    "A",        "[r]",      "x=2 y=0 z=[2]");
  addOpcode("ADD",    "A",        "[nn]",     "x=3 y=0 z=6");
  addOpcode("ADD",    "HL",       "[pp]",     "x=0 p=[2] q=1 z=1");
  addOpcode("AND",    "[r]",      "",         "x=2 y=4 z=[1]");
  addOpcode("AND",    "[nn]",     "",         "x=3 y=4 z=6");
  addOpcode("CALL",   "[nnnn]",   "",         "x=3 y=1 z=5");
  addOpcode("CALL",   "[cc]",     "[nnnn]",   "x=3 y=[1] z=4");
  addOpcode("CCF",    "",         "",         "x=0 y=7 z=7");
  addOpcode("CP",     "[r]",      "",         "x=2 y=7 z=[1]");
  addOpcode("CP",     "[nn]",     "",         "x=3 y=7 z=6");
  addOpcode("CPL",    "",         "",         "x=0 y=5 z=7");
  addOpcode("DAA",    "",         "",         "x=0 y=4 z=7");
  addOpcode("DEC",    "[pp]",     "",         "x=0 p=[1] q=1 z=3");
  addOpcode("DEC",    "[r]",      "",         "x=0 y=[1] z=5");
  addOpcode("DI",     "",         "",         "x=3 y=6 z=3");
  addOpcode("DJNZ",   "[d]",      "",         "x=0 y=2 z=0");
  addOpcode("EI",     "",         "",         "x=3 y=7 z=3");
  addOpcode("EX",     "AF",       "AF'",      "x=0 y=1 z=0");
  addOpcode("EX",     "DE",       "HL",       "x=3 y=5 z=3");
  addOpcode("EX",     "(SP)",     "HL",       "x=3 y=4 z=3");
  addOpcode("EXX",    "",         "",         "x=3 p=1 q=1 z=1");
  addOpcode("HALT",   "",         "",         "x=1 y=6 z=6");
  addOpcode("IN",     "A",        "([nn])",   "x=3 y=3 z=3");
  addOpcode("INC",    "[pp]",     "",         "x=0 p=[1] q=0 z=3");
  addOpcode("INC",    "[r]",      "",         "x=0 y=[1] z=4");
  addOpcode("JP",     "(HL)",     "",         "x=3 p=2 q=1 z=1");
  addOpcode("JP",     "[nnnn]",   "",         "x=3 y=0 z=3");
  addOpcode("JP",     "[cc]",     "[nnnn]",   "x=3 y=[1] z=2");
  addOpcode("JR",     "[d]",      "",         "x=0 y=3 z=0");
  addOpcode("JR",     "C",        "[d]",      "x=0 y=7 z=0");
  addOpcode("JR",     "NC",       "[d]",      "x=0 y=6 z=0");
  addOpcode("JR",     "NZ",       "[d]",      "x=0 y=4 z=0");
  addOpcode("JR",     "Z",        "[d]",      "x=0 y=5 z=0");
  addOpcode("LD",     "(BC)",     "A",        "x=0 p=0 q=0 z=2");
  addOpcode("LD",     "(DE)",     "A",        "x=0 p=1 q=0 z=2");
  addOpcode("LD",     "([nnnn])", "HL",       "x=0 p=2 q=0 z=2");
  addOpcode("LD",     "([nnnn])", "A",        "x=0 p=3 q=0 z=2");
  addOpcode("LD",     "A",        "(BC)",     "x=0 p=0 q=1 z=2");
  addOpcode("LD",     "A",        "(DE)",     "x=0 p=1 q=1 z=2");
  addOpcode("LD",     "HL",       "([nnnn])", "x=0 p=2 q=1 z=2");
  addOpcode("LD",     "SP",       "HL",       "x=3 p=3 q=1 z=1");
  addOpcode("LD",     "A",        "([nnnn])", "x=0 p=3 q=1 z=2");
  addOpcode("LD",     "[pp]",     "[nnnn]",   "x=0 p=[1] q=0 z=1");
  addOpcode("LD",     "[r]",      "[nn]",     "x=0 y=[1] z=6");
  addOpcode("LD",     "[r]",      "[r]",      "x=1 y=[1] z=[2]");
  addOpcode("NOP",    "",         "",         "x=0 y=0 z=0");
  addOpcode("OR",     "[r]",      "",         "x=2 y=6 z=[1]");
  addOpcode("OR",     "[nn]",     "",         "x=3 y=6 z=6");
  addOpcode("OUT",    "([nn])",   "A",        "x=3 y=2 z=3");
  addOpcode("POP",    "[qq]",     "",         "x=3 p=[1] q=0 z=1");
  addOpcode("PUSH",   "[qq]",     "",         "x=3 p=[1] q=0 z=5");
  addOpcode("RET",    "",         "",         "x=3 p=0 q=1 z=1");
  addOpcode("RET",    "[cc]",     "",         "x=3 y=[1] z=0");
  addOpcode("RLA",    "",         "",         "x=0 y=2 z=7");
  addOpcode("RLCA",   "",         "",         "x=0 y=0 z=7");
  addOpcode("RRA",    "",         "",         "x=0 y=3 z=7");
  addOpcode("RRCA",   "",         "",         "x=0 y=1 z=7");
  addOpcode("RST",    "[rst]",    "",         "x=3 y=[1] z=7");
  addOpcode("SBC",    "A",        "[r]",      "x=2 y=3 z=[2]");
  addOpcode("SBC",    "A",        "[nn]",     "x=3 y=3 z=6");
  addOpcode("SCF",    "",         "",         "x=0 y=6 z=7");
  addOpcode("SUB",    "A",        "[r]",      "x=2 y=2 z=[2]");
  addOpcode("SUB",    "A",        "[nn]",     "x=3 y=2 z=6");
  addOpcode("XOR",    "[r]",      "",         "x=2 y=5 z=[1]");
  addOpcode("XOR",    "[nn]",     "",         "x=3 y=5 z=6");

  addOpcode("BIT",    "[bit]",    "[r]",      "CB x=1 y=[1] z=[2]");
  addOpcode("RL",     "[r]",      "",         "CB x=0 y=2 z=[1]");
  addOpcode("RLC",    "[r]",      "",         "CB x=0 y=0 z=[1]");
  addOpcode("RES",    "[bit]",    "[r]",      "CB x=2 y=[1] z=[2]");
  addOpcode("RR",     "[r]",      "",         "CB x=0 y=3 z=[1]");
  addOpcode("RRC",    "[r]",      "",         "CB x=0 y=1 z=[1]");
  addOpcode("SET",    "[bit]",    "[r]",      "CB x=3 y=[1] z=[2]");
  addOpcode("SLA",    "[r]",      "",         "CB x=0 y=4 z=[1]");
  addOpcode("SLL",    "[r]",      "",         "CB x=0 y=6 z=[1]");
  addOpcode("SRA",    "[r]",      "",         "CB x=0 y=5 z=[1]");
  addOpcode("SRL",    "[r]",      "",         "CB x=0 y=7 z=[1]");

  addOpcode("ADC",    "HL",       "[pp]",     "ED x=1 p=[2] q=1 z=2");
  addOpcode("IM",     "0",        "",         "ED x=1 y=0 z=6");
  addOpcode("IM",     "1",        "",         "ED x=1 y=2 z=6");
  addOpcode("IM",     "2",        "",         "ED x=1 y=3 z=6");
  addOpcode("IN",     "[r]",      "(C)",      "ED x=1 y=[1] z=0");
  addOpcode("IN",     "(C)",      "",         "ED x=1 y=6 z=0");
  addOpcode("LD",     "A",        "I",        "ED x=1 y=2 z=7");
  addOpcode("LD",     "A",        "R",        "ED x=1 y=3 z=7");
  addOpcode("LD",     "I",        "A",        "ED x=1 y=0 z=7");
  addOpcode("LD",     "R",        "A",        "ED x=1 y=1 z=7");
  addOpcode("LD",     "([nnnn])", "[pp]",     "ED x=1 p=[2] q=0 z=3");
  addOpcode("LD",     "[pp]",     "([nnnn])", "ED x=1 p=[1] q=1 z=3");
  addOpcode("NEG",    "",         "",         "ED x=1 y=0 z=4");
  addOpcode("OUT",    "(C)",      "[r]",      "ED x=1 y=[2] z=1");
  addOpcode("OUT",    "(C)",      "",         "ED x=1 y=6 z=1");
  addOpcode("RLD",    "",         "",         "ED x=1 y=5 z=7");
  addOpcode("RRD",    "",         "",         "ED x=1 y=4 z=7");
  addOpcode("RETI",   "",         "",         "ED x=1 y=1 z=5");
  addOpcode("RETN",   "",         "",         "ED x=1 y=0 z=5");
  addOpcode("SBC",    "HL",       "[pp]",     "ED x=1 p=[2] q=0 z=2");
  addOpcode("LDI",    "",         "",         "ED x=2 y=4 z=0");
  addOpcode("LDD",    "",         "",         "ED x=2 y=5 z=0");
  addOpcode("LDIR",   "",         "",         "ED x=2 y=6 z=0");
  addOpcode("LDDR",   "",         "",         "ED x=2 y=7 z=0");
  addOpcode("CPI",    "",         "",         "ED x=2 y=4 z=1");
  addOpcode("CPD",    "",         "",         "ED x=2 y=5 z=1");
  addOpcode("CPIR",   "",         "",         "ED x=2 y=6 z=1");
  addOpcode("CPDR",   "",         "",         "ED x=2 y=7 z=1");
  addOpcode("INI",    "",         "",         "ED x=2 y=4 z=2");
  addOpcode("IND",    "",         "",         "ED x=2 y=5 z=2");
  addOpcode("INIR",   "",         "",         "ED x=2 y=6 z=2");
  addOpcode("INDR",   "",         "",         "ED x=2 y=7 z=2");
  addOpcode("OUTI",   "",         "",         "ED x=2 y=4 z=3");
  addOpcode("OUTD",   "",         "",         "ED x=2 y=5 z=3");
  addOpcode("OTIR",   "",         "",         "ED x=2 y=6 z=3");
  addOpcode("OTDR",   "",         "",         "ED x=2 y=7 z=3");

  addOpcode("ADC",    "A",        "IXH",      "DD x=2 y=1 z=4");
  addOpcode("ADC",    "A",        "IXL",      "DD x=2 y=1 z=5");
  addOpcode("ADC",    "A",        "(IX",      "DD x=2 y=1 z=6");
  addOpcode("ADD",    "A",        "IXH",      "DD x=2 y=0 z=4");
  addOpcode("ADD",    "A",        "IXL",      "DD x=2 y=0 z=5");
  addOpcode("ADD",    "A",        "(IX",      "DD x=2 y=0 z=6");
  addOpcode("ADD",    "IX",       "[ix]",     "DD x=0 p=[2] q=1 z=1");
  addOpcode("AND",    "IXH",      "",         "DD x=2 y=4 z=4");
  addOpcode("AND",    "IXL",      "",         "DD x=2 y=4 z=5");
  addOpcode("AND",    "(IX",      "",         "DD x=2 y=4 z=6");
  addOpcode("CP",     "IXH",      "",         "DD x=2 y=7 z=4");
  addOpcode("CP",     "IXL",      "",         "DD x=2 y=7 z=5");
  addOpcode("CP",     "(IX",      "",         "DD x=2 y=7 z=6");
  addOpcode("DEC",    "IX",       "",         "DD x=0 y=5 z=3");
  addOpcode("DEC",    "IXH",      "",         "DD x=0 y=4 z=5");
  addOpcode("DEC",    "IXL",      "",         "DD x=0 y=5 z=5");
  addOpcode("DEC",    "(IX",      "",         "DD x=0 y=6 z=5");
  addOpcode("EX",     "(SP)",     "IX",       "DD x=3 y=4 z=3");
  addOpcode("INC",    "IX",       "",         "DD x=0 y=4 z=3");
  addOpcode("INC",    "IXH",      "",         "DD x=0 y=4 z=4");
  addOpcode("INC",    "IXL",      "",         "DD x=0 y=5 z=4");
  addOpcode("INC",    "(IX",      "",         "DD x=0 y=6 z=4");
  addOpcode("JP",     "(IX)",     "",         "DD x=3 y=5 z=1");
  addOpcode("LD",     "IXH",      "[nn]",     "DD x=0 y=4 z=6");
  addOpcode("LD",     "IXL",      "[nn]",     "DD x=0 y=5 z=6");
  addOpcode("LD",     "IX",       "[nnnn]",   "DD x=0 y=4 z=1");
  addOpcode("LD",     "IX",       "([nnnn])", "DD x=0 y=5 z=2");
  addOpcode("LD",     "([nnnn])", "IX",       "DD x=0 y=4 z=2");
  addOpcode("LD",     "(IX",      "[nn]",     "DD x=0 y=6 z=6");
  addOpcode("LD",     "[r]",      "IXH",      "DD x=1 y=[1] z=4");
  addOpcode("LD",     "[r]",      "IXL",      "DD x=1 y=[1] z=5");
  addOpcode("LD",     "[r]",      "(IX",      "DD x=1 y=[1] z=6");
  addOpcode("LD",     "IXH",      "[rx]",     "DD x=1 y=4 z=[2]");
  addOpcode("LD",     "IXL",      "[rx]",     "DD x=1 y=5 z=[2]");
  addOpcode("LD",     "(IX",      "[r]",      "DD x=1 y=6 z=[2]");
  addOpcode("LD",     "SP",       "IX",       "DD x=3 y=7 z=1");
  addOpcode("OR",     "IXH",      "",         "DD x=2 y=6 z=4");
  addOpcode("OR",     "IXL",      "",         "DD x=2 y=6 z=5");
  addOpcode("OR",     "(IX",      "",         "DD x=2 y=6 z=6");
  addOpcode("POP",    "IX",       "",         "DD x=3 y=4 z=1");
  addOpcode("PUSH",   "IX",       "",         "DD x=3 y=4 z=5");
  addOpcode("SBC",    "IXH",      "",         "DD x=2 y=3 z=4");
  addOpcode("SBC",    "IXL",      "",         "DD x=2 y=3 z=5");
  addOpcode("SBC",    "A",        "(IX",      "DD x=2 y=3 z=6");
  addOpcode("SUB",    "IXH",      "",         "DD x=2 y=2 z=4");
  addOpcode("SUB",    "IXL",      "",         "DD x=2 y=2 z=5");
  addOpcode("SUB",    "A",        "(IX",      "DD x=2 y=2 z=6");
  addOpcode("XOR",    "IXH",      "",         "DD x=2 y=5 z=4");
  addOpcode("XOR",    "IXL",      "",         "DD x=2 y=5 z=5");
  addOpcode("XOR",    "(IX",      "",         "DD x=2 y=5 z=6");
  addOpcode("BIT",    "[bit]",    "(IX",      "DD CB x=1 y=[1] z=6");
  addOpcode("RES",    "[bit]",    "(IX",      "DD CB x=2 y=[1] z=6");
  addOpcode("RL",     "(IX",      "",         "DD CB x=0 y=2 z=6");
  addOpcode("RLC",    "(IX",      "",         "DD CB x=0 y=0 z=6");
  addOpcode("RR",     "(IX",      "",         "DD CB x=0 y=3 z=6");
  addOpcode("RRC",    "(IX",      "",         "DD CB x=0 y=1 z=6");
  addOpcode("SET",    "[bit]",    "(IX",      "DD CB x=3 y=[1] z=6");
  addOpcode("SLA",    "(IX",      "",         "DD CB x=0 y=4 z=6");
  addOpcode("SLIA",   "(IX",      "",         "DD CB x=0 y=6 z=6");
  addOpcode("SRA",    "(IX",      "",         "DD CB x=0 y=5 z=6");
  addOpcode("SRL",    "(IX",      "",         "DD CB x=0 y=7 z=6");

  addOpcode("ADC",    "A",        "IYH",      "FD x=2 y=1 z=4");
  addOpcode("ADC",    "A",        "IYL",      "FD x=2 y=1 z=5");
  addOpcode("ADC",    "A",        "(IY",      "FD x=2 y=1 z=6");
  addOpcode("ADD",    "A",        "IYH",      "FD x=2 y=0 z=4");
  addOpcode("ADD",    "A",        "IYL",      "FD x=2 y=0 z=5");
  addOpcode("ADD",    "A",        "(IY",      "FD x=2 y=0 z=6");
  addOpcode("ADD",    "IY",       "[iy]",     "FD x=0 p=[2] q=1 z=1");
  addOpcode("AND",    "IYH",      "",         "FD x=2 y=4 z=4");
  addOpcode("AND",    "IYL",      "",         "FD x=2 y=4 z=5");
  addOpcode("AND",    "(IY",      "",         "FD x=2 y=4 z=6");
  addOpcode("CP",     "IYH",      "",         "FD x=2 y=7 z=4");
  addOpcode("CP",     "IYL",      "",         "FD x=2 y=7 z=5");
  addOpcode("CP",     "(IY",      "",         "FD x=2 y=7 z=6");
  addOpcode("DEC",    "IY",       "",         "FD x=0 y=5 z=3");
  addOpcode("DEC",    "IYH",      "",         "FD x=0 y=4 z=5");
  addOpcode("DEC",    "IYL",      "",         "FD x=0 y=5 z=5");
  addOpcode("DEC",    "(IY",      "",         "FD x=0 y=6 z=5");
  addOpcode("EX",     "(SP)",     "IY",       "FD x=3 y=4 z=3");
  addOpcode("INC",    "IY",       "",         "FD x=0 y=4 z=3");
  addOpcode("INC",    "IYH",      "",         "FD x=0 y=4 z=4");
  addOpcode("INC",    "IYL",      "",         "FD x=0 y=5 z=4");
  addOpcode("INC",    "(IY",      "",         "FD x=0 y=6 z=4");
  addOpcode("JP",     "(IY)",     "",         "FD x=3 y=5 z=1");
  addOpcode("LD",     "IYH",      "[nn]",     "FD x=0 y=4 z=6");
  addOpcode("LD",     "IYL",      "[nn]",     "FD x=0 y=5 z=6");
  addOpcode("LD",     "IY",       "[nnnn]",   "FD x=0 y=4 z=1");
  addOpcode("LD",     "IY",       "([nnnn])", "FD x=0 y=5 z=2");
  addOpcode("LD",     "([nnnn])", "IY",       "FD x=0 y=4 z=2");
  addOpcode("LD",     "(IY",      "[nn]",     "FD x=0 y=6 z=6");
  addOpcode("LD",     "[r]",      "IYH",      "FD x=1 y=[1] z=4");
  addOpcode("LD",     "[r]",      "IYL",      "FD x=1 y=[1] z=5");
  addOpcode("LD",     "[r]",      "(IY",      "FD x=1 y=[1] z=6");
  addOpcode("LD",     "IYH",      "[ry]",     "FD x=1 y=4 z=[2]");
  addOpcode("LD",     "IYL",      "[ry]",     "FD x=1 y=5 z=[2]");
  addOpcode("LD",     "(IY",      "[r]",      "FD x=1 y=6 z=[2]");
  addOpcode("LD",     "SP",       "IY",       "FD x=3 y=7 z=1");
  addOpcode("OR",     "IYH",      "",         "FD x=2 y=6 z=4");
  addOpcode("OR",     "IYL",      "",         "FD x=2 y=6 z=5");
  addOpcode("OR",     "(IY",      "",         "FD x=2 y=6 z=6");
  addOpcode("POP",    "IY",       "",         "FD x=3 y=4 z=1");
  addOpcode("PUSH",   "IY",       "",         "FD x=3 y=4 z=5");
  addOpcode("SBC",    "IYH",      "",         "FD x=2 y=3 z=4");
  addOpcode("SBC",    "IYL",      "",         "FD x=2 y=3 z=5");
  addOpcode("SBC",    "A",        "(IY",      "FD x=2 y=3 z=6");
  addOpcode("SUB",    "IYH",      "",         "FD x=2 y=2 z=4");
  addOpcode("SUB",    "IYL",      "",         "FD x=2 y=2 z=5");
  addOpcode("SUB",    "A",        "(IY",      "FD x=2 y=2 z=6");
  addOpcode("XOR",    "IYH",      "",         "FD x=2 y=5 z=4");
  addOpcode("XOR",    "IYL",      "",         "FD x=2 y=5 z=5");
  addOpcode("XOR",    "(IY",      "",         "FD x=2 y=5 z=6");
  addOpcode("BIT",    "[bit]",    "(IY",      "FD CB x=1 y=[1] z=6");
  addOpcode("RES",    "[bit]",    "(IY",      "FD CB x=2 y=[1] z=6");
  addOpcode("RL",     "(IY",      "",         "FD CB x=0 y=2 z=6");
  addOpcode("RLC",    "(IY",      "",         "FD CB x=0 y=0 z=6");
  addOpcode("RR",     "(IY",      "",         "FD CB x=0 y=3 z=6");
  addOpcode("RRC",    "(IY",      "",         "FD CB x=0 y=1 z=6");
  addOpcode("SET",    "[bit]",    "(IY",      "FD CB x=3 y=[1] z=6");
  addOpcode("SLA",    "(IY",      "",         "FD CB x=0 y=4 z=6");
  addOpcode("SLIA",   "(IY",      "",         "FD CB x=0 y=6 z=6");
  addOpcode("SRA",    "(IY",      "",         "FD CB x=0 y=5 z=6");
  addOpcode("SRL",    "(IY",      "",         "FD CB x=0 y=7 z=6");
  printf("%d opcodes loaded\n",numOpcodes);
  }

void writeOutput() {
  int  i;
  char buffer[256];
  char tmp[4];
  if (outCount == 0) return;
  sprintf(buffer,":%04x",outAddress);
  for (i=0; i<outCount; i++) {
    sprintf(tmp," %02x",outBytes[i]);
    strcat(buffer,tmp);
    }
  if (pass == 2) fprintf(outFile,"%s\n",buffer);
  outCount = 0;
  outAddress = address;
  }

void output(byte value) {
  int  i;
  char tmp[4];
  codeGenerated++;
  address++;
  instructionBytes++;
  sprintf(tmp," %02x",value);
  strcat(listLine,tmp);
  if (instructionBytes == 4) {
    strcat(listLine,"  ");
    strcat(listLine, sourceLine);
    }
  if ((instructionBytes % 4) == 0) {
    if (pass == 2) {
      if (showList != 0) printf("%s\n",listLine);
      if (createListFile != 0) fprintf(listFile,"%s\n",listLine);
      }
    strcpy(listLine,"             ");
    }
  if (pass == 2) {
    outBytes[outCount++] = value;
    if (outCount == 16) {
      writeOutput();
      }
    }
  }

int findLabelNumber(char* name) {
  int i;
  int j;
  if (strcmp(module,"*") != 0) {
    for (i=0; i<numLabels; i++) {
      if (strcasecmp(labelNames[i], name) == 0 &&
          strcasecmp(labelProcs[i], module) == 0) {
        return i;
        }
      }
    }
  for (i=0; i<numLabels; i++) {
    if (strcasecmp(labelNames[i], name) == 0 &&
        strcasecmp(labelProcs[i], "*") == 0) {
      return i;
      }
    }
  return -1;
  }

word findLabel(char* name, char* err) {
  int i;
  int j;
  *err = 0;
  if (strcmp(module,"*") != 0) {
    for (i=0; i<numLabels; i++) {
      if (strcasecmp(labelNames[i], name) == 0 &&
          strcasecmp(labelProcs[i], module) == 0) {
        usedLocal = -1;
        for (j=0; j<numExternals; j++)
          if (externals[j] == i) usedExternal = j;
        return labelValues[i];
        }
      }
    }

  for (i=0; i<numLabels; i++) {
    if (strcasecmp(labelNames[i], name) == 0 &&
        strcasecmp(labelProcs[i], "*") == 0) {
      for (j=0; j<numExternals; j++)
        if (externals[j] == i) usedExternal = j;
      return labelValues[i];
      }
    }

  if (pass == 1) return 0;
  *err = 0xff;
  printf("Error: Label not found: %s\n",name);
  errors++;
  return 0;
  }

int addLabel(char* name, word value) {
  int i;
  if (pass == 2) return 0;
  for (i=0; i<numLabels; i++)
    if (strcasecmp(labelNames[i], name) == 0 &&
        strcasecmp(labelProcs[i], module) == 0) {
      printf("Error: Duplicate label: %s\n",name);
      errors++;
      return -1;
      }
  numLabels++;
  if (numLabels == 1) {
    labelNames = (char**)malloc(sizeof(char*));
    labelValues = (word*)malloc(sizeof(word));
    labelProcs = (char**)malloc(sizeof(char*));
    labelLine = (int*)malloc(sizeof(int));
    }
  else {
    labelNames = (char**)realloc(labelNames,sizeof(char*)*numLabels);
    labelValues = (word*)realloc(labelValues,sizeof(word)*numLabels);
    labelLine = (int*)realloc(labelLine,sizeof(int)*numLabels);
    labelProcs = (char**)realloc(labelProcs,sizeof(char*)*numLabels);
    }
  labelNames[numLabels-1] = (char*)malloc(strlen(name)+1);
  labelProcs[numLabels-1] = (char*)malloc(strlen(module)+1);
  strcpy(labelNames[numLabels-1], name);
  strcpy(labelProcs[numLabels-1], module);
  labelValues[numLabels-1] = value;
  labelLine[numLabels-1] = lineCount;
  return 0;
  }

void setLabel(char* name, word value) {
  int i;
  for (i=0; i<numLabels; i++)
    if (strcasecmp(labelNames[i], name) == 0) {
      labelValues[i] = value;
      return;
      }
  numLabels++;
  if (numLabels == 1) {
    labelNames = (char**)malloc(sizeof(char*));
    labelValues = (word*)malloc(sizeof(word));
    labelLine = (int*)malloc(sizeof(int));
    }
  else {
    labelNames = (char**)realloc(labelNames,sizeof(char*)*numLabels);
    labelValues = (word*)realloc(labelValues,sizeof(word)*numLabels);
    labelLine = (int*)realloc(labelLine,sizeof(int)*numLabels);
    }
  labelNames[numLabels-1] = (char*)malloc(strlen(name)+1);
  strcpy(labelNames[numLabels-1], name);
  labelValues[numLabels-1] = value;
  labelLine[numLabels-1] = lineCount;
  }

void addExternal(char* name) {
  int i;
  if (pass == 2) return;
  addLabel(name, 0);
  numExternals++;
  if (numExternals == 1)
    externals = (int*)malloc(sizeof(int));
  else
    externals = (int*)realloc(externals,sizeof(int)*numExternals);
  externals[numExternals-1] = findLabelNumber(name);
  }

void addDefine(char *def, char* value) {
  int i;
  for (i=0; i<numDefines; i++)
    if (strcmp(defines[i], def) == 0) {
      printf("Error: %s is defined more than once\n");
      errors++;
      return;
      }
  numDefines++;
  if (numDefines == 1) {
    defines = (char**)malloc(sizeof(char*));
    defineValues = (char**)malloc(sizeof(char*));
    }
  else {
    defines = (char**)realloc(defines,sizeof(char*)*numDefines);
    defineValues = (char**)realloc(defineValues,sizeof(char*)*numDefines);
    }
  defines[numDefines-1] = (char*)malloc(strlen(def) + 1);
  defineValues[numDefines-1] = (char*)malloc(strlen(value) + 1);
  strcpy(defines[numDefines-1], def);
  strcpy(defineValues[numDefines-1], value);
  }

char* findDefine(char*def) {
  int i;
  for (i=0; i<numDefines; i++)
    if (strcmp(defines[i], def) == 0) {
      return defineValues[i];
      }
  return NULL;
  }

void parse(char* line) {
  int pos;
  strcpy(label, "");
  strcpy(opcode, "");
  strcpy(arg1, "");
  strcpy(arg2, "");
  if (*line != ' ' && *line != '\t') {
    pos = 0;
    while (*line != 0 && *line != ' ' && *line != '\t' && *line != ':')
      label[pos++] = *line++;
    label[pos] = 0;
    if (*line == ':') line++;
    }
  while (*line == ' ' || *line == '\t') line++;
  if (*line == 0 || *line == ';') return;
  pos = 0;
  while (*line != 0 && *line != ' ' && *line != '\t')
    opcode[pos++] = *line++;
  opcode[pos] = 0;
  while (*line == ' ' || *line == '\t') line++;
  if (*line == 0 || *line == ';') return;
  pos = 0;
  while (*line != 0 && *line != ',' && *line != ';')
    arg1[pos++] = *line++;
  arg1[pos] = 0;
  if (*line == ',') line++;
  while (*line == ' ' || *line == '\t') line++;
  if (*line == 0 || *line == ';') return;
  pos = 0;
  while (*line != 0 && *line != ';')
    arg2[pos++] = *line++;
  arg2[pos] = 0;
  while (strlen(arg1) > 0 && arg1[strlen(arg1)-1] <= 32) arg1[strlen(arg1)-1] = 0;
  while (strlen(arg2) > 0 && arg2[strlen(arg2)-1] <= 32) arg2[strlen(arg2)-1] = 0;
  return;
  }

char* evaluate(char* expr, word* ret) {
  int  i;
  word nstack[256];
  int  nsp;
  byte ostack[256];
  int  osp;
  int  flag;
  char err;
  char token[128];
  int  pos;
  char isHex;
  char hexChar;
  word dec;
  word hex;
  word value;
  byte op;
  *ret = 0;
  evalErrors = 0;
  usedExternal = -1;
  usedLocal = 0;
  if (strcasecmp(expr, "A") == 0 ||
      strcasecmp(expr, "B") == 0 ||
      strcasecmp(expr, "C") == 0 ||
      strcasecmp(expr, "C)") == 0 ||
      strcasecmp(expr, "D") == 0 ||
      strcasecmp(expr, "E") == 0 ||
      strcasecmp(expr, "H") == 0 ||
      strcasecmp(expr, "L") == 0 ||
      strcasecmp(expr, "R") == 0 ||
      strcasecmp(expr, "I") == 0 ||
      strcasecmp(expr, "AF") == 0 ||
      strcasecmp(expr, "BC") == 0 ||
      strcasecmp(expr, "DE") == 0 ||
      strcasecmp(expr, "HL") == 0 ||
      strcasecmp(expr, "HL)") == 0 ||
      strcasecmp(expr, "SP") == 0 ||
      strcasecmp(expr, "SP)") == 0 ||
      strcasecmp(expr, "NC") == 0 ||
      strcasecmp(expr, "NZ") == 0 ||
      strcasecmp(expr, "PE") == 0 ||
      strcasecmp(expr, "PO") == 0 ||
      strcasecmp(expr, "M") == 0 ||
      strcasecmp(expr, "P") == 0 ||
      strcasecmp(expr, "Z") == 0 ||
      strcasecmp(expr, "IX") == 0 ||
      strcasecmp(expr, "IY") == 0 ||
      strcasecmp(expr, "IX)") == 0 ||
      strcasecmp(expr, "IY)") == 0 ||
      strcasecmp(expr, "IXH") == 0 ||
      strcasecmp(expr, "IYH") == 0 ||
      strcasecmp(expr, "IXL") == 0 ||
      strcasecmp(expr, "IYL") == 0 ||
      strcasecmp(expr, "(BC)") == 0 ||
      strcasecmp(expr, "(DE)") == 0 ||
      strcasecmp(expr, "(HL)") == 0 ||
      strncasecmp(expr, "(IX",3) == 0 ||
      strncasecmp(expr, "(IY",3) == 0 ||
      strncasecmp(expr, "IX+",3) == 0 ||
      strncasecmp(expr, "IY+",3) == 0 ||
      strncasecmp(expr, "IX-",3) == 0 ||
      strncasecmp(expr, "IY-",3) == 0 ||
      strcasecmp(expr, "(IX)") == 0 ||
      strcasecmp(expr, "(IY)") == 0) {
    evalErrors = 1;
    return expr;
    }
  osp = 0;
  nsp = 0;
  flag = 0;
  if (*expr == '-') {
    nstack[nsp++] = 0;
    ostack[osp++] = OP_SUB;
    expr++;
    }
  while (flag == 0) {
    hexChar = 'N';
    isHex = 'N';
    dec = 0;
    hex = 0;
    while (*expr == ' ') expr++;
    while (*expr == '(') {
      ostack[osp++] = OP_OP;
      expr++;
      }
    while (*expr == ' ') expr++;
    if (*expr == '$') {
      value = address;
      expr++;
      }
//    if (*expr == '$') {
//      isHex = 'Y';
//      expr++;
//      }
    else if (*expr >= '0' && *expr <= '9') {
      while ((*expr >= '0' && *expr <= '9') ||
             (*expr >= 'a' && *expr <= 'f') ||
             (*expr >= 'A' && *expr <= 'F')) {
        if (*expr >= '0' && *expr <= '9') {
          dec = (dec * 10) + (*expr - '0');
          hex = (hex * 16) + (*expr - '0');
          }
        if (*expr >= 'a' && *expr <= 'f') {
          hexChar = 'Y';
          hex = (hex * 16) + (*expr - 87);
          }
        if (*expr >= 'A' && *expr <= 'F') {
          hexChar = 'Y';
          hex = (hex * 16) + (*expr - 55);
          }
        expr++;
        }
      if (*expr == 'h' || *expr == 'H') {
        isHex = 'Y';
        expr++;
        }
      if (isHex == 'Y') {
        value = hex;
        }
      else if (hexChar == 'N') {
        value = dec;
        }
      else {
        printf("Error: Expression error\n");
        *ret = 0;
        evalErrors = 1;
        return expr;
        }
      }
    else if ((*expr >= 'a' && *expr <= 'z') ||
             (*expr >= 'A' && *expr <= 'Z') ||
             *expr == '_') {
      pos = 0;
      while ((*expr >= 'a' && *expr <= 'z') ||
             (*expr >= 'A' && *expr <= 'Z') ||
             (*expr >= '0' && *expr <= '9') ||
             *expr == '_') token[pos++] = *expr++;
      token[pos] = 0;
      value = findLabel(token, &err);
      if (err != 0) evalErrors = 1;
      }
    else if (*expr == '\'') {
      expr++;
      value = *expr++;
      while (*expr != 0 && *expr != '\'') expr++;
      if (*expr == '\'') expr++;
      }
    else {
      evalErrors = 1;
      return expr;
      }
    nstack[nsp++] = value;
    while (*expr == ' ' || *expr == '\t') expr++;
    op = OP_CP;
    while (op == OP_CP) {
      if (*expr == 0) op = OP_END;
      else if (*expr == '+') op = OP_ADD;
      else if (*expr == '-') op = OP_SUB;
      else if (*expr == '*') op = OP_MUL;
      else if (*expr == '/') op = OP_DIV;
      else if (*expr == ')') op = OP_CP;
      else if (*expr == '<' && *(expr+1) == '<') { op = OP_SHL; expr++; }
      else if (*expr == '>' && *(expr+1) == '>') { op = OP_SHR; expr++; }
      else if (*expr == '<' && *(expr+1) == '>') { op = OP_NE; expr++; }
      else if (*expr == '<' && *(expr+1) == '=') { op = OP_LE; expr++; }
      else if (*expr == '>' && *(expr+1) == '=') { op = OP_GE; expr++; }
      else if (*expr == '&' && *(expr+1) == '&') { op = OP_LAND; expr++; }
      else if (*expr == '|' && *(expr+1) == '|') { op = OP_LOR; expr++; }
      else if (*expr == '>') op = OP_GT;
      else if (*expr == '<') op = OP_LT;
      else if (*expr == '=') op = OP_EQ;
      else if (*expr == '&') op = OP_AND;
      else if (*expr == '|') op = OP_OR;
      else if (*expr == '^') op = OP_XOR;
      else {
        op = OP_END;
        flag = 0xff;
        }
      if (*expr != 0) expr++;
      while (osp > 0 && (ostack[osp-1] & 0xf0) >= (op & 0xf0)) {
        if (ostack[osp-1] == OP_ADD) { nstack[nsp-2] += nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_SUB) { nstack[nsp-2] -= nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_MUL) { nstack[nsp-2] *= nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_DIV) { nstack[nsp-2] /= nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_SHL) { nstack[nsp-2] <<= nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_SHR) { nstack[nsp-2] >>= nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_AND) { nstack[nsp-2] &= nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_OR) { nstack[nsp-2] |= nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_XOR) { nstack[nsp-2] ^= nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_NE) { nstack[nsp-2] = nstack[nsp-2] != nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_EQ) { nstack[nsp-2] = nstack[nsp-2] == nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_GE) { nstack[nsp-2] = nstack[nsp-2] >= nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_LE) { nstack[nsp-2] = nstack[nsp-2] <= nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_GT) { nstack[nsp-2] = nstack[nsp-2] > nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_LT) { nstack[nsp-2] = nstack[nsp-2] < nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_LAND) { nstack[nsp-2] = nstack[nsp-2] && nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_LOR) { nstack[nsp-2] = nstack[nsp-2] || nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_OP) {
          osp--;
          op = OP_STOP;
          }
        }
      if (op == OP_STOP) op = OP_CP;
      while (*expr == ' ' || *expr == '\t') expr++;
      }
    ostack[osp++] = op;
    if (*expr == 0) flag = 0xff;
    }
  if (nsp != 1) {
    printf("Error: Expression error\n");
    evalErrors = 1;
    }
  *ret = nstack[0];
  return expr;
  }

int lookupInstruction() {
  int i;
  char flag;
  word value;
  char temp[1024];
  char err;
  int  pos;
  usedExternal = -1;
  for (i=0; i<numOpcodes; i++) {
    if (strcasecmp(opcode,opcodes[i][0]) == 0) {
      c1 = 0;
      c2 = 0;
      flag = 0xff;
      if (strcasecmp(arg1, opcodes[i][1]) == 0 &&
          strcasecmp(arg2, opcodes[i][2]) == 0) {
        return i;
        }
      if (strcasecmp(opcodes[i][1],"[r]") == 0) {
        if (strcasecmp(arg1, "b") == 0) a1 = 0;
        else if (strcasecmp(arg1, "c") == 0) a1 = 1;
        else if (strcasecmp(arg1, "d") == 0) a1 = 2;
        else if (strcasecmp(arg1, "e") == 0) a1 = 3;
        else if (strcasecmp(arg1, "h") == 0) a1 = 4;
        else if (strcasecmp(arg1, "l") == 0) a1 = 5;
        else if (strcasecmp(arg1, "(hl)") == 0) a1 = 6;
        else if (strcasecmp(arg1, "a") == 0) a1 = 7;
        else flag = 0;
        }
      else if (strcasecmp(opcodes[i][1],"[cc]") == 0) {
        if (strcasecmp(arg1, "nz") == 0) a1 = 0;
        else if (strcasecmp(arg1, "z") == 0) a1 = 1;
        else if (strcasecmp(arg1, "nc") == 0) a1 = 2;
        else if (strcasecmp(arg1, "c") == 0) a1 = 3;
        else if (strcasecmp(arg1, "po") == 0) a1 = 4;
        else if (strcasecmp(arg1, "pe") == 0) a1 = 5;
        else if (strcasecmp(arg1, "p") == 0) a1 = 6;
        else if (strcasecmp(arg1, "m") == 0) a1 = 7;
        else flag = 0;
        }
      else if (strcasecmp(opcodes[i][1],"[bit]") == 0) {
        if (strcasecmp(arg1, "0") == 0) a1 = 0;
        else if (strcasecmp(arg1, "1") == 0) a1 = 1;
        else if (strcasecmp(arg1, "2") == 0) a1 = 2;
        else if (strcasecmp(arg1, "3") == 0) a1 = 3;
        else if (strcasecmp(arg1, "4") == 0) a1 = 4;
        else if (strcasecmp(arg1, "5") == 0) a1 = 5;
        else if (strcasecmp(arg1, "6") == 0) a1 = 6;
        else if (strcasecmp(arg1, "7") == 0) a1 = 7;
        else flag = 0;
        }
      else if (strcasecmp(opcodes[i][1],"[pp]") == 0) {
        if (strcasecmp(arg1, "bc") == 0) a1 = 0;
        else if (strcasecmp(arg1, "de") == 0) a1 = 1;
        else if (strcasecmp(arg1, "hl") == 0) a1 = 2;
        else if (strcasecmp(arg1, "sp") == 0) a1 = 3;
        else flag = 0;
        }
      else if (strcasecmp(opcodes[i][1],"[qq]") == 0) {
        if (strcasecmp(arg1, "bc") == 0) a1 = 0;
        else if (strcasecmp(arg1, "de") == 0) a1 = 1;
        else if (strcasecmp(arg1, "hl") == 0) a1 = 2;
        else if (strcasecmp(arg1, "af") == 0) a1 = 3;
        else flag = 0;
        }
      else if (strcasecmp(opcodes[i][1],"[rst]") == 0) {
        if (strcasecmp(arg1, "00h") == 0) a1 = 0;
        else if (strcasecmp(arg1, "08h") == 0) a1 = 1;
        else if (strcasecmp(arg1, "10h") == 0) a1 = 2;
        else if (strcasecmp(arg1, "18h") == 0) a1 = 3;
        else if (strcasecmp(arg1, "20h") == 0) a1 = 4;
        else if (strcasecmp(arg1, "28h") == 0) a1 = 5;
        else if (strcasecmp(arg1, "30h") == 0) a1 = 6;
        else if (strcasecmp(arg1, "38h") == 0) a1 = 7;
        else flag = 0;
        }
      else if (strcasecmp(opcodes[i][1],"(IX") == 0 &&
               strncasecmp(arg1,"(IX",3) == 0 &&
               (arg1[3] == '+' || arg1[3] == '-')) {
          evaluate(arg1+4, &value);
          value &= 0xff;
          if (arg1[3] == '-') value = ((value ^ 0xff) + 1) & 0xff;
          if (evalErrors != 0) flag = 0;
          c1 = 1;
          i1 = value;
        }
      else if (strcasecmp(opcodes[i][1],"(IY") == 0 &&
               strncasecmp(arg1,"(IY",3) == 0 &&
              (arg1[3] == '+' || arg1[3] == '-')) {
          evaluate(arg1+4, &value);
          value = value & 0xff;
          if (arg1[3] == '-') value = ((value ^ 0xff) + 1) & 0xff;
          if (evalErrors != 0) flag = 0;
          c1 = 1;
          i1 = value;
        }
      else if (strcasecmp(opcodes[i][1],"[d]") == 0 && strlen(arg2) == 0) {
        evalErrors = 0;
        if ((arg1[0] >= 'a' && arg1[0] <= 'z') ||
            (arg1[0] >= 'A' && arg1[0] <= 'Z')) {
          pos = 0;
          while ((arg1[pos] >= 'a' && arg1[pos] <= 'z') ||
                 (arg1[pos] >= 'A' && arg1[pos] <= 'Z') ||
                 (arg1[pos] >= '0' && arg1[pos] <= '9') ||
                 arg1[pos] == '_') {
            temp[pos] = arg1[pos];
            pos++;
            }
          temp[pos] = 0;
          if (pass == 1) value = 0;
            else value = findLabel(temp,&err) - (address+2);
          }
        else 
          evaluate(arg1, &value);
        i1 = value & 0xff;
        if (evalErrors != 0) flag = 0;
        if ((value & 0xff00) != 0 && (value & 0xff00) != 0xff00) {
          printf("Branch out of range: %04x\n",value);
          }
        c1 = 1;
        }
      else if (strcasecmp(opcodes[i][1],"[nn]") == 0) {
        evaluate(arg1, &value);
        if (value < 256 && evalErrors == 0) i1 = value;
          else flag = 0;
        c1 = 1;
        }
      else if (strcasecmp(opcodes[i][1],"([nn])") == 0 && 
        arg1[0] == '(' && arg1[strlen(arg1)-1] == ')') {
        evaluate(arg1+1, &value);
        if (value < 256 && evalErrors == 0) i1 = value;
          else flag = 0;
        c1 = 1;
        }
      else if (strcasecmp(opcodes[i][1],"[nnnn]") == 0 &&
               !(arg1[0] == '(' && arg1[strlen(arg1)-1] == ')')) {
        evaluate(arg1, &i1);
        c1 = 2;
        if (evalErrors != 0) flag = 0;
        }
      else if (strcasecmp(opcodes[i][1],"([nnnn])") == 0 &&
        arg1[0] == '(' && arg1[strlen(arg1)-1] == ')') {
        evaluate(arg1+1, &i1);
        c1 = 2;
        if (evalErrors != 0) flag = 0;
        }
      else if (strcasecmp(opcodes[i][1], arg1) != 0) flag = 0;

      if (strcasecmp(opcodes[i][2],"[r]") == 0) {
        if (strcasecmp(arg2, "b") == 0) a2 = 0;
        else if (strcasecmp(arg2, "c") == 0) a2 = 1;
        else if (strcasecmp(arg2, "d") == 0) a2 = 2;
        else if (strcasecmp(arg2, "e") == 0) a2 = 3;
        else if (strcasecmp(arg2, "h") == 0) a2 = 4;
        else if (strcasecmp(arg2, "l") == 0) a2 = 5;
        else if (strcasecmp(arg2, "(hl)") == 0) a2 = 6;
        else if (strcasecmp(arg2, "a") == 0) a2 = 7;
        else flag = 0;
        }
      else if (strcasecmp(opcodes[i][2],"[rx]") == 0) {
        if (strcasecmp(arg2, "b") == 0) a2 = 0;
        else if (strcasecmp(arg2, "c") == 0) a2 = 1;
        else if (strcasecmp(arg2, "d") == 0) a2 = 2;
        else if (strcasecmp(arg2, "e") == 0) a2 = 3;
        else if (strcasecmp(arg2, "ixh") == 0) a2 = 4;
        else if (strcasecmp(arg2, "ixl") == 0) a2 = 5;
        else if (strcasecmp(arg2, "a") == 0) a2 = 7;
        else flag = 0;
        }
      else if (strcasecmp(opcodes[i][2],"[ry]") == 0) {
        if (strcasecmp(arg2, "b") == 0) a2 = 0;
        else if (strcasecmp(arg2, "c") == 0) a2 = 1;
        else if (strcasecmp(arg2, "d") == 0) a2 = 2;
        else if (strcasecmp(arg2, "e") == 0) a2 = 3;
        else if (strcasecmp(arg2, "iyh") == 0) a2 = 4;
        else if (strcasecmp(arg2, "iyl") == 0) a2 = 5;
        else if (strcasecmp(arg2, "a") == 0) a2 = 7;
        else flag = 0;
        }
      else if (strcasecmp(opcodes[i][2],"[pp]") == 0) {
        if (strcasecmp(arg2, "bc") == 0) a2 = 0;
        else if (strcasecmp(arg2, "de") == 0) a2 = 1;
        else if (strcasecmp(arg2, "hl") == 0) a2 = 2;
        else if (strcasecmp(arg2, "sp") == 0) a2 = 3;
        else flag = 0;
        }
      else if (strcasecmp(opcodes[i][2],"[qq]") == 0) {
        if (strcasecmp(arg2, "bc") == 0) a2 = 0;
        else if (strcasecmp(arg2, "de") == 0) a2 = 1;
        else if (strcasecmp(arg2, "hl") == 0) a2 = 2;
        else if (strcasecmp(arg2, "af") == 0) a2 = 3;
        else flag = 0;
        }
      else if (strcasecmp(opcodes[i][2],"[ix]") == 0) {
        if (strcasecmp(arg2, "bc") == 0) a2 = 0;
        else if (strcasecmp(arg2, "de") == 0) a2 = 1;
        else if (strcasecmp(arg2, "ix") == 0) a2 = 2;
        else if (strcasecmp(arg2, "sp") == 0) a2 = 3;
        else flag = 0;
        }
      else if (strcasecmp(opcodes[i][2],"[iy]") == 0) {
        if (strcasecmp(arg2, "bc") == 0) a2 = 0;
        else if (strcasecmp(arg2, "de") == 0) a2 = 1;
        else if (strcasecmp(arg2, "iy") == 0) a2 = 2;
        else if (strcasecmp(arg2, "sp") == 0) a2 = 3;
        else flag = 0;
        }
      else if (strcasecmp(opcodes[i][2],"(IX") == 0 &&
               strncasecmp(arg2,"(IX",3) == 0 &&
               (arg2[3] == '+' || arg2[3] == '-')) {
          evaluate(arg2+4, &value);
          value &= 0xff;
          if (arg2[3] == '-') value = ((value ^ 0xff) + 1) & 0xff;
          if (evalErrors != 0) flag = 0;
          c2 = 1;
          i2 = value;
        }
      else if (strcasecmp(opcodes[i][2],"(IY") == 0 &&
               strncasecmp(arg2,"(IY",3) == 0 &&
               (arg2[3] == '+' || arg2[3] == '-')) {
          evaluate(arg2+4, &value);
          value &= 0xff;
          if (arg2[3] == '-') value = ((value ^ 0xff) + 1) & 0xff;
          if (evalErrors != 0) flag = 0;
          c2 = 1;
          i2 = value;
        }
      else if (strcasecmp(opcodes[i][2],"[d]") == 0) {
        evalErrors = 0;
        if ((arg2[0] >= 'a' && arg2[0] <= 'z') ||
            (arg2[0] >= 'A' && arg2[0] <= 'Z')) {
          pos = 0;
          while ((arg2[pos] >= 'a' && arg2[pos] <= 'z') ||
                 (arg2[pos] >= 'A' && arg2[pos] <= 'Z') ||
                 (arg2[pos] >= '0' && arg2[pos] <= '9') ||
                 arg2[pos] == '_') {
            temp[pos] = arg2[pos];
            pos++;
            }
          temp[pos] = 0;
          if (pass == 1) value = 0;
            else value = findLabel(temp,&err) - (address+2);
          }
        else 
          evaluate(arg2, &value);
        i2 = value & 0xff;
        if (evalErrors != 0) flag = 0;
        if ((value & 0xff00) != 0 && (value & 0xff00) != 0xff00) {
          printf("Branch out of range\n");
          }
        c2 = 1;
        }
      else if (strcasecmp(opcodes[i][2],"[nn]") == 0) {
        evaluate(arg2, &value);
        if (value < 256 && evalErrors == 0) i2 = value;
          else flag = 0;
        c2 = 1;
        }
      else if (strcasecmp(opcodes[i][2],"([nn])") == 0 &&
               arg2[0] == '(' && arg2[strlen(arg2)-1] == ')') {
        evaluate(arg2+1, &value);
        if (value < 256 && evalErrors == 0) i2 = value;
          else flag = 0;
        c2 = 1;
        }
      else if (strcasecmp(opcodes[i][2],"[nnnn]") == 0 &&
               !(arg2[0] == '(' && arg2[strlen(arg2)-1] == ')')) {
        evaluate(arg2, &i2);
        c2 = 2;
        if (evalErrors != 0) flag = 0;
        }
      else if (strcasecmp(opcodes[i][2],"([nnnn])") == 0 &&
               arg2[0] == '(' && arg2[strlen(arg2)-1] == ')') {
        evaluate(arg2+1, &i2);
        c2 = 2;
        if (evalErrors != 0) flag = 0;
        }
      else if (strcasecmp(opcodes[i][2], arg2) != 0) flag = 0;
      if (flag != 0) return i;
      }
    }
  return -1;
  }

void translateInstruction(int o) {
  byte  x,y,z,p,q;
  byte *b;
  char *trans;
  p=255;
  x = 0;
  y = 0;
  z = 0;
  q = 0;
  trans = translations[o];
  if (strncasecmp(trans, "DD CB",5) == 0) {
    output(0xdd);
    output(0xcb);
    trans+=5;
    if (c1 != 0) {
      output(i1 & 0xff);
      c1 = 0;
      }
    if (c2 != 0) {
      output(i2 & 0xff);
      c2 = 0;
      }
    }
  else if (strncasecmp(trans, "FD CB",5) == 0) {
    output(0xfd);
    output(0xcb);
    trans+=5;
    if (c1 != 0) {
      output(i1 & 0xff);
      c1 = 0;
      }
    if (c2 != 0) {
      output(i2 & 0xff);
      c2 = 0;
      }
    }
  else if (strncasecmp(trans, "CB", 2) == 0) {
    output(0xcb);
    trans+=2;
    }
  else if (strncasecmp(trans, "ED", 2) == 0) {
    output(0xed);
    trans+=2;
    }
  else if (strncasecmp(trans, "DD", 2) == 0) {
    output(0xdd);
    trans+=2;
    }
  else if (strncasecmp(trans, "FD", 2) == 0) {
    output(0xfd);
    trans+=2;
    }
  while (*trans == ' ') trans++;
  while (*trans != 0) {
    if (*trans == 'x' || *trans == 'X') b = &x;
    else if (*trans == 'y' || *trans == 'Y') b = &y;
    else if (*trans == 'z' || *trans == 'Z') b = &z;
    else if (*trans == 'p' || *trans == 'P') b = &p;
    else if (*trans == 'q' || *trans == 'Q') b = &q;
    *b = 0;
    trans+=2;
    if (*trans == '[') {
      trans++;
      if (*trans == '1') *b = a1;
      if (*trans == '2') *b = a2;
      trans += 2;
      }
    else {
      while (*trans >= '0' && *trans <= '9') {
        *b = (*b * 10) + (*trans - '0');
        trans++;
        }
      }
    while (*trans == ' ') trans++;
    }
  if (p == 255) output((x << 6) | (y << 3) | z);
    else output((x << 6) | (p << 4) | (q << 3) | z);
  if (c1 == 1) output(i1 & 0xff);
  if (c1 == 2) {
    if (usedExternal >= 0 && pass == 2) {
      if (pass == 2) fprintf(outFile,"?%s %04x\n",labelNames[externals[usedExternal]],address);
      }
    if (usedLocal != 0 && pass == 2) {
      fixups[numFixups] = address;
      fixupTypes[numFixups] = 'W';
      fixupLowOffset[numFixups] = 0;
      numFixups++;
      }
    output(i1 & 0xff);
    output((i1 >> 8) & 0xff);
    }
  if (c2 == 1) output(i2 & 0xff);
  if (c2 == 2) {
    if (usedExternal >= 0 && pass == 2) {
      if (pass == 2) fprintf(outFile,"?%s %04x\n",labelNames[externals[usedExternal]],address);
      }
    if (usedLocal != 0 && pass == 2) {
      fixups[numFixups] = address;
      fixupTypes[numFixups] = 'W';
      fixupLowOffset[numFixups] = 0;
      numFixups++;
      }
    output(i2 & 0xff);
    output((i2 >> 8) & 0xff);
    }
  }

void defReplace(char* line) {
  char  buffer[1024];
  char *pchar;
  int i;
  for (i=0; i<numDefines; i++) {
    while ((pchar = strstr(line, defines[i])) != NULL) {
      strncpy(buffer,line,pchar-line);
      buffer[pchar-line] = 0;
      strcat(buffer,defineValues[i]);
      strcat(buffer,pchar+strlen(defines[i]));
      strcpy(line,buffer);
      }
    }
  }

char* nextLine(char* line) {
  int   i;
  char* ret;
  int   flag;
  char  buffer[1024];
  int   pos;
  char *pchar;
  word  value;
  flag = -1;
  while (flag) {
    ret = fgets(line, 1024, sourceFile[fileNumber]);
    lineCount++;
    lineNumber[fileNumber]++;
    if (ret != NULL) {
      while (strlen(ret) > 0 && line[strlen(ret)-1] <= ' ')
        line[strlen(ret)-1] = 0;
      flag = 0;
      if (*ret == '#') {
        if (fileNumber == 0)
          sprintf(listLine,"[%05d] ",lineNumber[fileNumber]);
        else
          sprintf(listLine,"<%05d> ",lineNumber[fileNumber]);
        while (strlen(listLine) < 25) strcat(listLine," ");
        strcat(listLine,"  ");
        strcat(listLine,ret);
        if (pass == 2) {
          if (showList != 0) printf("%s\n",listLine);
          if (createListFile != 0) fprintf(listFile,"%s\n",listLine);
          }
        flag = -1;
        if (strncmp(ret,"#include ",9) == 0) {
          ret += 9;
          while (*ret == ' ' || *ret == '\t') ret++;
          pos = 0;
          while (*ret != 0 && *ret > ' ')
            buffer[pos++] = *ret++;
          buffer[pos] = 0;
          fileNumber++;
          lineNumber[fileNumber] = 0;
          sourceFile[fileNumber] = fopen(buffer,"r");
          if (sourceFile[fileNumber] == NULL) {
            }
          }
        if (strncmp(ret,"#define ",8) == 0) {
          ret += 8;
          while (*ret == ' ' || *ret == '\t') ret++;
          pos = 0;
          while (*ret != 0 && *ret > ' ')
            buffer[pos++] = *ret++;
          buffer[pos] = 0;
          while (*ret == ' ' || *ret == '\t') ret++;
          if (*ret == 0) addDefine(buffer,"1");
            else addDefine(buffer, ret);
          }
        if (strncmp(ret,"#ifdef ",7) == 0) {
          ret += 7;
          while (*ret == ' ' || *ret == '\t') ret++;
          pos = 0;
          while (*ret != 0 && *ret > ' ')
            buffer[pos++] = *ret++;
          buffer[pos] = 0;
          pchar = findDefine(buffer);
          if (pchar != NULL) {
            numNests++;
            nests[numNests] = 'Y';
            }
          else {
            numNests++;
            nests[numNests] = 'N';
            }
          }
        if (strncmp(ret,"#ifndef ",8) == 0) {
          ret += 8;
          while (*ret == ' ' || *ret == '\t') ret++;
          pos = 0;
          while (*ret != 0 && *ret > ' ')
            buffer[pos++] = *ret++;
          buffer[pos] = 0;
          pchar = findDefine(buffer);
          if (pchar != NULL) {
            numNests++;
            nests[numNests] = 'N';
            }
          else {
            numNests++;
            nests[numNests] = 'Y';
            }
          }
        if (strncmp(ret,"#if ",4) == 0) {
          ret += 4;
          while (*ret == ' ' || *ret == '\t') ret++;
          defReplace(ret);
          evaluate(ret, &value);
          if (value != 0) {
            numNests++;
            nests[numNests] = 'Y';
            }
          else {
            numNests++;
            nests[numNests] = 'N';
            }
          }
        if (strncmp(ret,"#endif",6) == 0) {
          if (numNests > 0) numNests--;
          else {
            printf("Error: Unmatched #endif\n");
            errors++;
            }
          }
        if (strncmp(ret,"#else",5) == 0) {
          if (numNests > 0)
            nests[numNests] = (nests[numNests] == 'Y') ? 'N' : 'Y';
          else {
            printf("Error: Unmatched #else\n");
            errors++;
            }
          }
        }
      else if (nests[numNests] != 'Y') {
        flag = -1;
        }
      else {
        defReplace(ret);
        }
      }
    else {
      if (fileNumber == 0) flag = 0;
      else {
        fclose(sourceFile[fileNumber]);
        fileNumber--;
        flag = -1;
        }
      }
    }
  return ret;
  }

int assemblyPass(char* sourceName) {
  int  o;
  int  i;
  word value;
  char *pchar;
  char  err;
  FTOI ftoi;
  char line[1024];
  sourceFile[0] = fopen(sourceName, "r");
  if (sourceFile[0] == NULL) {
    printf("Error: Could not open: %s\n",sourceName);
    return -1;
    }
  lineNumber[0] = 0;
  fileNumber = 0;
  lineCount = 0;
  address = 0;
  outCount = 0;
  outAddress = 0;
  codeGenerated = 0;
  numDefines = 0;
  strcpy(module,"*");
  inProc = 0;
  nests[0] = 'Y';
  numNests = 0;
  while (nextLine(line)) {
    strcpy(sourceLine, line);
    pchar = strchr(line, ';');
    if (pchar != NULL) {
      *pchar = 0;
      while (strlen(line) > 0 && line[strlen(line)-1] <= ' ')
        line[strlen(line)-1] = 0;
      }
    if (strcmp(line,".list") == 0) {
      showList = -1;
      strcpy(line,"");
      }
    parse(line);
    if (strlen(label) > 0 || strlen(opcode) > 0) {
      if (fileNumber == 0)
        sprintf(listLine,"[%05d] %04x:",lineNumber[fileNumber],address);
      else
        sprintf(listLine,"<%05d> %04x:",lineNumber[fileNumber],address);
      if (strlen(label) > 0) addLabel(label, address);
      instructionBytes = 0;
      if (strlen(opcode) > 0) {
        if (strcasecmp(opcode,"org") == 0) {
          if (outCount != 0) writeOutput();
          evaluate(arg1, &address);
          outAddress = address;
          }
        else if (strcasecmp(opcode,"extrn") == 0) {
          addExternal(arg1);
          }
        else if (strcasecmp(opcode,"public") == 0) {
          if (pass == 2) {
            i = findLabelNumber(arg1);
            if (i < 0) {
              printf("Error: Symbol not found: %s\n",arg1);
              errors++;
              }
            else {
              numPublics++;
              if (numPublics == 1)
                publics = (int*)malloc(sizeof(int));
              else
                publics = (int*)realloc(publics,sizeof(int)*numPublics);
              publics[numPublics-1] = i;
              }
            }
          }
        else if (strcasecmp(opcode,"proc") == 0) {
          inProc = -1;
          strcpy(module, arg1);
          if (outCount != 0) writeOutput();
          address = 0;
          outAddress = 0;
          if (pass == 1) addLabel(arg1, 0);
          if (pass == 2) {
            fprintf(outFile,"{%s\n",arg1);
            }
          numFixups = 0;
          }
        else if (strcasecmp(opcode,"endp") == 0) {
          if (inProc == 0) {
            printf("***ERROR: ENDP encountered outside PROC\n");
            errors++;
            }
          if (outCount != 0) writeOutput();
          if (pass == 2) {
            for (i=0; i<numFixups; i++) {
              if (fixupTypes[i] == 'W')
                fprintf(outFile,"+%04x\n",fixups[i]);
              if (fixupTypes[i] == 'H') {
                if (fixupLowOffset[i] != 0)
                  fprintf(outFile,"^%04x %02x\n",fixups[i],fixupLowOffset[i]);
                else
                  fprintf(outFile,"^%04x\n",fixups[i]);
                }
              if (fixupTypes[i] == 'L')
                fprintf(outFile,"v%04x\n",fixups[i]);
              }
            fprintf(outFile,"}\n");
            }
          }
        else if (strcasecmp(opcode,"ds") == 0) {
          if (outCount != 0) writeOutput();
          evaluate(arg1, &value);
          address += value;
          outAddress = address;
          }
        else if (strcasecmp(opcode,"db") == 0) {
          if (strlen(arg2) > 0) {
            strcat(arg1,",");
            strcat(arg1,arg2);
            }
          pchar = arg1;
          while (*pchar != 0) {
            if (*pchar == '"') {
              pchar++;
              while (*pchar != 0 && *pchar != '"') {
                output(*pchar);
                pchar++;
                }
              if (*pchar == '"') pchar++;
              }
            else {
              pchar = evaluate(pchar, &value);
              output(value & 0xff);
              }
            while (*pchar == ' ') pchar++;
            if (*pchar == ',') pchar++;
            while (*pchar == ' ') pchar++;
            }
          }
        else if (strcasecmp(opcode,"dw") == 0) {
          if (strlen(arg2) > 0) {
            strcat(arg1,",");
            strcat(arg1,arg2);
            }
          pchar = arg1;
          while (*pchar != 0) {
            pchar = evaluate(pchar, &value);
            output(value & 0xff);
            output((value >> 8) & 0xff);
            while (*pchar == ' ') pchar++;
            if (*pchar == ',') pchar++;
            while (*pchar == ' ') pchar++;
            }
          }
        else if (strcasecmp(opcode,"df") == 0) {
          ftoi.f = atof(arg1);
          output(ftoi.i & 0xff);
          output((ftoi.i >> 8) & 0xff);
          output((ftoi.i >> 16) & 0xff);
          output((ftoi.i >> 24) & 0xff);
          }
        else if (strcasecmp(opcode,"end") == 0) {
          if (outCount != 0) writeOutput();
          evaluate(arg1, &startAddress);
          }
        else if (strcasecmp(opcode,"equ") == 0) {
          evaluate(arg1, &value);
          if (strlen(label) > 0) setLabel(label, value);
          }
        else {
          o = lookupInstruction();
          if (o >= 0) {
            translateInstruction(o);
            }
          else {
            printf("Error: Invalid instruction\n");
            printf("   [%05d] %s\n",lineCount,sourceLine);
            errors++;
            }
          }
        }
      if (instructionBytes < 4) {
        while (strlen(listLine) < 25) strcat(listLine," ");
        strcat(listLine,"  ");
        strcat(listLine,sourceLine);
        }
      if (instructionBytes < 4 || ((instructionBytes % 4) != 0) && instructionBytes != 4)
        if (pass == 2) {
          if (showList != 0) printf("%s\n",listLine);
          if (createListFile != 0) fprintf(listFile,"%s\n",listLine);
          }
      }
    }
  while (fileNumber > 0) {
    fclose(sourceFile[fileNumber--]);
    }
  fclose(sourceFile[0]);
  for (i=0; i<numDefines; i++) {
    free(defines[i]);
    free(defineValues[i]);
    }
  if (numDefines > 0) {
    free(defines);
    free(defineValues);
    }
  return errors;
  }

void assembleFile(char* sourceName) {
  int   i;
  char *pchar;
  char buffer[1024];
  strcpy(baseName, sourceName);
  pchar = strchr(baseName,'.');
  if (pchar != NULL) *pchar = 0;
  strcpy(listName, baseName);
  strcat(listName, ".lst");
  strcpy(outName, baseName);
  strcat(outName, ".prg");

  printf("Source file: %s\n",sourceName);
  errors = 0;
  numLabels = 0;
  numExternals = 0;
  numPublics = 0;
  startAddress = 0xffff;
  pass = 1;
  if (assemblyPass(sourceName) != 0) {
    printf("Errors encountered. Assembly aborted\n");
    }
  else {
    pass = 2;
    outFile = fopen(outName, "w");
    if (createListFile != 0) listFile = fopen(listName, "w");
    assemblyPass(sourceName);
    if (outBytes > 0) writeOutput();
    if (startAddress != 0xffff)
      fprintf(outFile,"@%04x\n",startAddress);
    if (numPublics > 0) {
      for (i=0; i<numPublics; i++) {
        fprintf(outFile,"=%s %04x\n",labelNames[publics[i]],labelValues[publics[i]]);
        }
      }
    fclose(outFile);
    if (showSymbols != 0) {
      printf("\n");
      if (createListFile) fprintf(listFile,"\n");
      for (i=0; i<numLabels; i++) {
        sprintf(buffer,"%-16s %04x <%05d> \n",labelNames[i],labelValues[i],labelLine[i]);
        printf("%s",buffer);
        if (createListFile) fprintf(listFile,"%s",buffer);
        }
      printf("\n");
      if (createListFile) fprintf(listFile,"\n");
      }
    }
  printf("Lines assembled: %d\n",lineCount);
  printf("Errors         : %d\n",errors);
  printf("Code generated : %d\n",codeGenerated);
  if (createListFile != 0 && pass == 2) {
    fprintf(listFile,"Lines assembled: %d\n",lineCount);
    fprintf(listFile,"Errors         : %d\n",errors);
    fprintf(listFile,"Code generated : %d\n",codeGenerated);
    }
  if (createListFile != 0 && pass == 2) fclose(listFile);
  printf("\n");
  for (i=0; i<numLabels; i++) {
    free(labelNames[i]);
    }
  if (numExternals > 0) free(externals);
  if (numPublics > 0) free(publics);
  if (numLabels > 0) {
    free(labelNames);
    free(labelValues);
    free(labelLine);
    }
  }

int main(int argc, char **argv) {
  int i;
  printf("Asm/80 1.0 by Michael H. Riley\n\n");
  initOpcodes();
  showList = 0;
  showSymbols = 0;
  createListFile = 0;
  numSourceFiles = 0;
  for (i=1; i<argc; i++) {
    if (strcmp(argv[i],"-l") == 0) showList = -1;
    else if (strcmp(argv[i],"-L") == 0) createListFile = -1;
    else if (strcmp(argv[i],"-s") == 0) showSymbols = -1;
    else {
      numSourceFiles++;
      if (numSourceFiles == 1)
        sourceNames = (char**)malloc(sizeof(char*));
      else
        sourceNames = (char**)realloc(sourceNames,sizeof(char*) * numSourceFiles);
      sourceNames[numSourceFiles-1] = (char*)malloc(strlen(argv[i])+1);
      strcpy(sourceNames[numSourceFiles-1], argv[i]);
      }
    }
  if (numSourceFiles == 0) {
    printf("No source file specified\n");
    exit(1);
    }
  for (i=0; i<numSourceFiles; i++)
    assembleFile(sourceNames[i]);
  return 0;
  }

