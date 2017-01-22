#include "T3DMesh.h"

#include "T3DLog.h"
#include "T3DUtil.h"

namespace T3D {

	char * PLGLoader::GetLinePLG(char *buffer, int maxlength, FILE * fp)
	{
		int index = 0;
		int length = 0;

		while (true)
		{
			if (!fgets(buffer, maxlength, fp)) return NULL;

			//计算空格数
			for (; index < strlen(buffer); ++index)
			{
				if (!strcmp(buffer + index, " ")) break;
			}

			//整行空格或者注释
			if (index == strlen(buffer) || strcmp(buffer + index, "#")) continue;

			//返回 数据
			return buffer + index;
		}
	}

	int PLGLoader::LoadObjectPLG(Object *obj, const char *filename, const Vector4D &scale, const Vector4D &pos, const Vector4D &rot)
	{
		FILE *fp;

		char buffer[256]; //缓冲区

		char *token_string; //执行要分析物体数据文本的指针

		//清空obj
		memset(obj, 0, sizeof(Object));
		
		//将物体设置为可见的或者活动的
		obj->m_state = OBJECT_STATE_ACTIVE | OBJECT_STATE_VISIBLE;

		//设置物体的位置
		obj->m_world_pos.m_x = pos.m_x;
		obj->m_world_pos.m_y = pos.m_y;
		obj->m_world_pos.m_z = pos.m_z;
		obj->m_world_pos.m_w = pos.m_w;

		//打开文件
		if (!(fp = fopen(filename, "r")))
		{
			Log::WriteError("Couldn't open plg file:%s\n", filename);
			return 1;
		}

		if (!(token_string = GetLinePLG(buffer, 256, fp)))
		{
			Log::WriteError("plg file error with file %s (object descriptor invaild).\n", filename);
			return 1;
		}

		Log::WriteError("Object Descriptor:%s\n", token_string);

		//对物体描述符进行分析
		sscanf(token_string, "%s %d %d", &obj->m_name, &obj->m_num_vertices, &obj->m_num_polys);

		//加载顶点列表
		for (int i = 0; i < obj->m_num_vertices; ++i)
		{
			if (!(token_string = GetLinePLG(buffer, 256, fp)))
			{
				Log::WriteError("plg file error with file %s (vertex list invaild).\n", filename);
				return 1;
			}

			//分析顶点
			Point4D point;
			sscanf(token_string, "%f %f %f", &point.m_x, &point.m_y, &point.m_z);
			point.m_w = 1;

			//缩放顶点坐标
			point.m_x *= scale.m_x;
			point.m_y *= scale.m_y;
			point.m_z *= scale.m_z;

			obj->m_vlist_local.push_back(point);

			Log::WriteError("vectex %d = %f, %f, %f, %f\n", i, point.m_x, point.m_y, point.m_z, point.m_w);
		}

		//计算平均半径和最大半径 TODO
		Log::WriteError("Object average radius = %f, max radius\n", obj->m_attr, obj->m_max_radisus);

		int poly_surface_desc = 0; //plg/plx多边形描述符
		int poly_num_verts = 0; //当前多边形的顶点数  三角形始终为3
		char tmp_string[8]; //多边形的描述符

		//加载多边形列表
		for (int poly = 0; poly < obj->m_num_polys; ++poly)
		{
			//读取多边形描述符
			if (!(token_string = GetLinePLG(buffer, 256, fp)))
			{
				Log::WriteError("plg file error with file %s (polygon descriptor invaild).\n", filename);
				return 1;
			}

			Log::WriteError("Polypon %d:\n", poly);

			Triangle triangle;
			sscanf(token_string, "%s %d %f %f %f", tmp_string, &poly_num_verts, &triangle.m_vertices[0], &triangle.m_vertices[1], &triangle.m_vertices[2]);
			
			//描述符可能是16进制 需要判断
			if (tmp_string[0] == '0' && tmp_string[1] == 'X')  //十六进制
				sscanf(tmp_string, "%x", &poly_surface_desc);
			else
				poly_surface_desc = atoi(tmp_string);

			triangle.m_vlist = &obj->m_vlist_local[0];
			Log::WriteError("Surface Desc = 0x%.4x, num_verts = %d, vert_indices[%d, %d, %d]", poly_surface_desc, poly_num_verts, triangle.m_vertices[0], triangle.m_vertices[1], triangle.m_vertices[3]);

			//分析多边形描述符
			//提取多边形的的每个位字段
			//从单、双面开始
			if (poly_surface_desc & PLX_2SIDED_FLAG)
			{
				SET_BIT(obj->m_plist[poly].m_attr, POLY4DV1_ATTR_2SIDED);
				Log::WriteError("2 sides.\n");
			}
			else
			{
				Log::WriteError("1 side.\n");
			}

			//设置颜色模式  16位rgb和8位颜色索引
			if (poly_surface_desc & PLX_COLOR_MODE_RGB_FLAG)
			{
				SET_BIT(obj->m_plist[poly].m_attr, POLY4DV1_ATTR_RGB16);

				//提取颜色
				int red = (poly_surface_desc & 0x0f00) >> 8;
				int green = (poly_surface_desc & 0x00f0) >> 4;
				int blue = (poly_surface_desc & 0x000f);

				obj->m_plist[poly].m_color = RGB1
			}
		}
	}
}
