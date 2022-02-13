#include <gb/gb.h>
#include "common.h"


uint8_t tileAnimationCounter=0;


uint8_t fallTimer = 0, isBlinking = 0;
uint8_t currentTetromino = 0,nextCurrentTetromino=0;
uint8_t currentTetrominoRotation = 0,nextCurrentTetrominoRotation=0;
uint8_t joypadCurrent, joypadPrevious;
uint8_t currentX, currentY;

uint16_t score,lines;

uint16_t lines=0;
uint8_t level=1;

uint8_t blankTile=0,blankTilePalette=0,tileAnimationBase,tileAnimationBasePalette;

unsigned char reusableRow10[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

uint8_t RandomNumber(uint8_t min, uint8_t max)
{
    const unsigned char *ptr_div_reg = 0xFF04;

    // get value at memory address
    return min + (*(ptr_div_reg) % (max - min)); 
}

void ResetAllSprites(){

    // Reset all sprites
    for (uint8_t i = 0; i < 40; i++){
        set_sprite_tile(i, 0);
        move_sprite(i,160,160);
    }
}