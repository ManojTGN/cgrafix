
CC = gcc
CFLAGS = -lgdi32 -lfreetype 
BINS = grafix.so grafix.a clean

all: $(BINS)

grafix.so: src/grafix.c src/shapes.c src/event.c src/time.c src/image.c src/font.c
	$(CC) $(CFLAGS) -fPIC -shared -o build/grafix.so src/grafix.c src/shapes.c src/event.c src/time.c src/image.c src/font.c $(CFLAGS) $(CINCLUDES)


grafix.a: grafix.o shapes.o event.o time.o image.o font.o
	ar rcs build/libgrafix.a build/grafix.o build/shapes.o build/event.o build/time.o build/image.o build/font.o

grafix.o: src/grafix.c 
	$(CC) -c src/grafix.c -o build/grafix.o $(CFLAGS)

shapes.o: src/shapes.c
	$(CC) -c src/shapes.c -o build/shapes.o $(CFLAGS)

event.o: src/event.c
	$(CC) -c src/event.c -o build/event.o $(CFLAGS)

time.o: src/time.c
	$(CC) -c src/time.c -o build/time.o $(CFLAGS)

image.o: src/image.c
	$(CC) -c src/image.c -o build/image.o $(CFLAGS)

font.o: src/font.c
	$(CC) -c src/font.c -o build/font.o $(CFLAGS)


clean:
	rm build/*.o $(BINS)
