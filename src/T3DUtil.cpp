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
		case CLIP_CODE_NE:  //先N如果不满足 则使用E
			yc1 = recty1;
			xc1 = x1 + (recty1 - y1) * (x1 - x2) / (y1 - y2) + 0.5;
			if (xc1 < rectx1 || xc1 > rectx2)
			{
				xc1 = rectx2;
				yc1 = y1 + (rectx2 - x1) * (y1 - y2) / (x1 - x2) + 0.5;
			}
			break;
		case CLIP_CODE_SE:
			yc1 = recty2;
			xc1 = x1 + (recty2 - y1) * (x1 - x2) / (y1 - y2) + 0.5;
			if (xc1 < rectx1 || xc1 > rectx2)
			{
				xc1 = rectx2;
				yc1 = y1 + (rectx2 - x1) * (y1 - y2) / (x1 - x2) + 0.5;
			}
			break;
		case CLIP_CODE_NW:
			yc1 = recty1;
			xc1 = x1 + (recty1 - y1) * (x1 - x2) / (y1 - y2) + 0.5;
			if (xc1 < rectx1 || xc1 > rectx2)
			{
				xc1 = rectx1;
				yc1 = y1 + (rectx1 - x1) * (y1 - y2) / (x1 - x2) + 0.5;
			}
			break;
		case CLIP_CODE_SW:
			yc1 = recty2;
			xc1 = x1 + (recty2 - y1) * (x1 - x2) / (y1 - y2) + 0.5;
			if (xc1 < rectx1 || xc1 > rectx2)
			{
				xc1 = rectx1;
				yc1 = y1 + (rectx1 - x1) * (y1 - y2) / (x1 - x2) + 0.5;
			}
			break;
		default:
			break;
		} //END FOR SWITCH p1_code

		switch (p2_code)
		{
		case CLIP_CODE_C:
			break;
		case CLIP_CODE_N:
			yc2 = recty1;
			xc2 = x2 + (recty1 - y2) * (y2 - y1) / (x2 - x1) + 0.5;
			break;
		case CLIP_CODE_S:
			yc2 = recty2;
			xc2 = x2 + (recty2 - y2) * (y2 - y1) / (x2 - x1) + 0.5;
			break;
		case CLIP_CODE_E:
			xc2 = rectx2;
			yc2 = y2 + (rectx2 - x2) * (y2 - y1) / (x2 - x1) + 0.5;
			break;
		case CLIP_CODE_W:
			xc2 = rectx1;
			yc2 = y2 + (rectx1 - x2) * (y2 - y1) / (x2 - x1) + 0.5;
			break;
		case CLIP_CODE_NE:
			yc2 = recty1;
			xc2 = x2 + (recty1 - y2) * (y2 - y1) / (x2 - x1) + 0.5;
			if (xc2 < rectx1 || xc2 > rectx2)
			{
				xc2 = rectx2;
				yc2 = y2 + (rectx2 - x2) * (y2 - y1) / (x2 - x1) + 0.5;
			}
			break;
		case CLIP_CODE_SE:
			yc2 = recty2;
			xc2 = x2 + (recty2 - y2) * (y2 - y1) / (x2 - x1) + 0.5;
			if (xc2 < rectx1 || xc2 > rectx2)
			{
				xc2 = rectx2;
				yc2 = y2 + (rectx2 - x2) * (y2 - y1) / (x2 - x1) + 0.5;
			}
			break;
		case CLIP_CODE_NW:
			yc2 = recty1;
			xc2 = x2 + (recty1 - y2) * (y2 - y1) / (x2 - x1) + 0.5;
			if (xc2 < rectx1 || xc2 > rectx2)
			{
				xc2 = rectx1;
				yc2 = y2 + (rectx1 - x2) * (y2 - y1) / (x2 - x1) + 0.5;
			}
			break;
		case CLIP_CODE_SW:
			yc2 = recty2;
			xc2 = x2 + (recty2 - y2) * (y2 - y1) / (x2 - x1) + 0.5;
			if (xc2 < rectx1 || xc2 > rectx2)
			{
				xc2 = rectx1;
				yc2 = y2 + (rectx1 - x2) * (y2 - y1) / (x2 - x1) + 0.5;
			}
			break;
		default:
			break;
		}//END SWITCH p2_code

		if (xc1 < rectx1 || xc1 > rectx2 || yc1 < recty1 || yc1 > recty2 || xc2 < rectx1 || x2 > rectx2 || y2 < recty1 || y2 > recty2)
		{
			return 1;
		} //end if

		y1 = yc1;
		x1 = xc1;
		y2 = yc2;
		x2 = xc2;

		return 0;
	} //end CLIP_LINE

	int DrawLine(int x0, int y0, int x1, int y1, int color, UCHAR *vb_start, int lpitch)
	{
		/************************************************************************/
		/*                           Bresenham算法                                          
			1.会计算直线坐标和像素格子之间的交点，判断交点的坐标和坐标轴距离的远近从而判断选用那个像素格子
			2.算法实现使用直线斜率为0.5的作为分隔线，因为直线斜率为0.5的时候交点位于像素格子中间
			3.算法实现完全采用整数，不使用除法，因此看起来逻辑有点问题，具体算法可看 Bresenham算法
		*/
		/************************************************************************/
		int dx,  // 两点之间x的坐标差
			dy,  // 两点之间y的坐标差
			dx2, //
			dy2,
			x_inc,  //移动到下一个x像素的间隔
			y_inc,  //移动到下一个y像素的间隔
			error,
			index;

		vb_start = vb_start + x0 + y0 * lpitch;  //计算p0点对应像素开始的位置

		dx = x1 - x0;
		dy = y1 - y0;

		if (dx > 0)
		{
			x_inc = 1;
		} //end move to right
		else
		{
			x_inc = -1;
			dx = -dx;
		} //end move to left

		if (dy > 0)
		{
			y_inc = lpitch;
		} // end move to down
		else
		{
			y_inc = -lpitch;
			dy = -dy;
		}

		dx2 = dx << 1;
		dy2 = dy << 1;

		//判断以哪个坐标轴作为像素格子增长 因为dx > dy 所以 x+1时， y可能+0/+1
		if (dx > dy)
		{
			error = dy2 - dx;

			for (index = 0; index <= dx; ++index)
			{
				*vb_start = color;

				if (error >= 0)
				{
					error -= dx2;
					vb_start += y_inc;  //移到下一行
				} // end for dx

				error += dy2;

				vb_start += x_inc;
			}
		} //end if
		else 
		{
			error = dx2 - dy;
			for (index = 0; index < dy; ++index)
			{
				*vb_start = color;

				if (error > 0)
				{
					error -= dy2;
					vb_start += x_inc;
				}

				error += dx2;

				vb_start += y_inc;
			} //end for dy
		}// end else

		return 0;
	} // end draw line


}