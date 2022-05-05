@echo off

:: Cleanup
rmdir /s /q bin
rmdir /s /q dist

:: Cleanup
mkdir bin
mkdir dist


SET GBDK_HOME=C:/gbdk

SET LCC_COMPILE_BASE=%GBDK_HOME%\bin\lcc -debug -Iheaders/main -Ilib/hUGEDriver -Iheaders/gen -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG
SET LCC_COMPILE=%LCC_COMPILE_BASE% -c -o 

:: Required to concatenate the "COMPILE_OBJECT_FILES" via a for loop
SETLOCAL ENABLEDELAYEDEXPANSION


:: Assemble the hUGEDriver source into an RGBDS object file
"lib/rgbasm.exe" -obin/hUGEDriver.obj -i.. source/asm/hUGEDriver.asm

:: Convert the RGBDS object file into a GBDK object file
"lib/rgb2sdas.exe" bin/hUGEDriver.obj





SET "COMPILE_OBJECT_FILES=bin/hUGEDriver.obj.o"

call generate-graphics.bat


:: loop for all files in the default source folder
FOR /R "source/gen/" %%X IN (*.c) DO (
    echo Compiling %%~nX ...
    %LCC_COMPILE% bin/gen_%%~nX.o %%X
    SET "COMPILE_OBJECT_FILES=bin/gen_%%~nX.o !COMPILE_OBJECT_FILES!"

)


:: loop for all files in the default source folder
FOR /R "source/main/" %%X IN (*.c) DO (
    echo Compiling %%~nX ...
    %LCC_COMPILE% bin/%%~nX.o %%X
    SET "COMPILE_OBJECT_FILES=bin/%%~nX.o !COMPILE_OBJECT_FILES!"

)


:: Compile a .gb file from the compiled .o files
%LCC_COMPILE_BASE% -Wm-yC -Wl-yt3 -Wl-yo2 -o dist/Tetris.gb !COMPILE_OBJECT_FILES!

endlocal

:: Use the romusage.exe to show the size of the ROM and what makes it up
"lib/romusage" dist\Tetris.noi -a