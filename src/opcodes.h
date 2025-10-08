#ifndef OPCODES_H_INC
#define OPCODES_H_INC
#pragma once

#include "types.h"
#include <stdint.h>
#include <string.h>

// @brief Clear the display of the chip8.
//
// @param chip The chip8 to run the instruction on.
// @param instruction The value of the instruction.
void op_00e0(chip8 *const chip, uint16_t instruction) {
  memset(chip->display.data, 0,
         sizeof(chip->display.data) / sizeof(chip->display.data[0]));
}

// @brief Sets the program counter to the 12 lowest bits of the instruction.
//
// @param chip The chip8 to run the instruction on.
// @param instruction The value of the instruction.
void op_1nnn(chip8 *const chip, uint16_t instruction) {
  uint16_t new_pc = instruction & 0x0FFF;
  chip->program_counter.data = new_pc;
}

// @brief Call the subroutine at the addrress given by the 12 lowest bits
// of the instruction.
//
// This will increment the stack counter by 1, push the current value of the
// program counter to the top of the stack and then set the program counter to
// nnn.
//
// @param chip The chip8 to run the instruction on.
// @param instruction The value of the instruction.
void op_2nnn(chip8 *const chip, uint16_t instruction) {
  chip->stack_pointer.data += 1;
  chip->stack.data[chip->stack_pointer.data] = chip->program_counter.data;
  op_1nnn(chip, instruction);
}

// @brief Skips the next instruction if register x is equal to kk.
//
// @param chip The chip8 to run the instruction on.
// @param instruction The value of the instruction.
void op_3xkk(chip8 *const chip, uint16_t instruction) {
  int kk = instruction & 0x00FF;
  int reg = instruction & 0x0F00;

  if (chip->gp_registers[reg] == kk) {
    chip->program_counter.data += 2;
  }
}

// @brief Skips the next instruction if register x is not equal to kk.
//
// @param chip The chip8 to run the instruction on.
// @param instruction The value of the instruction.
void op_4xkk(chip8 *const chip, uint16_t instruction) {
  int kk = instruction & 0x00FF;
  int reg = instruction & 0x0F00;

  if (chip->gp_registers[reg] != kk) {
    chip->program_counter.data += 2;
  }
}

// @brief Skips the next instruction if register x is equal to register y.
//
// @param chip The chip8 to run the instruction on.
// @param instruction The value of the instruction.
void op_5xy0(chip8 *const chip, uint16_t instruction) {
  int reg_x = instruction & 0x0F00;
  int reg_y = instruction & 0x00F0;

  if (chip->gp_registers[reg_x] == chip->gp_registers[reg_y]) {
    chip->program_counter.data += 2;
  }
}

// @brief Load the value kk into register Vx.
//
// @param chip The chip8 to run the instruction on.
// @param instruction The value of the instruction.
void op_6xkk(chip8 *const chip, uint16_t instruction) {
  int reg_x = instruction & 0x0F00;
  int kk = instruction & 0x00FF;

  chip->gp_registers[reg_x] = kk;
}

// @brief Add the value kk to the valye of register x.
//
// @param chip The chip8 to run the instruction on.
// @param instruction The value of the instruction.
void op_7xkk(chip8 *const chip, uint16_t instruction) {
  int reg_x = instruction & 0x0F00;
  int kk = instruction & 0x00FF;

  chip->gp_registers[reg_x] += kk;
}

#endif // OPCODES_H_INC
