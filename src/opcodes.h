#ifndef OPCODES_H_INC
#define OPCODES_H_INC
#pragma once

#include "types.h"
#include <stdint.h>
#include <string.h>

void op_00e0(chip8 *const chip, uint16_t instruction) {
  // clear the chip display
  memset(chip->display.data, 0,
         sizeof(chip->display.data) / sizeof(chip->display.data[0]));
}

void op_1nnn(chip8 *const chip, uint16_t instruction) {
  // set program counter to nnn
  uint16_t new_pc = instruction & 0x0FFF;
  chip->program_counter.data = new_pc;
}

void op_2nnn(chip8 *const chip, uint16_t instruction) {
  // Call subroutine at nnn
  // inc stack pointer, puts current PC on top of stack
  // PC is set to nnn
  chip->stack_pointer.data += 1;
  chip->stack.data[chip->stack_pointer.data] = chip->program_counter.data;
  op_1nnn(chip, instruction);
}

void op_3xkk(chip8 *const chip, uint16_t instruction) {
  int kk = instruction & 0x00FF;
  int reg = instruction & 0x0F00;

  if (chip->gp_registers[reg] == kk) {
    chip->program_counter.data += 2;
  }
}

#endif // OPCODES_H_INC
