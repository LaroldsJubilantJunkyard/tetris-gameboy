#include <gb/gb.h>
#include <gb/metasprites.h>
#include "Tetrominos.h"
#include "common.h"
#include "graphics/Tetromino1.h"
#include "graphics/Tetromino2.h"
#include "graphics/Tetromino3.h"
#include "graphics/Tetromino4.h"
#include "graphics/Tetromino5.h"
#include "graphics/Tetromino6.h"
#include "graphics/Tetromino7.h"


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

uint8_t CanPieceBePlacedHere(uint8_t piece, uint8_t rotation, uint8_t column, uint8_t row){

    metasprite_t *metasprite = Tetrominos_metasprites[piece*4+rotation];

    // Offset by 1 colum and 2 rows for the -8 x-16 sprite offset
    int8_t finalColumn=column;
    int8_t finalRow=row;

    uint8_t i=0;

    while(i<4){

        finalColumn += metasprite->dx/8;
        finalRow += metasprite->dy/8;
        
        // If this square would be below the bottom, a piece cannot be placed here
        /// Or if the background element here isn't empty, a piece cannot be placed here
        if(finalRow-2>=18)return 0;

        // Check our values to make sure the numer doesn't wrap around
        if(finalColumn>=1&&finalRow>=2){
            if(get_bkg_tile_xy(finalColumn-1,finalRow-2)!=blankTile)return 0;
        }

        metasprite++;
        i++;
    }


    return 1;
}

uint8_t PickNewTetromino(){

    // Do we not have a current tetromino?
    // Can the next tetromino be placed at it's default spot?
    if(CanPieceBePlacedHere(nextCurrentTetromino,nextCurrentTetrominoRotation,5,0)){

        currentX = 5;
        currentY = 0;
        currentTetromino=nextCurrentTetromino;
        currentTetrominoRotation=nextCurrentTetrominoRotation;

        // Decide the next tetromino
        nextCurrentTetromino = RandomNumber(0, 7) % 7;
        nextCurrentTetrominoRotation=RandomNumber(0, 4) % 4;

        return 1;
    }

    return 0;
}
