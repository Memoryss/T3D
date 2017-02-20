#include "T3DUtil.h"

namespace T3D {


	UNSHORT RGB16Bit565(int r, int g, int b)
	{
		r >>= 3;
		g >>= 2;
		b >>= 3;

		UNSHORT x = 0;
		x = x | (r << 11);
		x = x | (g << 5);
		x = x | b;

		return x;
	}

	UNSHORT RGB16Bit555(int r, int g, int b)
	{
		r >>= 3;
		g >>= 2;
		b >>= 3;

		UNSHORT x = 0;
		x = x | (r << 10);
		x = x | (g << 5);
		x = x | b;

		return x;
	}

	int ClipLine(int &x1, int &y1, int &x2, int &y2, int rectx1, int recty1, int rectx2, int recty2)
	{
		/**********
			算法：
				1.p1,p2判断
					在窗口左边
					在窗口上边
					在窗口右边
					在窗口下边（将矩形及其周围分为九宫格）
				2.如果（p1 | p2） == 0 在窗口内 无需裁剪
				3.如果(p1 & p2) != 0 在窗口一侧，无需裁剪
				4.否则需要裁剪
				TTFF  FTFF  FTTF
				TFFF  FFFF  FFTF
				TFFT  FFFT  FFTT
		*/
#define CLIP_CODE_C  0x0000
#define CLIP_CODE_N  0x0008
#define CLIP_CODE_S  0x0004
#define CLIP_CODE_E  0x0002
#define CLIP_CODE_W  0x0001

#define CLIP_CODE_NE 0x000a
#define CLIP_CODE_SE 0x0006
#define CLIP_CODE_NW 0x0009 
#define CLIP_CODE_SW 0x0005

		int xc1 = x1, yc1 = y1, xc2 = x2, yc2 = y2;

		int p1_code = 0, p2_code = 0, temp = -1;
		if (rectx1 < rectx2)
		{
			temp = rectx1;
			rectx1 = rectx2;
			rectx2 = temp;
		}

		if (recty1 < recty2)
		{
			temp = recty1;
			recty1 = recty2;
			recty2 = temp;
		}

		if (x1 < rectx1)
		{
			p1_code |= CLIP_CODE_W;
		}

		if (x1 > rectx2)
		{
			p1_code|= CLIP_CODE_E;
		}

		if (y1 < recty1)
		{
			p1_code |= CLIP_CODE_N;
		}

		if (y1 > recty2)
		{ 
			p1_code |= CLIP_CODE_S;
		}

		if (x2 < rectx1)
		{
			p2_code |= CLIP_CODE_W;
		}

		if (x2 > rectx2)
		{
			p2_code |= CLIP_CODE_E;
		}

		if (y2 < recty1)
		{
			p2_code |= CLIP_CODE_N;
		}

		if (y2 > recty2)
		{
			p2_code |= CLIP_CODE_S;
		}

		//在窗口内
		if (p1_code == 0 && p2_code == 0)
		{
			return 0;
		}

		//在窗口外
		if ((p1_code & p2_code))
		{
			return 1;
		}
			
		switch (p1_code)
		{
		case CLIP_CODE_C:
			break;
		case CLIP_CODE_N:
			yc1 = recty1;
			xc1 = x1 + (recty1 - y1) * (x1 - x2) / (y1 - y2) + 0.5; //三角形相似  TODO 加上0.5干啥？
			break;
		case CLIP_CODE_S:
			yc1 = recty2;
			xc1 = x1 + (recty2 - y1) * (x1 - x2) / (y1 - y2) + 0.5;
			break;
		case CLIP_CODE_E:
			xc1 = rectx2;
			yc1 = y1 + (rectx2 - x1) * (y1 - y2) / (x1 - x2) + 0.5;
			break;
		case CLIP_CODE_W:
			xc1 = rectx1;
			yc1 = y1 + (rectx1 - x1) * (y1 - y2) / (x1 - x2) + 0.5;
			break;
		default:
			break;
		}

		switch (switch_on)
		{
		default:
			break;
		}
	}

}