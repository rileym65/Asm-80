PROJECT=asm80
CC=gcc
DEFS=
INDIR=
INCS=
LIBDIR=
LIBS=
OBJS=\
	main.o

$(PROJECT): $(OBJS)
	$(CC) $(DEFS) $(LIBDIR) $(OBJS) $(LIBS) -o $(PROJECT)

.c.o:
	$(CC) $(DEFS) $(INCDIR) $(INCS) -c $<

clean:
	-rm *.o
	-rm $(PROJECT)

install:
	cp asm80 /usr/local/bin
	chmod a+x /usr/local/bin/asm80

main.o:                header.h main.c

