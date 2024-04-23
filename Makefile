matrot: ./matrot/main.c
	gcc ./matrot/main.c -o ./build/matrot

planes: ./planes/main.c ./planes/lib/object.h ./planes/lib/object.c ./planes/lib/raster.h ./planes/lib/raster.c  ./planes/lib/color.h ./planes/lib/color.c ./planes/lib/transform.h ./planes/lib/transform.c
	gcc -ggdb ./planes/main.c ./planes/lib/object.c ./planes/lib/raster.c ./planes/lib/color.c ./planes/lib/transform.c -o ./build/planes