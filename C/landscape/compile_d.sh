
# Si compilais en linux x86/x64, teneis que quitar "-mfpu=vfp" que es la unidad de coma flotante de ARM
gcc -c -g -Wall -mfpu=vfp -O0 -o obj/dot_canvas.o dot_canvas.c
gcc -c -g -Wall -mfpu=vfp -O0 -o obj/chrono.o chrono.c
gcc -c -g -o obj/heightmap.o heightmap.s

cd obj

gcc -o ../dot_canvas.elf dot_canvas.o  heightmap.o chrono.o  -lm -lSDL 
