#include <gb/gb.h>
#include <gb/metasprites.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "hud.h"
#include "GameplayGui.h"
#include "TetrisTilesAndGui.h"
#include "graphics/Tetromino1.h"
#include "graphics/Tetromino2.h"
#include "graphics/Tetromino3.h"
#include "graphics/Tetromino4.h"
#include "graphics/Tetromino5.h"
#include "graphics/Tetromino6.h"
#include "graphics/Tetromino7.h"
#include "graphics/TileAnimation.h"
#include "graphics/UserInterface.h"
#include "graphics/Palette.h"
#include "graphics/Numbers.h"

extern const metasprite_t Tetromino1_metasprite0[], Tetromino1_metasprite1[], Tetromino1_metasprite2[], Tetromino1_metasprite3[];
extern const metasprite_t Tetromino2_metasprite0[], Tetromino2_metasprite1[], Tetromino2_metasprite2[], Tetromino2_metasprite3[];
extern const metasprite_t Tetromino3_metasprite0[], Tetromino3_metasprite1[], Tetromino3_metasprite2[], Tetromino3_metasprite3[];
extern const metasprite_t Tetromino4_metasprite0[], Tetromino4_metasprite1[], Tetromino4_metasprite2[], Tetromino4_metasprite3[];
extern const metasprite_t Tetromino5_metasprite0[], Tetromino5_metasprite1[], Tetromino5_metasprite2[], Tetromino5_metasprite3[];
extern const metasprite_t Tetromino6_metasprite0[], Tetromino6_metasprite1[], Tetromino6_metasprite2[], Tetromino6_metasprite3[];
extern const metasprite_t Tetromino7_metasprite0[], Tetromino7_metasprite1[], Tetromino7_metasprite2[], Tetromino7_metasprite3[];

const metasprite_t* const Tetrominos_metasprites[28] = {
    Tetromino1_metasprite0,Tetromino1_metasprite1,Tetromino1_metasprite2,Tetromino1_metasprite3,
    Tetromino2_metasprite0,Tetromino2_metasprite1,Tetromino2_metasprite2,Tetromino2_metasprite3,
    Tetromino3_metasprite0,Tetromino3_metasprite1,Tetromino3_metasprite2,Tetromino3_metasprite3,
    Tetromino4_metasprite0,Tetromino4_metasprite1,Tetromino4_metasprite2,Tetromino4_metasprite3,
    Tetromino5_metasprite0,Tetromino5_metasprite1,Tetromino5_metasprite2,Tetromino5_metasprite3,
    Tetromino6_metasprite0,Tetromino6_metasprite1,Tetromino6_metasprite2,Tetromino6_metasprite3,
    Tetromino7_metasprite0,Tetromino7_metasprite1,Tetromino7_metasprite2,Tetromino7_metasprite3
};

const uint8_t tileOffsets[]={
    0,
    Tetromino1_TILE_COUNT,
    Tetromino1_TILE_COUNT+Tetromino2_TILE_COUNT,
    Tetromino1_TILE_COUNT+Tetromino2_TILE_COUNT+Tetromino3_TILE_COUNT,
    Tetromino1_TILE_COUNT+Tetromino2_TILE_COUNT+Tetromino3_TILE_COUNT+Tetromino4_TILE_COUNT,
    Tetromino1_TILE_COUNT+Tetromino2_TILE_COUNT+Tetromino3_TILE_COUNT+Tetromino4_TILE_COUNT+Tetromino5_TILE_COUNT,
    Tetromino1_TILE_COUNT+Tetromino2_TILE_COUNT+Tetromino3_TILE_COUNT+Tetromino4_TILE_COUNT+Tetromino5_TILE_COUNT+Tetromino6_TILE_COUNT,
    Tetromino1_TILE_COUNT+Tetromino2_TILE_COUNT+Tetromino3_TILE_COUNT+Tetromino4_TILE_COUNT+Tetromino5_TILE_COUNT+Tetromino6_TILE_COUNT+Tetromino7_TILE_COUNT
};

