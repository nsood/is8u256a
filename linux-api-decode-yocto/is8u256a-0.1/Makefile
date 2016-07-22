#Acorn Common Utils for is8u256a rw

default:
	$(CC) -o test_is8u256a test_is8u256a.c is8u256a.c key_prase.c is8u256a.h key_prase.h
	$(CC) -o libis8u256a.so -shared -fPIC is8u256a.c
clean:
	rm -rf test_is8u256a libis8u256a.so

.PHONY: default clean
