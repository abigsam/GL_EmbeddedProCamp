#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>


uint16_t rgb_888_to_565(uint32_t rgb888);


int main ()
{
    printf("RGB888 = 0x%X; RGB565 = 0x%X\n", 0x45a1, rgb_888_to_565(0x45a1));
    
    return 0;
}

uint16_t rgb_888_to_565(uint32_t rgb888)
{
    return ( (uint16_t)((rgb888 >> 3) & 0xf800) | //R
             (uint16_t)((rgb888 >> 2) & 0x7e0)  | //G
             (uint16_t)((rgb888 >> 3) & 0x1f)     //B
           );
}