#define USERINTERFACE_TILE_START tileOffsets[7]
#define TILEANIMATION_TILE1_VRAM USERINTERFACE_TILE_START+UserInterface_TILE_COUNT
#define TILEANIMATION_TILE2_VRAM USERINTERFACE_TILE_START+UserInterface_TILE_COUNT+1
#define NUMBERS_TILES_START TILEANIMATION_TILE2_VRAM+1

#define CURRENT_TETROMINO TETROMINOS[currentTetromino][currentTetrominoRotation]

uint8_t tileAnimationCounter=0;


const uint8_t TETROMINOS[6][4][4][4] = {
     { 
         //Square Block
        {{0, 0, 0, 0}, 
        {0, 0, 0, 0}, 
        {1, 1, 0, 0}, 
        {1, 1, 0, 0}},

        {{0, 0, 0, 0}, 
        {0, 0, 0, 0}, 
        {1, 1, 0, 0}, 
        {1, 1, 0, 0}},

        {{0, 0, 0, 0}, 
        {0, 0, 0, 0}, 
        {1, 1, 0, 0}, 
        {1, 1, 0, 0}},

        {{0, 0, 0, 0}, 
        {0, 0, 0, 0}, 
        {1, 1, 0, 0}, 
        {1, 1, 0, 0}}
    },
    { // Line Piece
        {{0,9, 0, 0}, 
        {0, 10, 0, 0}, 
        {0, 10, 0, 0}, 
        {0, 11, 0, 0}},

        {{0, 0, 0, 0}, 
        {0, 0, 0, 0}, 
        {6, 7, 7, 8}, 
        {0, 0, 0, 0}},

        {{0, 0,9, 0}, 
        {0, 0,10, 0}, 
        {0, 0,10, 0}, 
        {0, 0, 11, 0}},

        {{0, 0, 0, 0}, 
        {6, 7, 7, 8}, 
        {0, 0, 0, 0}, 
        {0, 0, 0, 0}}
    },
    { // L Piece
        {{0, 0, 0, 0}, 
        {0, 4, 4, 0}, 
        {0, 0, 4, 0}, 
        {0, 0, 4, 0}},

        {{0, 0, 0, 0}, 
        {0, 0, 4, 0},
        {4, 4, 4, 0},
        {0, 0, 0, 0}},

        {{0, 4, 0, 0},
        {0, 4, 0, 0},
        {0, 4, 4, 0},
        {0, 0, 0, 0}},

        {{0, 0, 0, 0},
        {0, 4, 4, 4},
        {0, 4, 0, 0},
        {0, 0, 0, 0}}
    },
    { // Reverse L
        {{0, 0, 0, 0}, 
        {0, 12, 12, 0}, 
        {0, 12, 0, 0},
        {0, 12, 0, 0}},

        {{0, 0, 0, 0},
        {12, 12, 12, 0},
        {00, 00, 12, 0},
        {00, 0, 0, 0}},

        {{0, 0, 0, 0},
        {0, 0, 12, 0},
        {0, 0, 12, 0},
        {0, 12, 12, 0}},

        {{0, 0, 0, 0},
        {12, 0, 0, 0},
        {12, 12, 12, 0},
        {0, 0, 0, 0}}
    },
    { // S Piece
        {{0, 0, 0, 0},
        {0, 3, 0, 0},
        {0, 3, 3, 0}, 
        {0, 0, 3, 0}},

        {{0, 0, 0, 0}, 
        {0, 3, 3, 0}, 
        {3, 3, 0, 0}, 
        {0, 0, 0, 0}},

        {{0, 0, 0, 0}, 
        {0, 3, 0, 0}, 
        {0, 3, 3, 0}, 
        {0, 0, 3, 0}},

        {{0, 0, 0, 0}, 
        {0, 3, 3, 0}, 
        {3, 3, 0, 0}, 
        {0, 0, 0, 0}}
    },
    { // Reverse S Piece
        {{0, 0, 0, 0}, 
        {0, 0, 2, 0}, 
        {0, 2, 2, 0}, 
        {0, 2, 0, 0}},

        {{0, 0, 0, 0}, 
        {2, 2, 0, 0}, 
        {0, 2, 2, 0}, 
        {0, 0, 0, 0}},

        {{0, 0, 0, 0}, 
        {0, 0, 2, 0}, 
        {0, 2, 2, 0}, 
        {0, 2, 0, 0}},

        {{0, 0, 0, 0}, 
        {2, 2, 0, 0}, 
        {0, 2, 2, 0}, 
        {0, 0, 0, 0}}
    }
};

