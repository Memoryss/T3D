#ifndef __T3D_UTIL_H__
#define __T3D_UTIL_H__

#define SET_BIT(word, bit_flag) word = (word | bit_flag)
#define RESET_BIT(word, bit_flag) word = (word & (~bit_flag))

typedef unsigned short UNSHORT;
typedef unsigned char UCHAR;

namespace T3D {
	
	UNSHORT(*RGB16Bit) (int r, int g, int b);

	UNSHORT RGB16Bit565(int r, int g, int b);
	UNSHORT RGB16Bit555(int r, int g, int b);
}

#endif
