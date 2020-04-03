PN=main

CFLAGS=-Wall -Iproduct -I../Unity -Itest

#add your own other c files here
SHARED=	src/Adidas.c \
		src/FileManager.c

all: 
	gcc $(CFLAGS) src/$(PN).c $(SHARED) -o build/$(PN)
   
clean:
	del build/$(PN).exe

.PHONY: clean all
