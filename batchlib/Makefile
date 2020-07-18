BATCHLIB_DIR=${HOME}/matt/FIRESTARTER/batchlib

main: batch
	gcc -Wall -std=c99 -L/${BATCHLIB_DIR}/batch -Wl,-rpath=${BATCHLIB_DIR}/  main.c -lbatch

batchlib:
	gcc -Wall -fPIC -c -std=c99 -g batch.c 
	ld -shared batch.o -o batch.so

clean:
	rm -rf a.out batch.o batch.so 
