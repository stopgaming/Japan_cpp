
SET PATH=C:\msys64\mingw32\bin
g++ fix_msys2.cpp -o fix_msys2.exe
del cflags.tmp
del libsflags.tmp
pkg-config --cflags --static sfml-all >> cflags.tmp
@echo -DSFML_STATIC >> cflags.tmp
pkg-config --libs --static sfml-all >> libsflags.tmp 
@echo -static -static-libgcc -static-libstdc++ >> libsflags.tmp 
fix_msys2.exe


objcopy --prefix-symbol=_ --input-target binary --output-target pe-i386 --binary-architecture i386 MontserratMedium_nRxlJ.ttf font1.o
g++ -o3 @cflags.tmp -c main.cpp -o main.o
g++ main.o font1.o @libsflags.tmp @libsflags.tmp -o Japan.exe

del fix_msys2.exe

