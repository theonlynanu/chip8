#ifndef CHIP8_H
#define CHIP8_H
#include <stdint.h>
#include <stddef.h>
#define MEMORY_SIZE 4096 // Max memory size set to 4kB
#define ROM_LOADING_ADDR 0x200 // Loading point for ROMs - first 512 bytes are 
                               // reserved for the interpreter
#define STACK_DEPTH 16 // Max stack depth for nested subroutines
#define SCREEN_WIDTH 64 // Defined by classic dimensions
#define SCREEN_HEIGHT 32
#define GENERAL_REGISTER_COUNT 16
#define KEYPAD_LENGTH 16
#define PROGRAM_START 0x200
#define FONT_START 0x050
#define FONT_SIZE 80

/**
 * Main chip8 emulator struct
 */
typedef struct chip8 {
    /* Core resources */
    uint8_t memory[MEMORY_SIZE];        // Main RAM
    uint8_t V[GENERAL_REGISTER_COUNT];  // General registers V0-V16
    uint16_t I;                         // Index register
    uint16_t PC;                        // Program counter

    /* Call stack */
    uint16_t stack[STACK_DEPTH];        // Main program stack
    uint8_t SP;                         // Stack pointer

    /* Timers */
    uint8_t delay_timer;
    uint8_t sound_timer;

    /* I/O */
    uint8_t video[SCREEN_WIDTH * SCREEN_HEIGHT];
                                    // Monochrome frame buffer - 1 byte/pixel
    uint8_t keypad[KEYPAD_LENGTH];
    uint8_t draw_flag;              // Indicates that screen buffer has been
                                    // altered and should be redrawn

    /* Helpers */
} chip8_t;

/**
 * Clears and sets up a clean chip8_t instance.
 * 
 * This will also clear any ROMs currently in memory, so be sure to reload any
 * ROMs if doing a reset
 */
void chip8_init(chip8_t* chip);
void chip8_load_rom(chip8_t* chip, const uint8_t* blob, size_t size);
void chip8_cycle(chip8_t* chip); // Runs fetch-decode-execute one time

#endif