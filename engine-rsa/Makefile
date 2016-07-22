#
# Makefile for engine test
#

all:
	$(CC) -o librsa.so rsa.c -fPIC -shared -lcrypto
	$(CC) -o rsatest rsatest.c -lcrypto -L. -lis8u256a 
clean:
	rm -rf *.o
