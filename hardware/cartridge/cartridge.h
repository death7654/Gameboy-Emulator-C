/*
0100 - 0103 entry_point
0104 - 0133 nintendo_logo
0134 - 0143 rom_title
013F - 0142 manufacturer_code
0143 - 0143 CGB_flag (use color mode no dont use color mode)
0144 – 0145 new_licence_code
0146 - 0146 SGB_flag
0147 - 0147 cartridge_type
0148 - 0148 rom_size
0149 - 0149 ram_size
014A - 014A destination_code eg japan (00) or overseas(01)
014B - 014B old_licence_code (33 indicates that the new licence code should be used)
014C - 014C game_version
014D - 014D header_checksum
014E - 014F global_checksum
*/
#pragma once

#include <stdint.h>

typedef struct
{
    uint8_t entry_point[4];
    uint8_t nintendo_logo[0x30];
    char rom_title[16];
    uint8_t manufacturer_code;
    uint8_t cgb_flag;
    uint16_t new_licence_code;
    uint8_t  sgb_flag;
    uint8_t cartridge_type;
    uint8_t rom_size;
    uint8_t ram_size;
    uint8_t destination_code;
    uint8_t old_licence_code;
    uint8_t game_version;
    uint8_t header_checksum;
    uint16_t global_checksum;
} rom_header;

//type names are defined at the end;

