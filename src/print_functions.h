#ifndef PRINT_FNC_H_INC
#define PRINT_FNC_H_INC
#pragma once

#include "types.h"

#include <stdint.h>
#include <stdio.h>

void print_register_16(register16_t const *const reg);
void print_register_gp(uint8_t reg_val, size_t idx);
void print_gp_registers(uint8_t const *const regs, size_t size);
void print_stack(stack_t const *const stack,
                 register8_t const *const stack_ptr);
void print_ram(uint8_t const *const ram, size_t size);

#endif // PRINT_FNC_H_INC
