#include <gb/gb.h>
#include <gb/metasprites.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "hud.h"
#include "UserInterface.h"
#include "board.h"
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
#include "graphics/Palette.h"
#include "graphics/Numbers.h"
#include "hUGEDriver.h"

extern const hUGESong_t tetris_music;


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


void SetupVRAM(){
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
}

void SetupGameplay(){
    
    // Fill our full window layers with blank
    VBK_REG=1; fill_win_rect(0,0,31,31,blankTilePalette);
    VBK_REG=0; fill_win_rect(0,0,31,31,blankTile);

    // Fill our board with blank tiles
    VBK_REG=1; fill_bkg_rect(2,0,10,18,blankTilePalette);
    VBK_REG=0; fill_bkg_rect(2,0,10,18,blankTile);

    ResetAllSprites();

    // Decide the next tetromino
    nextCurrentTetromino = RandomNumber(0, 7) % 7;
    nextCurrentTetrominoRotation=RandomNumber(0, 4) % 4;

    PickNewTetromino();

    fallTimer = 0;
    lines=0;
    level=1;
    score=0;

    UpdateGui();
}

void main(void)
{

    DISPLAY_ON;
    SHOW_BKG;
    SHOW_SPRITES;

    SetupVRAM();
    SetupUserInterface();

    NR52_REG = 0x80;
    NR51_REG = 0xFF;
    NR50_REG = 0x77;

    __critical {
        hUGE_init(&tetris_music);
        add_VBL(hUGE_dosound);
    }

    GameplayStart:

    SetupGameplay();    

    // Loop
    while (1)
    {
        // If we don't have a current tetromino
        if(currentTetromino==255){

            uint8_t canSpawnNewShape = PickNewTetromino();

            // Try to pick a new shape
            // If we can't go to game start
            if(!canSpawnNewShape){
                goto GameplayStart;
            }else{
                
                UpdateGui();
            }
        }



       AnimateBackground();

        fallTimer++;

        // If our timer is up
        if (fallTimer >= 30)
        {
            // If the piece cannot move down
            if(!CanPieceBePlacedHere(currentTetromino,currentTetrominoRotation,currentX,currentY+1)){


                // Increase the score
                IncreaseScore(5);

                // Transition the tiles from the tetromino sprite to thebackground
                SetCurrentPieceInBackground();

                // BLink any/all rows that are full
                BlinkFullRows();

                // Shift all tiles down from removed rows
                ShiftAllTilesDown();
                
                // Hide the current tetromino
                hide_metasprite(Tetrominos_metasprites[currentTetromino*4+currentTetrominoRotation],0);

                currentTetromino=255;
            
            // Otherwise, if the piece can be moved down
            }else{

                // Move the piece down
                // Reset our timer
                currentY++;
                fallTimer = 0;
            }

        }

        if(currentTetromino!=255){

            // Handle user input
            HandleInput();

            // Show the current tetromino at the proper position
            move_metasprite(Tetrominos_metasprites[currentTetromino*4+currentTetrominoRotation],tileOffsets[currentTetromino],0,currentX*8,currentY*8);

        }
        
        // Wait for a vertical blank to finish
        wait_vbl_done();

    }


}