#include "constants.h"
#include "opcodes.h"
#include "print_functions.h"
#include "types.h"

#include <stdbool.h>
#include <stdio.h>

[[nodiscard]] bool load_rom(char const *const path, chip8 *const chip) {
  FILE *fp = fopen(path, "rb");
  if (fp == nullptr) {
    perror("Failed to open file.\n");
    return false;
  }

  // Find the size of file
  fseek(fp, 0L, SEEK_END);
  int64_t size = ftell(fp);
  rewind(fp);

  // Read size bytes into chip8 memory @ start addr
  size_t bytes_read = fread(&(chip->memory.data[chip->memory.start]),
                            sizeof(chip->memory.data[0]), size, fp);

  if ((int64_t)bytes_read != size) {
    perror("Did not read entire file.\n");
    fclose(fp);
    return false;
  }

  fclose(fp);
  return true;
}

/// @brief Initialize the font sprites into the chip8 ROM.
/// @param[in] chip A const pointer to a chip8 device.
void init_font_sprites(chip8 *const chip) {
  for (size_t i = 0; i < FONTSET_SIZE; i++) {
    chip->memory.data[FONT_START_ADDR + i] = fontset[i];
  }
}

int main(void) {
  chip8 chip = {
      .memory = {{0}, 0x200}, // Initialize all ram to 0 and start addr
      .stack = {{0}},         // Initialize stack to 0
      .gp_registers = {0},    // Initialize all registers to 0
      .program_counter = {.data = 0x200, .name = {"PC"}},
      .index_register = {.data = 0, .name = {"I"}},
      .stack_pointer = {.data = 0, .name = {"SP"}},
      .sound_timer = {.data = 0, .name = {"ST"}},
      .delay_timer = {.data = 0, .name = {"DT"}},
      .display = {.data = {0}}};

  // TODO: Make a chip8 init function.
  bool success = load_rom("./test.bin", &chip);
  if (!success) {
    return -1;
  }

  init_font_sprites(&chip);
}
