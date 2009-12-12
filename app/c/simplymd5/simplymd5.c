/*
 * simplymd5.c
 *
 * This code will compute the md5 hash of some range of memory.
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/****************************************************
 *  md5.c - converts a string into an md5 hash        
 *                                                  
 *  main() takes the hard-coded string and MD5Hash()  
 *  returns the hash                                  
 *                                                  
 *  Lindsey Bieda
 ****************************************************/

unsigned int r[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

unsigned int k[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1,
	0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x2441453,
	0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942,
	0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x4881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d,
	0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};


unsigned int g[64] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
	1, 6, 11, 0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12,
	5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2,
	0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9 };


char* MD5Hash( char* hash, char* message, int len) {
	int bufferLen = (((len+9)/64)+1)*64, i;
	char* buffer;

	long bitLen = len*8;

	char* bufferptr;

	int* data;

	unsigned int a, b, c, d, tmp;

	unsigned int a0 = 0x67452301, b0 = 0xEFCDAB89, c0 = 0x98BADCFE, d0 = 0x10325476;

	buffer = malloc(sizeof(char)*bufferLen);

	memcpy(buffer, message, len);

	for(i=len+1; i<bufferLen-8; i++) {
		buffer[i] = 0;
	}

	buffer[len] = 128;

	bufferptr = &buffer[bufferLen-8];

	while(bufferptr != &buffer[bufferLen]) {
		bufferptr[0] = bitLen & 0xFF;

		bufferptr++;

		bitLen = bitLen >> 8;
	}

	data = (int*)buffer;

	while(data != (int*)&buffer[bufferLen]) {
		a = a0;
		b = b0;
		c = c0;
		d = d0;

		for(i=0; i<64; i++) {
			if(i<16) {
				a += (b & c) | (~b & d);
			}
			else if(i<32) {
				a += (b & d) | (~d & c);
			}
			else if(i<48) {
				a += (b ^ c ^ d);
			}
			else {
				a += c ^ (~d | b);
			}

			a += data[g[i]] + k[i];
			a = (a << r[i]) | (a >> 32-r[i]);
			a+= b;

			tmp = d;
			d = c;
			c = b;
			b = a;
			a = tmp;
		}

		a0 += a;
		b0 += b;
		c0 += c;
		d0 += d;

		data+=16;
	}

	a = (a0 & 0xFF) << 24;
	a0 = a0 >> 8;
	a += (a0 & 0xFF) << 16;
	a0 = a0 >> 8;
	a += (a0 & 0xFF) << 8;
	a += a0 >> 8;

	b = (b0 & 0xFF) << 24;
	b0 = b0 >> 8;
	b += (b0 & 0xFF) << 16;
	b0 = b0 >> 8;
	b += (b0 & 0xFF) << 8;
	b += b0 >> 8;

	c = (c0 & 0xFF) << 24;
	c0 = c0 >> 8;
	c += (c0 & 0xFF) << 16;
	c0 = c0 >> 8;
	c += (c0 & 0xFF) << 8;
	c += c0 >> 8;

	d = (d0 & 0xFF) << 24;
	d0 = d0 >> 8;
	d += (d0 & 0xFF) << 16;
	d0 = d0 >> 8;
	d += (d0 & 0xFF) << 8;
	d += d0 >> 8;

	sprintf(hash, "%.8x%.8x%.8x%.8x", a,b,c,d);

	free(buffer);

	return hash;
}

void main() {
	char message[]="String you wish to hash";
	char hash[33];

	MD5Hash( hash, message, strlen(message));
}
