#include "cartridge.h"


typedef struct
{
    char filename[1024];
    uint32_t file_size;
    uint8_t *rom_data; //reference to an address
    rom_header *header;
} cartridge_file;


static cartridge_file ctx; //creates a static context, static implies the data should be useable while the program is executing

static const char *CARTRIDGE_TYPE[] =
{
    "ROM ONLY",
    "MBC1",
    "MBC1+RAM",
    "MBC1+RAM+BATTERY",
    "0x04 ???",
    "MBC2",
    "MBC2+BATTERY",
    "0x07 ???",
    "ROM+RAM 1",
    "ROM+RAM+BATTERY 1",
    "0x0A ???",
    "MMM01",
    "MMM01+RAM",
    "MMM01+RAM+BATTERY",
    "0x0E ???",
    "MBC3+TIMER+BATTERY",
    "MBC3+TIMER+RAM+BATTERY 2",
    "MBC3",
    "MBC3+RAM 2",
    "MBC3+RAM+BATTERY 2",
    "0x14 ???",
    "0x15 ???",
    "0x16 ???",
    "0x17 ???",
    "0x18 ???",
    "MBC5",
    "MBC5+RAM",
    "MBC5+RAM+BATTERY",
    "MBC5+RUMBLE",
    "MBC5+RUMBLE+RAM",
    "MBC5+RUMBLE+RAM+BATTERY",
    "0x1F ???",
    "MBC6",
    "0x21 ???",
    "MBC7+SENSOR+RUMBLE+RAM+BATTERY",
};

static const char *LICENCE_CODES[0xA5] = //creates an array with size 0xA5 or around 165 bits
{
    [0x00] = "None",
    [0x01] = "Nintendo R&D1",
    [0x08] = "Capcom",
    [0x13] = "Electronic Arts",
    [0x18] = "Hudson Soft",
    [0x19] = "b-ai",
    [0x20] = "kss",
    [0x22] = "pow",
    [0x24] = "PCM Complete",
    [0x25] = "san-x",
    [0x28] = "Kemco Japan",
    [0x29] = "seta",
    [0x30] = "Viacom",
    [0x31] = "Nintendo",
    [0x32] = "Bandai",
    [0x33] = "Ocean/Acclaim",
    [0x34] = "Konami",
    [0x35] = "Hector",
    [0x37] = "Taito",
    [0x38] = "Hudson",
    [0x39] = "Banpresto",
    [0x41] = "Ubi Soft",
    [0x42] = "Atlus",
    [0x44] = "Malibu",
    [0x46] = "angel",
    [0x47] = "Bullet-Proof",
    [0x49] = "irem",
    [0x50] = "Absolute",
    [0x51] = "Acclaim",
    [0x52] = "Activision",
    [0x53] = "American sammy",
    [0x54] = "Konami",
    [0x55] = "Hi tech entertainment",
    [0x56] = "LJN",
    [0x57] = "Matchbox",
    [0x58] = "Mattel",
    [0x59] = "Milton Bradley",
    [0x60] = "Titus",
    [0x61] = "Virgin",
    [0x64] = "LucasArts",
    [0x67] = "Ocean",
    [0x69] = "Electronic Arts",
    [0x70] = "Infogrames",
    [0x71] = "Interplay",
    [0x72] = "Broderbund",
    [0x73] = "sculptured",
    [0x75] = "sci",
    [0x78] = "THQ",
    [0x79] = "Accolade",
    [0x80] = "misawa",
    [0x83] = "lozc",
    [0x86] = "Tokuma Shoten Intermedia",
    [0x87] = "Tsukuda Original",
    [0x91] = "Chunsoft",
    [0x92] = "Video system",
    [0x93] = "Ocean/Acclaim",
    [0x95] = "Varie",
    [0x96] = "Yonezawa/s’pal",
    [0x97] = "Kaneko",
    [0x99] = "Pack in soft",
    [0xA4] = "Konami (Yu-Gi-Oh!)"
}; //used to match cartridge type to the manufacturer

//finds licence name from the array
const char *cartrige_licence_name()
{
    return (ctx.header->new_licence_code <= 0xA4) ? (LICENCE_CODES[ctx.header->new_licence_code]) : "UNKNOWN"; //-> means the variable inside a struct inside the struct
}
//finds cartridge type from the array
const char *cartridge_type()
{
    return (ctx.header->cartridge_type <= 0x22) ? (LICENCE_CODES[ctx.header->new_licence_code]) : "UNKNOWN"; //-> means the variable inside a struct inside the struct

}

bool cartridge_loaded(char *cartridge)
{
    snprintf(ctx.filename, sizeof(ctx.filename), "%s", cartridge);//reads the entire file into the variable cartridge.
    FILE *fp = fopen(cartridge, "r");

    if(!fp)
    {
        printf("failed to open cartridge file");
        return false;
    }
    //error handling
    fseek(fp, 0, SEEK_END); //checks for the true size of rom

    ctx.file_size = ftell(fp); //puts the size of the rom into file_size

    rewind(fp); //rewinds fp to the inital state of the rom

    ctx.rom_data = malloc(ctx.file_size); //allocates the memory equal to the rom size
    fread(ctx.rom_data, ctx.file_size, 1, fp); //reads the data with size file_size from fp
    fclose(fp);//closes file

    uint16_t x = 0;
    
    ctx.header = (rom_header *)(ctx.rom_data + 0x100); //starts the reading at the entry point 0x100
    ctx.header->rom_title[15] = 0; //fills the rom_title with 0s so whatever is not used will not be null

    //todo add rest of the data
    
    printf("Cartridge Loaded:\n");
    printf("\t Cartridge Title: %s\n", ctx.header->rom_title);
    printf("\t Cartridge Type : %2.2X (%s)\n", ctx.header->cartridge_type, cartridge_type());
    printf("\t ROM Size       : %d KB\n", 32 << ctx.header->rom_size);
    printf("\t RAM Size       : %2.2X\n", ctx.header->ram_size);
    printf("\t Licence Code   : %2.2X (%s)\n", ctx.header->new_licence_code, cartrige_licence_name());
    printf("\t ROM Version    : %2.2X\n", ctx.header->game_version);
    
    printf("\t Checksum : %2.2X (%s)\n", ctx.header->global_checksum, (x & 0xFF) ? "PASSED" : "FAILED");
    return true;
}
