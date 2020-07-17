#make file for batch lib.
#$(CC) $(CFLAGS)-o $(TARGET) $(TARGET).c 

main:
	gcc -Wall -std=c99 -L/home/bobbitt5/FIRESTARTER/batchlib -Wl,-rpath=/home/bobbitt5/FIRESTARTER/batchlib/  main.c -lbatchlib

batchlib:
	gcc -Wall -fPIC -c -std=c99 -g batch_orig.c -o batchlib.o
	ld -shared batchlib.o -o batchlib.so
clean:
	rm -rf a.out batchlib.o batchlib.so 
