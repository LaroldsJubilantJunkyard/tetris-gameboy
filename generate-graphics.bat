
rmdir /s/q  "source\gen"
rmdir /s/q  "headers\gen"

mkdir "source\gen\graphics"
mkdir "headers\gen\graphics"


SET GBDK_HOME=C:/gbdk
SET PNG2ASSET=%GBDK_HOME%/bin/png2asset.exe

:: Tetrominos
%PNG2ASSET% graphics\Tetromino1.png -c source\gen\graphics\Tetromino1.c -px 0 -py 0 -sx 0 -sy 0 -sw 32 -sh 32 -spr8x8 -keep_palette_order -noflip
%PNG2ASSET% graphics\Tetromino2.png -c source\gen\graphics\Tetromino2.c -px 0 -py 0 -sx 0 -sy 0 -sw 32 -sh 32 -spr8x8 -keep_palette_order -noflip
%PNG2ASSET% graphics\Tetromino3.png -c source\gen\graphics\Tetromino3.c -px 0 -py 0 -sx 0 -sy 0 -sw 32 -sh 32 -spr8x8 -keep_palette_order -noflip
%PNG2ASSET% graphics\Tetromino4.png -c source\gen\graphics\Tetromino4.c -px 0 -py 0 -sx 0 -sy 0 -sw 32 -sh 32 -spr8x8 -keep_palette_order -noflip
%PNG2ASSET% graphics\Tetromino5.png -c source\gen\graphics\Tetromino5.c -px 0 -py 0 -sx 0 -sy 0 -sw 32 -sh 32 -spr8x8 -keep_palette_order -noflip
%PNG2ASSET% graphics\Tetromino6.png -c source\gen\graphics\Tetromino6.c -px 0 -py 0 -sx 0 -sy 0 -sw 32 -sh 32 -spr8x8 -keep_palette_order -noflip
%PNG2ASSET% graphics\Tetromino7.png -c source\gen\graphics\Tetromino7.c -px 0 -py 0 -sx 0 -sy 0 -sw 32 -sh 32 -spr8x8 -keep_palette_order -noflip

:: Backgrounds & Maps
%PNG2ASSET% graphics\UserInterface.png -c source\gen\graphics\UserInterface.c -map -use_map_attributes  -keep_palette_order -noflip
%PNG2ASSET% graphics\Palette.png -c source\gen\graphics\Palette.c -map -use_map_attributes  -keep_palette_order -noflip
%PNG2ASSET% graphics\TileAnimation.png -c source\gen\graphics\TileAnimation.c -map -use_map_attributes  -keep_palette_order -noflip
%PNG2ASSET% graphics\Numbers.png -c source\gen\graphics\Numbers.c -map -use_map_attributes  -keep_palette_order -noflip


:: move .h files to their proper location
FOR /R "source/gen/graphics/" %%X IN (*.h) DO (
    move "%%X" "%cd%/headers/gen/graphics/"
)