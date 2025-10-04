#include "print_functions.h"
#include "types.h"

void print_register_16(register16_t const *const reg) {
  printf("(Reg) %s - 0x%02x\n", reg->name, reg->data);
}

void print_register_8(register8_t const *const reg) {
  printf("(Reg) %s - 0x%02x\n", reg->name, reg->data);
}

void print_gp_registers(uint8_t const *const regs, size_t size) {
  for (size_t i = 0; i < size; i++) {
    print_register_gp(regs[i], i);
  }
}

void print_register_gp(uint8_t reg_val, size_t idx) {
  int ascii_code;
  if (idx <= 9) {
    ascii_code = idx + 48;
  } else {
    ascii_code = idx + 55;
  }
  printf("(Reg) V%c - 0x%02x\n", ascii_code, reg_val);
}

void print_stack(stack_t const *const stack,
                 register8_t const *const stack_ptr) {
  printf("Current Stack\n");
  int elements = sizeof(stack->data) / sizeof(stack->data[0]);
  for (int i = elements; i >= 0; i--) {
    printf("Pos (%02d) - 0x%02x", i, stack->data[i]);
    if (stack_ptr->data == i) {
      printf(" <-- %s", stack_ptr->name);
    }
    printf("\n");
  }
}

void print_ram(uint8_t const *const ram, size_t size) {
  int bytes_per_line = 16;

  // For each line of ouput;
  for (size_t line = 0; line < size / bytes_per_line; line++) {
    printf("0x%04lx ", bytes_per_line * line);
    for (int bytes_read = 0; bytes_read < bytes_per_line; bytes_read++) {
      printf("0x%02x ", ram[line * bytes_per_line + bytes_read]);
    }
    printf("\n");
  }
}
