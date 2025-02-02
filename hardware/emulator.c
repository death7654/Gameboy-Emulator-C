#include <stdio.h>
#include "emulator.h"
#include "cartridge.h"
#include "cpu.h"
#include "../SDL3-3.2.0/include/SDL3/SDL.h"
#include "../SDL3-3.2.0/include/SDL3/SDL_timer.h"
#define SDL_MAIN_HANDLED


/* 
  Emu components:

  |Cart|
  |CPU|
  |Address Bus|
  |PPU|
  |Timer|

*/

static emu_context ctx;

emu_context *emu_get_context() {
    return &ctx;
}

void delay(uint32_t ms) {
    //SDL_Delay(ms);
}

int emu_run(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: emulator <rom_file>\n");
        return -1;
    }

    if (!cartridge_loaded(argv[1])) {
        printf("Failed to load ROM file: %s\n", argv[1]);
        return -2;
    }

    printf("Cart loaded..\n");

    //todo fix GPU
    SDL_Init(SDL_INIT_VIDEO);
    printf("SDL INIT\n");
    TTF_Init();
    //printf("TTF INIT\n");

    //cpu_init();
    
    ctx.running = true;
    ctx.paused = false;
    ctx.ticks = 0;

    while(ctx.running) {
        if (ctx.paused) {
            delay(10);
            continue;
        }
        /*
        if (!cpu_step()) {
            printf("CPU Stopped\n");
            return -3;
        }*/

        ctx.ticks++;
    }

    return 0;
}