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

	//线段裁剪 参数 线段两个端点的x y坐标，矩形的左下角坐标和右上角坐标
	//Cohen-Sutherland线段裁剪算法
	int ClipLine(int &x1, int &y1, int &x2, int &y2, int rectx1, int recty1, int rectx2, int recty2);
	
	//线段绘制 线段的起始坐标 颜色 video buffer起始地址  pitch(像素每一行之间的字节间隔)   Bresenham算法（直线光栅化算法）
	int DrawLine(int x0, int y0, int x1, int y1, int color, UCHAR *vb_start, int lpitch);
}

#endif
