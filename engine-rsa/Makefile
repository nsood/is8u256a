#
# Makefile for engine test
#

all:
	$(CC) -o librsa.so rsa.c -fPIC -shared -lcrypto
	$(CC) -o rsatest rsatest.c -lcrypto 
clean:
	rm -rf *.o
