#include "../include/chip8.h"
#include <stdio.h>

/* clang testCore.c ../src/chip8.c -o [whatever] */



/**
 * Test clearing during chip8_init()
 */
int test1() {
    int passed = 1;
    chip8_t chip;
    chip.draw_flag = 1;
    chip.memory[0] = 0x1F;
    chip.I = 0x1412;
    chip.keypad[4] = 0xF2;
    chip8_init(&chip);

    for (int i = 0; i < GENERAL_REGISTER_COUNT; i++) {
        if (chip.V[i] != 0) {
            printf("Register %d not cleared!\n", i);
            passed = 0;
        }

    }
    for (int i = 0; i < STACK_DEPTH; i++) {
        if (chip.stack[i] != 0) {
            printf("Stack frame %d not cleared!\n", i);
            passed = 0;
        }
    }

    if (chip.I != 0) {
        printf("Index register not cleared!\n");
        passed = 0;
    }

    if (chip.PC != 0x200) {
        printf("Program counter not cleared!\n");
        passed = 0;
    }

    if (chip.delay_timer != 0 || chip.sound_timer != 0) {
        printf("Timers not cleared!\n");
    }

    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        if (chip.video[i] != 0) {
            printf("Video frame buffers not cleared!\n");
            passed = 0;
        }
    }

    for (int i = 0; i < KEYPAD_LENGTH; i++) {
        if (chip.keypad[i] != 0) {
            printf("Keypad data not cleared!\n");
            passed = 0;
        }
    }

    if (chip.draw_flag != 0) {
        printf("Draw flag not reset!\n");
        passed = 0;
    }

    return passed;
}

int (*unitTests[])() = {test1, NULL};

int main() {
    int counter = 0;
    int testsPassed = 0;

    while (unitTests[counter] != NULL) {
        printf("========== Test %d ==========\n", counter);
        if (unitTests[counter]() == 1) {
            printf("Test %d passed\n", counter);
            testsPassed++;
        } else {
            printf("Test %d failed\n", counter);
        }
        printf("\n");
        counter++;
    }

    printf("%d of %d tests passed\n", testsPassed, counter);
    return 0;
}