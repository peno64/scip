rem make sure that first soplex was build

cmake -Bbuild -H. -DSOPLEX_DIR=..\soplex\build -DZLIB=off -DREADLINE=off -DGMP=off -DPAPILO=off -DZIMPL=off -DIPOPT=off
cmake --build build --config Release

rem 32-bit
cmake -A Win32 -Bbuild32 -H. -DSOPLEX_DIR=..\soplex\build32 -DZLIB=off -DREADLINE=off -DGMP=off -DPAPILO=off -DZIMPL=off -DIPOPT=off
cmake --build build32 --config Release
