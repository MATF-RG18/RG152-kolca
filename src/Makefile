PROGRAM = projekat
CC      = gcc
CFLAGS  = -g -ansi -Wall -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL -lm -Wall

$(PROGRAM): main.o prepreke.o model_autica.o kolizije.o helti.o tekstura.o image.o svetlo.o mapa.o
	$(CC) $(LDFLAGS) -o $(PROGRAM) $^ $(LDLIBS)

helti.o: helti.c helti.h
	$(CC) $(LDFLAGS) -c -o $@ $< $(LDLIBS)

main.o: main.c prepreke.h model_autica.h kolizije.h
	$(CC) $(LDFLAGS) -c -o $@ $< $(LDLIBS)

kolizije.o: kolizije.c kolizije.h prepreke.h model_autica.h
	$(CC) $(LDFLAGS) -c -o $@ $< $(LDLIBS)

mapa.o: mapa.c prepreke.h tekstura.h
	$(CC) $(LDFLAGS) -c -o $@ $< $(LDLIBS)

prepreke.o: prepreke.c prepreke.h model_autica.h
	$(CC) $(LDFLAGS) -c -o $@ $< $(LDLIBS)

model_autica.o: model_autica.c model_autica.h svetlo.h
	$(CC) $(LDFLAGS) -c -o $@ $< $(LDLIBS)

tekstura.o: tekstura.c tekstura.h
	$(CC) $(LDFLAGS) -c -o $@ $< $(LDLIBS)

image.o: image.c image.h
	$(CC) $(LDFLAGS) -c -o $@ $< $(LDLIBS)

svetlo.o: svetlo.c svetlo.h
	$(CC) $(LDFLAGS) -c -o $@ $< $(LDLIBS)

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM)

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)