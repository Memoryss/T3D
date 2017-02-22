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
			�㷨��
				1.p1,p2�ж�
					�ڴ������
					�ڴ����ϱ�
					�ڴ����ұ�
					�ڴ����±ߣ������μ�����Χ��Ϊ�Ź���
				2.�����p1 | p2�� == 0 �ڴ����� ����ü�
				3.���(p1 & p2) != 0 �ڴ���һ�࣬����ü�
				4.������Ҫ�ü�
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

		//�ڴ�����
		if (p1_code == 0 && p2_code == 0)
		{
			return 0;
		}

		//�ڴ�����
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
			xc1 = x1 + (recty1 - y1) * (x1 - x2) / (y1 - y2) + 0.5; //����������  TODO ����0.5��ɶ��
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
		case CLIP_CODE_NE:  //��N��������� ��ʹ��E
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
		/*                           Bresenham�㷨                                          
			1.�����ֱ����������ظ���֮��Ľ��㣬�жϽ�������������������Զ���Ӷ��ж�ѡ���Ǹ����ظ���
			2.�㷨ʵ��ʹ��ֱ��б��Ϊ0.5����Ϊ�ָ��ߣ���Ϊֱ��б��Ϊ0.5��ʱ�򽻵�λ�����ظ����м�
			3.�㷨ʵ����ȫ������������ʹ�ó�������˿������߼��е����⣬�����㷨�ɿ� Bresenham�㷨
		*/
		/************************************************************************/
		int dx,  // ����֮��x�������
			dy,  // ����֮��y�������
			dx2, //
			dy2,
			x_inc,  //�ƶ�����һ��x���صļ��
			y_inc,  //�ƶ�����һ��y���صļ��
			error,
			index;

		vb_start = vb_start + x0 + y0 * lpitch;  //����p0���Ӧ���ؿ�ʼ��λ��

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

		//�ж����ĸ���������Ϊ���ظ������� ��Ϊdx > dy ���� x+1ʱ�� y����+0/+1
		if (dx > dy)
		{
			error = dy2 - dx;

			for (index = 0; index <= dx; ++index)
			{
				*vb_start = color;

				if (error >= 0)
				{
					error -= dx2;
					vb_start += y_inc;  //�Ƶ���һ��
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