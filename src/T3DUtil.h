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

	//�߶βü� ���� �߶������˵��x y���꣬���ε����½���������Ͻ�����
	//Cohen-Sutherland�߶βü��㷨
	int ClipLine(int &x1, int &y1, int &x2, int &y2, int rectx1, int recty1, int rectx2, int recty2);
	
	//�߶λ��� �߶ε���ʼ���� ��ɫ video buffer��ʼ��ַ  pitch(����ÿһ��֮����ֽڼ��)   Bresenham�㷨��ֱ�߹�դ���㷨��
	int DrawLine(int x0, int y0, int x1, int y1, int color, UCHAR *vb_start, int lpitch);
}

#endif
