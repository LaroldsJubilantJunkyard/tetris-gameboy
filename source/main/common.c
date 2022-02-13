#include <gb/gb.h>

uint8_t RandomNumber(uint8_t min, uint8_t max)
{
    const unsigned char *ptr_div_reg = 0xFF04;

    // get value at memory address
    return min + (*(ptr_div_reg) % (max - min)); 
}