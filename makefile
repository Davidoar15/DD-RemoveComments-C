CC = gcc
GHC = ghc
CFLAGS = -Wall
DEL = rm # o del

.PHONY: all benchmark clean

all: remove_goto remove_recursive remove_hs

remove_goto: implementaciones/RemoveComments.c
	$(CC) $(CFLAGS) -o RemoveComments_goto implementaciones/RemoveComments.c

remove_recursive: implementaciones/RemoveCommentsRecursive.c 
	$(CC) $(CFLAGS) -o RemoveComments_recursive implementaciones/RemoveCommentsRecursive.c

remove_hs: implementaciones/RemoveComments.hs
	$(GHC) -o RemoveComments_hs implementaciones/RemoveComments.hs

No_Comentarios_C: # time funciona con git bash. Crea los archivos NoComments y muestra el tiempo de ejecucion de la instruccion
	time ./RemoveComments_goto < Test.c > NoComments_goto.c
	time ./RemoveComments_recursive < Test.c > NoComments_recursive.c

No_Comentarios_All:
	time ./RemoveComments_goto < Test.c > NoComments_goto.c
	time ./RemoveComments_recursive < Test.c > NoComments_recursive.c
	time ./RemoveComments_hs < Test.c > NoComments_hs.c

test: # diff funciona con git bash. Compara el contenido entre 2 archivos. Si son diferentes marcan el error.
	diff NoComments_goto.c test_expected.c
	@echo La implementacion goto remueve comentarios correctamente
	diff NoComments_recursive.c test_expected.c
	@echo La implementacion recursiva remueve comentarios correctamente
	diff NoComments_hs.c test_expected.c
	@echo La implementacion haskell remueve comentarios correctamente

clean:
	$(DEL) RemoveComments_goto RemoveComments_recursive RemoveComments_hs NoComments_goto.c NoComments_recursive.c NoComments_hs.c implementaciones/*.o implementaciones/*.hi
