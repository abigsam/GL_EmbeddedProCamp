#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>


uint16_t swap16(uint16_t word);
uint32_t swap32(uint32_t word);
uint64_t swap64(uint64_t word);


int main ()
{
    printf("swap16(0x%X) = 0x%X\n", 0x45a1, swap16(0x45a1));
    printf("swap32(0x%X) = 0x%X\n", 0xA0B0C0D0, swap32(0xA0B0C0D0));
    printf("swap64(0x%"PRIX64") = 0x%"PRIX64"\n", 0xA0B0C0D090807060, swap64(0xA0B0C0D090807060));
    
    return 0;
}

uint16_t swap16(uint16_t word)
{
    return ( ((word >> 8) & 0xff) | ((word << 8) & 0xff00) );
}


uint32_t swap32(uint32_t word)
{
    return ( ((word << 24) & 0xff000000) |
             ((word << 8)  & 0x00ff0000) |
             ((word >> 8)  & 0x0000ff00) |
             ((word >> 24) & 0x000000ff)
           );
}


uint64_t swap64(uint64_t word)
{
    return ( ((word << (8*7)) & 0xff00000000000000) |
             ((word << (8*5)) & 0x00ff000000000000) |
             ((word << (8*3)) & 0x0000ff0000000000) |
             ((word << (8*1)) & 0x000000ff00000000) |
             ((word >> (8*1)) & 0x00000000ff000000) |
             ((word >> (8*3)) & 0x0000000000ff0000) |
             ((word >> (8*5)) & 0x000000000000ff00) |
             ((word >> (8*7)) & 0x00000000000000ff)
           );
}