uint8_t fallTimer = 0, isBlinking = 0;
uint8_t currentTetromino = 0,nextCurrentTetromino=0;
uint8_t currentTetrominoRotation = 0,nextCurrentTetrominoRotation=0;
uint8_t joypadCurrent, joypadPrevious;
uint8_t currentX, currentY;

uint16_t score;

uint8_t clearRows[4];
uint8_t lines=0;
uint8_t level=1;

unsigned char reusableRow10[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const unsigned char blinkRow10[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

uint8_t blankTile=0,blankTilePalette=0;


uint8_t IsRowFullBoth(uint8_t j,uint8_t both){

    // Return 0 if any items in the row are zero
    for (uint8_t i = 0; i < 10; i++){
        if(both){
            if (get_bkg_tile_xy(2+i,j) == blankTile&&get_win_tile_xy(2+i,j) == blankTile)return 0;
        }else if (get_bkg_tile_xy(2+i,j) == blankTile)return 0;
    }

    // None of the items were zero
    return 1;
}

uint8_t IsRowFull(uint8_t j){

    return IsRowFullBoth(j,FALSE);
}
void ShiftAllTilesDown(uint8_t j)
{
    // set the top row to be mpty
    VBK_REG=1; fill_bkg_rect(2,j,10,1,blankTilePalette);
    VBK_REG=0; fill_bkg_rect(2,j,10,1,blankTile);

    // From the given row up
    for (uint8_t j2 = j-1; j2 !=255; j2--){
        
        // Move all rows downward
        VBK_REG=1; get_bkg_tiles(2, j2,10,1,&reusableRow10[0]); set_bkg_tiles(2, j2+1, 10, 1, &reusableRow10[0]);
        VBK_REG=0; get_bkg_tiles(2, j2,10,1,&reusableRow10[0]); set_bkg_tiles(2, j2+1, 10, 1, &reusableRow10[0]);
    }
}

uint8_t CanPieceBePlacedHere(uint8_t piece, uint8_t rotation, uint8_t column, uint8_t row){

    metasprite_t *metasprite = Tetrominos_metasprites[piece*4+rotation];

    // Offset by 1 colum and 2 rows for the -8 x-16 sprite offset
    uint8_t finalColumn=column;
    uint8_t finalRow=row;

    uint8_t i=0;

    while(i<4){

        finalColumn += metasprite->dx/8;
        finalRow += metasprite->dy/8;

        
        uint8_t overlap = finalRow>25;
        
        // If this square would be below the bottom, a piece cannot be placed here
        /// Or if the background element here isn't empty, a piece cannot be placed here
        if(finalRow-2>=18&&!overlap)return 0;
        if(get_bkg_tile_xy(finalColumn-1,finalRow-2)!=blankTile&&!overlap)return 0;

        metasprite++;
        i++;
    }


    return 1;
}

void HandleInput(){

    joypadPrevious = joypadCurrent;
    joypadCurrent = joypad();

    // Fall faster when down is held
    if (joypadCurrent & J_DOWN){
        fallTimer += 5;
    }

    // Was the left button A pressed
    if ((joypadCurrent & J_A) && !(joypadPrevious & J_A))
    {
        // check if our next rotation can be placed here
        if(CanPieceBePlacedHere(currentTetromino,(currentTetrominoRotation+1)%4,currentX,currentY)){
            
            currentTetrominoRotation=(currentTetrominoRotation+1)%4;            
        }else if(CanPieceBePlacedHere(currentTetromino,(currentTetrominoRotation+1)%4,currentX+1,currentY)){
            
            currentTetrominoRotation=(currentTetrominoRotation+1)%4;    
            currentX++;        
        }else if(CanPieceBePlacedHere(currentTetromino,(currentTetrominoRotation+1)%4,currentX-1,currentY)){
            
            currentTetrominoRotation=(currentTetrominoRotation+1)%4;    
            currentX--;        
        }
    }

    // Was the left button JUST pressed
    if ((joypadCurrent & J_LEFT) && !(joypadPrevious & J_LEFT))
    {
        // check if our tetromino can be placed one position to the left
        if(CanPieceBePlacedHere(currentTetromino,currentTetrominoRotation,currentX-1,currentY)){
            currentX--;
        }
    }
    
    // Was the right button JUST pressed
    if ((joypadCurrent & J_RIGHT) && !(joypadPrevious & J_RIGHT))
    {
        // check if our tetromino can be placed one position to the right
         if(CanPieceBePlacedHere(currentTetromino,currentTetrominoRotation,currentX+1,currentY)){
            currentX++;
        }
    }
}

void SetBlockSpritePositions(){

    // For each square in our current tetromino
    for (uint8_t i = 0; i < 4; i++){
        for (uint8_t j = 0; j < 4; j++){

            // Set sprite 0-15 to equal the value defined
            set_sprite_tile(i*4+j,CURRENT_TETROMINO[j][i]);

            // If the value isn't zero
            if (CURRENT_TETROMINO[j][i] != 0){

                // Show normally
                // Move over +8, and +16 because of 'move_sprite' internal offset
                move_sprite(i * 4 + j, (currentX + i) * 8 + 8, (currentY + j) * 8 + 16);
            }else{

                // Position the sprite offscreen, so it's not visible
                move_sprite(i * 4 + j, 160, 160);
            }
        }
    }
}

void SetCurrentPieceInBackground(){
    
     
    metasprite_t *metasprite = Tetrominos_metasprites[currentTetromino*4+currentTetrominoRotation];

    uint8_t finalColumn=currentX;
    uint8_t finalRow=currentY;

    uint8_t i=0;

    while(i<4){

        finalColumn += metasprite->dx/8;
        finalRow += metasprite->dy/8;

        // Set it in the background
        // Offset by 1 colum and 2 rows for the -8 x-16 sprite offset
        VBK_REG=1;set_bkg_tile_xy(finalColumn-1, finalRow-2, metasprite->props);
        VBK_REG=0;set_bkg_tile_xy(finalColumn-1, finalRow-2, metasprite->dtile+tileOffsets[currentTetromino]);

        metasprite++;
        i++;
    }

}

uint8_t PickNewShape(){

    // Can the next tetromino be placed at it's default spot?
    if(CanPieceBePlacedHere(nextCurrentTetromino,nextCurrentTetrominoRotation,5,1)){

        currentX = 5;
        currentY = 1;
        currentTetromino=nextCurrentTetromino;
        currentTetrominoRotation=nextCurrentTetrominoRotation;

        // Decide the next tetromino
        nextCurrentTetromino = RandomNumber(0, 6) % 6;
        nextCurrentTetrominoRotation=RandomNumber(0, 4) % 4;

        return 1;
    }

    return 0;
}

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

void BlinkFullRows(){

    isBlinking=FALSE;
    
    // Move all sprites off screen for the blinking
    // So the last placed tile doesn't cover some o it up
    for (uint8_t i = 0; i < 16; i++){
        move_sprite(i,160,160);
    }

    int8_t j=0;
    
    for ( j = 17; j >=0; j--)
    {
        // The 'IsRowFull' unction checks the background tiles, which may be set to empty for the flashing
        // Check of our index is in the 'clearRows' variable.
        if (IsRowFull(j)){

            isBlinking=TRUE;

            lines++;
            IncreaseScore(100);
            
            // Copy from the background to the window
            // The window will be our "buffer"
            VBK_REG=1;get_bkg_tiles(2,j,10,1,reusableRow10); set_win_tiles(2,j,10,1,reusableRow10);
            VBK_REG=0; get_bkg_tiles(2,j,10,1,reusableRow10); set_win_tiles(2,j,10,1,reusableRow10);
        }
    }

    if(isBlinking){

        // Flash 8 times
        // This should be an even number to make sure things get set right back how they were
        for(uint8_t k=0;k<8;k++){      

            // From the bottom to the top
            for ( j = 17; j >=0; j--)
            {
                // We need to check both the window and background
                // Since the background will be blank every other iteration of the k for-loop
                if (IsRowFullBoth(j,TRUE)){

                    if(k%2==0){

                        // Fill with blank
                        VBK_REG=1;fill_bkg_rect(2,j,10,1,blankTilePalette);
                        VBK_REG=0;fill_bkg_rect(2,j,10,1,blankTile);
                    }else{
                
                        // Copy from the window to the background
                        VBK_REG=1;get_win_tiles(2,j,10,1,reusableRow10); set_bkg_tiles(2,j,10,1,reusableRow10);
                        VBK_REG=0;get_win_tiles(2,j,10,1,reusableRow10); set_bkg_tiles(2,j,10,1,reusableRow10);
                    }
                }
            }


            for(uint8_t n=0;n<20;n++){
                AnimateBackground();
                wait_vbl_done();
            }
        }
        

        // Fill our full window layers with blank
        VBK_REG=1; fill_win_rect(0,0,31,31,blankTilePalette);
        VBK_REG=0; fill_win_rect(0,0,31,31,blankTile);
    }
}

void AnimateBackground(){
     tileAnimationCounter+=5;
    if(tileAnimationCounter>=128)tileAnimationCounter=0;
    set_bkg_data(TILEANIMATION_TILE1_VRAM, 1, TileAnimation_tiles+(tileAnimationCounter>>4)*16);
    set_bkg_data(TILEANIMATION_TILE2_VRAM, 1, TileAnimation_tiles+128+(tileAnimationCounter>>4)*16);
}

void main(void)
{

    DISPLAY_ON;
    SHOW_BKG;
    SHOW_SPRITES;

    GameplayStart:

    set_sprite_data(tileOffsets[0], Tetromino1_TILE_COUNT, Tetromino1_tiles);
    set_sprite_data(tileOffsets[1], Tetromino2_TILE_COUNT, Tetromino2_tiles);
    set_sprite_data(tileOffsets[2], Tetromino3_TILE_COUNT, Tetromino3_tiles);
    set_sprite_data(tileOffsets[3], Tetromino4_TILE_COUNT, Tetromino4_tiles);
    set_sprite_data(tileOffsets[4], Tetromino5_TILE_COUNT, Tetromino5_tiles);
    set_sprite_data(tileOffsets[5], Tetromino6_TILE_COUNT, Tetromino6_tiles);
    set_sprite_data(tileOffsets[6], Tetromino7_TILE_COUNT, Tetromino7_tiles);

    set_bkg_data(tileOffsets[0], Tetromino1_TILE_COUNT, Tetromino1_tiles);
    set_bkg_data(tileOffsets[1], Tetromino2_TILE_COUNT, Tetromino2_tiles);
    set_bkg_data(tileOffsets[2], Tetromino3_TILE_COUNT, Tetromino3_tiles);
    set_bkg_data(tileOffsets[3], Tetromino4_TILE_COUNT, Tetromino4_tiles);
    set_bkg_data(tileOffsets[4], Tetromino5_TILE_COUNT, Tetromino5_tiles);
    set_bkg_data(tileOffsets[5], Tetromino6_TILE_COUNT, Tetromino6_tiles);
    set_bkg_data(tileOffsets[6], Tetromino7_TILE_COUNT, Tetromino7_tiles);

    set_bkg_data(USERINTERFACE_TILE_START, UserInterface_TILE_COUNT, UserInterface_tiles);
    set_bkg_data(TILEANIMATION_TILE1_VRAM, 1, TileAnimation_tiles);
    set_bkg_data(TILEANIMATION_TILE2_VRAM, 1, TileAnimation_tiles+128);
    set_bkg_data(NUMBERS_TILES_START, Numbers_TILE_COUNT, Numbers_tiles);

    set_bkg_palette(0,8,Palette_palettes);
    set_sprite_palette(0,8,Palette_palettes);

    // Reset our whole screen
    // Reset the 4 helper rows we use for blinking
    VBK_REG=1; set_bkg_tiles(0,0,20,18,UserInterface_map_attributes);
    VBK_REG=0; set_bkg_based_tiles(0,0,20,18,UserInterface_map,USERINTERFACE_TILE_START);

    
    VBK_REG=1;uint8_t tileAnimationBasePalette = get_bkg_tile_xy(0,0);
    VBK_REG=0;uint8_t tileAnimationBase = get_bkg_tile_xy(0,0);

    // SAve which tile is considred blank
    // For easy comparison
    VBK_REG=1; blankTilePalette=get_bkg_tile_xy(3,3);
    VBK_REG=0; blankTile=get_bkg_tile_xy(3,3);

    // Fill our full window layers with blank
    VBK_REG=1; fill_win_rect(0,0,31,31,blankTilePalette);
    VBK_REG=0; fill_win_rect(0,0,31,31,blankTile);

    // Fill in everything else outside of the scren with our blank tiles
    VBK_REG=1;fill_bkg_rect(0,18,31,14,tileAnimationBasePalette);fill_bkg_rect(20,0,12,31,tileAnimationBasePalette);
    VBK_REG=0;fill_bkg_rect(0,18,31,14,tileAnimationBase); fill_bkg_rect(20,0,12,31,tileAnimationBase);

    uint8_t animatedTile1 = TILEANIMATION_TILE1_VRAM;
    uint8_t animatedTile2 = TILEANIMATION_TILE2_VRAM;

    for(uint16_t i=0;i<32;i++){
        for(uint16_t j=0;j<32;j++){
            if(get_bkg_tile_xy(i,j)==tileAnimationBase){
                if(j%2==0){
                    if(i%2==0)set_bkg_tile_xy(i,j,animatedTile1);
                    else set_bkg_tile_xy(i,j,animatedTile2);
                }else{
                     if(i%2==0)set_bkg_tile_xy(i,j,animatedTile2);
                    else set_bkg_tile_xy(i,j,animatedTile1);
                }
            }
        }
    }

    // Reset all sprites
    for (uint8_t i = 0; i < 16; i++){
        set_sprite_tile(i, 0);
        move_sprite(i,160,160);
    }

    // Reset gameplay variables

    nextCurrentTetromino = RandomNumber(0, 6) % 6;
    nextCurrentTetrominoRotation=RandomNumber(0, 4) % 4;
    joypadCurrent = 0;
    joypadPrevious = 0;
    fallTimer = 0;
    lines=0;
    level=1;
    score=0;

    GameplayLoop:

    // Try to pick a new shape
    // If we can't go to game start
    if(!PickNewShape()){
        goto GameplayStart;
    }

    UpdateGui();


    // Loop
    while (1)
    {

       AnimateBackground();

        fallTimer++;

        // If our timer is up
        if (fallTimer >= 30)
        {
            // If the piece cannot move down
            if(!CanPieceBePlacedHere(currentTetromino,currentTetrominoRotation,currentX,currentY+1)){

                // Break out of the loop,
                break;
            
            // Otherwise, if the piece can be moved down
            }else{

                // Move the piece down
                // Reset our timer
                currentY++;
                fallTimer = 0;
            }

        }

        HandleInput();

        move_metasprite(Tetrominos_metasprites[currentTetromino*4+currentTetrominoRotation],tileOffsets[currentTetromino],0,currentX*8,currentY*8);
        
        // Wait for a vertical blank to finish
        wait_vbl_done();

    }

    SetPiece:

    // Increase the score
    // Set the piece into the background
    IncreaseScore(5);
    SetCurrentPieceInBackground();

    Blink:

    BlinkFullRows();

    ShiftTiles:

    for (uint8_t j = 17; j != 255; j--)
    {
        // While this row is full
        while (IsRowFull(j)){
            
            // Shift all above rows down
            ShiftAllTilesDown(j);
        }
    }

    goto GameplayLoop;
}