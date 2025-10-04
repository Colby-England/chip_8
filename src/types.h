#ifndef TYPES_H_INC
#define TYPES_H_INC
#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct {
  uint8_t data[4096];
  uint16_t start;
} ram_t;

typedef struct {
  uint8_t data;
  const char name[3];
} register8_t;

typedef struct {
  uint16_t data;
  const char name[3];
} register16_t;

typedef struct {
  uint16_t data[16];
} stack_t;

typedef struct {
  uint8_t data[64 * 32];
} display_t;

typedef struct {
  uint8_t data[15];
  size_t size;
} sprite_t;

typedef struct {
  ram_t memory;
  stack_t stack;
  uint8_t gp_registers[16];
  register16_t program_counter;
  register16_t index_register;
  register8_t stack_pointer;
  register8_t sound_timer;
  register8_t delay_timer;
  display_t display;
} chip8;

#endif // TYPES_H_INC
