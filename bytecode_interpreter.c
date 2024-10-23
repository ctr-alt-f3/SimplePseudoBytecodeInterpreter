#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
__int128_t regvs[3];
int instruction = 0;
int reg3 = 0; // also functioning as imm value
int reg1 = 0;
int reg2 = 0;
enum OPCODES {
  DONE_OP = 0,
  ADD_OP = 1,
  IMUL_OP = 2,
  SUB_OP = 3,
  DIV_OP = 4,
  PRINT_OP = 5,
  LOADI_OP = 6,
  SWAP_OP = 7,
};
void decode(__int128_t *bytecode) {
  if (bytecode == NULL) {
    perror("cannot decode - no opcode\n");
    return;
  }
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
    if (reg3 == 0) {
      printf("cannot divide by zero\n");
    }
    goto end;
    regvs[reg1] = regvs[reg2] / regvs[reg3];
  end:
    break;
  case PRINT_OP:
    printf("your register has value of: %d\n", regvs[reg1]);
    break;
  case LOADI_OP:
    //    reg0 = reg2; // reg is now functioning as imm value
    regvs[reg1] = reg3;
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
    /* printf("reg0 = %d\n", regvs[0]);
    printf("reg1 = %d\n", regvs[1]);
    printf("reg2 = %d\n", regvs[2]);*/
    break;
  default:
    printf("interpretation failed - wrong opcode - %x\n", instruction);
    break;
  }
}
int main() {
  memset(regvs, 0, sizeof(regvs));
  __int128_t bytecode[] = {
      // put here your code;
      0x6005, // LOADI_OP, reg1 = 0, reg3 = 5 (regvs[0] = 5)
      0x6102, // LOADI_OP, reg1 = 1, reg3 = 2 (regvs[1] = 2)
      0x1010, // ADD_OP,  reg1 = 0, reg2 = 1 (regvs[0] += regvs[1])
      0x5000, // PRINT_OP, reg1 = 0 print register 0
      0x7010, // SWAP_OP, reg1 = 0, reg2 = 1 (swap register 0 with register 1)
      0x5000, // PRINT_OP, reg1 = 0 (print regvs[0])
      0x0000, // DONE_OP (end program)
  };
  for (int i = 0; i < sizeof(bytecode) / sizeof(bytecode[0]); i++) {
    decode(&bytecode[i]);
    interpret();
  }
  //
  return 0;
};
