CC = gcc
GHC = ghc
CFLAGS = -Wall
DEL = rm # o del

.PHONY: all benchmark clean

all: remove_goto remove_hs

remove_goto: RemoveComments.c
	$(CC) $(CFLAGS) -o RemoveComments_goto RemoveComments.c

remove_hs: RemoveComments.hs
	$(GHC) -o RemoveComments_hs RemoveComments.hs

No_Comentarios:
	./RemoveComments_goto < Test.c > NoComments_goto.c
	./RemoveComments_hs   < Test.c > NoComments_hs.c

clean:
	$(DEL) RemoveComments_goto RemoveComments_hs NoComments_goto.c NoComments_hs.c *.o *.hi
