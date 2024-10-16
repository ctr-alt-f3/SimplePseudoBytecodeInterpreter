#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
///
__int128_t regvs[3];
//
int instruction = 0;
int reg3 = 0; // also functioning as imm value
int reg1 = 0;
int reg2 = 0;
enum OPCODES {
  ADD_OP = 0,
  IMUL_OP = 1,
  SUB_OP = 2,
  DIV_OP = 3,
  PRINT_OP = 4,
  LOADI_OP = 5,
  SWAP_OP = 6,
  DONE_OP = 7,
};
void decode(__int128_t *bytecode) {
  instruction = (*bytecode & 0xF000) >> 12;
  reg1 = (*bytecode & 0x0F00) >> 8;
  reg2 = (*bytecode & 0x00F0) >> 4;
  reg3 = (*bytecode & 0x000F);
}
void interpret() {
  switch (instruction) {
  case ADD_OP:
    regvs[reg1] += regvs[reg2];
    break;
  case IMUL_OP:
    //   reg0 = reg1 * reg2;
    regvs[reg1] = regvs[reg2] * regvs[reg3];
    break;
  case SUB_OP:
    //   reg0 = reg1 - reg2;
    regvs[reg1] = regvs[reg2] - regvs[reg3];
    break;
  case DIV_OP:
    //  reg0 = reg1 / reg2;
    regvs[reg1] = regvs[reg2] / regvs[reg3];
    break;
  case PRINT_OP:
    printf("your register has value of: %d\n", regvs[reg1]);
    break;
  case LOADI_OP:
    //    reg0 = reg2; // reg is now functioning as imm value
    regvs[reg1] = regvs[reg3];
    break;
  case SWAP_OP:
    /* reg0 += reg1;
    reg1 = reg0 - reg1;
    reg0 -= reg1;*/
    regvs[reg1] += regvs[reg2];
    regvs[reg2] = regvs[reg1] - regvs[reg2];
    regvs[reg1] -= regvs[reg2];
    break;
  case DONE_OP:
    printf("Interpretation done successfully\nhere are register values:\n");
    printf("reg0 = %d\n", regvs[0]);
    printf("reg1 = %d\n", regvs[1]);
    printf("reg2 = %d\n", regvs[2]);
    break;

  default:
    printf("interpretation failed - wrong opcode - %d\n", instruction);
    break;
  }
}
int main() {
  //
  memset(regvs, 0, sizeof(regvs));
  /*  FILE *fp = fopen("instrukcje.m", "rb");
    //

    /*while (1) {
      if (fgets((char *)&opcode, sizeof(opcode), fp)) {
        break;
      }
      decode((__int128_t *)&opcode);
      printf("decoded\n");
      interpret();                         //does not work
  }*/
  /*unsigned char size = 0;
  fseek(fp, 0L, SEEK_END);
  size = ftell(fp);
  rewind(fp);
  void *buff = malloc(size + 1);
  fread(buff, size, 1, fp);
  unsigned int pointer = 0;
  void *opcode = 0;
  while (/*(rozmiar / 32) >= pointer /*this does not work too* *//* 1) {
    opcode = (&buff + pointer);
    decode((__int128_t *)opcode);
    //    printf("decoded\n");
    interpret();
    pointer += 16;
  }
  * /
      //
      /*  printf("debugging info...\n");
        printf("reg0 = %d\n", regvs[0]);
        printf("reg1 = %d\n", regvs[1]);
        printf("reg2 = %d\n", regvs[2]);
  fclose(fp);*/
  //
  return 0;
};
