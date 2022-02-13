#include <gb/gb.h>
#include <gb/metasprites.h>

extern const metasprite_t Tetromino1_metasprite0[], Tetromino1_metasprite1[], Tetromino1_metasprite2[], Tetromino1_metasprite3[];
extern const metasprite_t Tetromino2_metasprite0[], Tetromino2_metasprite1[], Tetromino2_metasprite2[], Tetromino2_metasprite3[];
extern const metasprite_t Tetromino3_metasprite0[], Tetromino3_metasprite1[], Tetromino3_metasprite2[], Tetromino3_metasprite3[];
extern const metasprite_t Tetromino4_metasprite0[], Tetromino4_metasprite1[], Tetromino4_metasprite2[], Tetromino4_metasprite3[];
extern const metasprite_t Tetromino5_metasprite0[], Tetromino5_metasprite1[], Tetromino5_metasprite2[], Tetromino5_metasprite3[];
extern const metasprite_t Tetromino6_metasprite0[], Tetromino6_metasprite1[], Tetromino6_metasprite2[], Tetromino6_metasprite3[];
extern const metasprite_t Tetromino7_metasprite0[], Tetromino7_metasprite1[], Tetromino7_metasprite2[], Tetromino7_metasprite3[];

extern const metasprite_t* const Tetrominos_metasprites[28];
extern const uint8_t tileOffsets[];

#define TILEANIMATION_TILE1_VRAM USERINTERFACE_TILE_START+UserInterface_TILE_COUNT
#define TILEANIMATION_TILE2_VRAM USERINTERFACE_TILE_START+UserInterface_TILE_COUNT+1


uint8_t PickNewTetromino();
uint8_t CanPieceBePlacedHere(uint8_t piece, uint8_t rotation, uint8_t column, uint8_t row);