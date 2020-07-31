BATCHLIB_DIR=${HOME}/FIRESTARTER/batchlib

main: batch
	#gcc -Wall -DDEBUG -std=c99 -L. -Wl,-rpath=.  main.c -lbatch
	gcc -Wall -DDEBUG -std=c99 -L${BATCHLIB_DIR} -Wl,-rpath=${BATCHLIB_DIR}  main.c -lbatch

batch:
	gcc -Wall -DDEBUG -fPIC -std=c99 -g -c batch.c
	ld -shared batch.o -o libbatch.so
	ar rcs libbatch.a batch.o

clean:
	rm -rf a.out libbatch.o libbatch.so libbatch.a
