#include <gb/gb.h>
#include <gb/metasprites.h>



#define USERINTERFACE_TILE_START tileOffsets[7]
#define NUMBERS_TILES_START TILEANIMATION_TILE2_VRAM+1

extern uint16_t score, lines;
extern uint8_t fallTimer, isBlinking, currentTetromino,nextCurrentTetromino, currentTetrominoRotation,nextCurrentTetrominoRotation, joypadCurrent, joypadPrevious, currentX, currentY;
extern uint8_t level,tileAnimationCounter, blankTile,blankTilePalette,tileAnimationBase,tileAnimationBasePalette;

extern unsigned char reusableRow10[];


uint8_t RandomNumber(uint8_t min, uint8_t max);
void ResetAllSprites();