#pragma once

#include <stdint.h>
#include <stdbool.h>
typedef struct
{
    //A-L are the 12 CPU registers found on the gameboy
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t f;
    uint8_t g;
    uint8_t h;
    uint8_t i;
    uint8_t j;
    uint8_t k;
    uint8_t l;

    uint16_t pc;
    uint16_t sp;
} gameboy_cpu;

typedef struct
{
    
    bool halt;
    bool stop;

} cpu_state;

