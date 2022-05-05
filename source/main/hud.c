#include <gb/gb.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "hud.h"
#include "Tetrominos.h"
#include "graphics/Tetromino1.h"
#include "graphics/Tetromino2.h"
#include "graphics/Tetromino3.h"
#include "graphics/Tetromino4.h"
#include "graphics/Tetromino5.h"
#include "graphics/Tetromino6.h"
#include "graphics/Tetromino7.h"
#include "graphics/TileAnimation.h"
#include "graphics/UserInterface.h"
#include "graphics/Numbers.h"

void DrawNumber(uint8_t x,uint8_t y, uint16_t number,uint8_t digits){
	
    unsigned char buffer[]="00000000";

    // Convert the number to a decimal string (stored in the buffer char array)
    uitoa(number, buffer, 10);

    // Get the length of the number so we can add leading zeroes
    uint8_t len =strlen(buffer);

    // Add some leading zeroes
    // uitoa will not do this for us
    // Increase the VRAM address each iteration to move to the next tile
    for(uint8_t i=0;i<digits-len;i++){
        VBK_REG=1; set_bkg_tile_xy(x,y,4);
        VBK_REG=0;set_bkg_tile_xy(x++,y,NUMBERS_TILES_START);
    }
        
    // Draw our number
    // Increase the VRAM address each iteration to move to the next tile
    for(uint8_t i=0;i<len;i++){
        
        VBK_REG=1;set_bkg_tile_xy(x,y,4);
        VBK_REG=0;set_bkg_tile_xy(x++,y,(buffer[i]-'0')+NUMBERS_TILES_START);
    }
}


void UpdateGui(){

    DrawNumber(14,10,score,5);
    DrawNumber(14,13,level,2);
    DrawNumber(14,16,lines,2);

    move_metasprite(Tetrominos_metasprites[nextCurrentTetromino*4+nextCurrentTetrominoRotation],tileOffsets[nextCurrentTetromino],16,124,36);
}

void IncreaseScore(uint8_t amount){

    score+=amount;

    // Update the gui with our new score
    UpdateGui();
}
