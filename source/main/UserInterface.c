#include <gb/gb.h>
#include <gb/metasprites.h>
#include "common.h"
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

void SetupAnimatedBackground(){

    // For the entire background layer
    for(uint16_t i=0;i<32;i++){
        for(uint16_t j=0;j<32;j++){

            // We are going to manually place our animating tile
            // Our graphic has a basic green tile everywhere that we should have our animating tile
            // If this tile is that basic green tile
            if(get_bkg_tile_xy(i,j)==tileAnimationBase){

                // If our row is even
                if(j%2==0){

                    // Alternate starting with tile 1 if it's even
                    // If it's odd, Alternate starting with tile 2
                    if(i%2==0)set_bkg_tile_xy(i,j,TILEANIMATION_TILE1_VRAM);
                    else set_bkg_tile_xy(i,j,TILEANIMATION_TILE2_VRAM);
                }else{
                    // Alternate starting with tile 2 if it's even
                    // If it's odd, Alternate starting with tile 1
                     if(i%2==0)set_bkg_tile_xy(i,j,TILEANIMATION_TILE2_VRAM);
                    else set_bkg_tile_xy(i,j,TILEANIMATION_TILE1_VRAM);
                }
            }
        }
    }
}

void SetupUserInterface(){

     // Reset our whole screen
    // Reset the 4 helper rows we use for blinking
    VBK_REG=1; set_bkg_tiles(0,0,20,18,UserInterface_map_attributes);
    VBK_REG=0; set_bkg_based_tiles(0,0,20,18,UserInterface_map,USERINTERFACE_TILE_START);
    
    VBK_REG=1; tileAnimationBasePalette = get_bkg_tile_xy(0,0);
    VBK_REG=0; tileAnimationBase = get_bkg_tile_xy(0,0);

    // SAve which tile is considred blank
    // For easy comparison
    VBK_REG=1; blankTilePalette=get_bkg_tile_xy(3,3);
    VBK_REG=0; blankTile=get_bkg_tile_xy(3,3);

    // Fill in everything else outside of the scren with our blank tiles
    VBK_REG=1;fill_bkg_rect(0,18,31,14,tileAnimationBasePalette);fill_bkg_rect(20,0,12,31,tileAnimationBasePalette);
    VBK_REG=0;fill_bkg_rect(0,18,31,14,tileAnimationBase); fill_bkg_rect(20,0,12,31,tileAnimationBase);

    SetupAnimatedBackground();
}


void AnimateBackground(){
    tileAnimationCounter+=6;
    if(tileAnimationCounter>=128)tileAnimationCounter=0;
    set_bkg_data(TILEANIMATION_TILE1_VRAM, 1, TileAnimation_tiles+(tileAnimationCounter>>4)*16);
    set_bkg_data(TILEANIMATION_TILE2_VRAM, 1, TileAnimation_tiles+128+(tileAnimationCounter>>4)*16);
}

