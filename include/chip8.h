#ifndef CHIP8_H
#define CHIP8_H
#define MEMORY_SIZE 4096 // Max memory size set to 4kB
#define ROM_LOADING_ADDR 0x200 // Loading point for ROMs - first 512 bytes are 
                               // reserved for the interpreter
#define STACK_DEPTH 16 // Max stack depth for nested subroutines
#define SCREEN_WIDTH 64 // Defined by classic dimensions
#define SCREEN_HEIGHT 32

typedef struct chip8 {
    /* Core resources */
    uint8_t memory[MEMORY_SIZE];    // Main RAM
    uint8_t V[16];                  // General registers V0-V16
    uint16_t I;                     // Index register
    uint16_t PC;                    // Program counter

    /* Call stack */
    uint16_t stack[STACK_DEPTH];    // Main program stack
    uint8_t SP;                     // Stack pointer

    /* Timers */
    uint8_t delay_timer;
    uint8_t sound_timer;

    /* I/O */
    uint8_t video[SCREEN_WIDTH * SCREEN_HEIGHT];
                                    // Monochrome frame buffer - 1 byte/pixel
    uint8_t keypad[16];
    uint8_t draw_flag;              // Indicates that screen buffer has been
                                    // altered and should be redrawn

    /* Helpers */
} chip8_t;

void chip8_init(chip8_t* chip);
void chip8_load_rom(chip8_t* chip, const uint8_t* blob, size_t size);
void chip8_cycle(chip8_t* chip); // Runs fetch-decode-execute one time

#endif