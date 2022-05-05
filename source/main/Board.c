#include <gb/gb.h>
#include <gb/metasprites.h>
#include "common.h"
#include "hud.h"
#include "Tetrominos.h"

uint8_t IsRowFull(uint8_t j,uint8_t both){

    // Return 0 if any items in the row are zero
    for (uint8_t i = 0; i < 10; i++){

        // Should we check the window AND the background
        if(both){
            if (get_bkg_tile_xy(2+i,j) == blankTile&&get_win_tile_xy(2+i,j) == blankTile)return 0;

        //Normally, just heck the background
        }else if (get_bkg_tile_xy(2+i,j) == blankTile)return 0;
    }

    // None of the items were zero
    return 1;
}


void ShiftAllTilesAboveThisRowDown(uint8_t j)
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

void ShiftAllTilesDown(){
    for (uint8_t j = 17; j != 255; j--)
    {
        // While this row is full
        while (IsRowFull(j,FALSE)){
            
            // Shift all above rows down
            ShiftAllTilesAboveThisRowDown(j);
        }
    }
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
        if (IsRowFull(j,FALSE)){

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
                if (IsRowFull(j,TRUE)){

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
