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

			//����ո���
			for (; index < strlen(buffer); ++index)
			{
				if (!strcmp(buffer + index, " ")) break;
			}

			//���пո����ע��
			if (index == strlen(buffer) || strcmp(buffer + index, "#")) continue;

			//���� ����
			return buffer + index;
		}
	}

	int PLGLoader::LoadObjectPLG(Object *obj, const char *filename, const Vector4D &scale, const Vector4D &pos, const Vector4D &rot)
	{
		FILE *fp;

		char buffer[256]; //������

		char *token_string; //ִ��Ҫ�������������ı���ָ��

		//���obj
		memset(obj, 0, sizeof(Object));
		
		//����������Ϊ�ɼ��Ļ��߻��
		obj->m_state = OBJECT_STATE_ACTIVE | OBJECT_STATE_VISIBLE;

		//���������λ��
		obj->m_world_pos.m_x = pos.m_x;
		obj->m_world_pos.m_y = pos.m_y;
		obj->m_world_pos.m_z = pos.m_z;
		obj->m_world_pos.m_w = pos.m_w;

		//���ļ�
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

		//���������������з���
		sscanf(token_string, "%s %d %d", &obj->m_name, &obj->m_num_vertices, &obj->m_num_polys);

		//���ض����б�
		for (int i = 0; i < obj->m_num_vertices; ++i)
		{
			if (!(token_string = GetLinePLG(buffer, 256, fp)))
			{
				Log::WriteError("plg file error with file %s (vertex list invaild).\n", filename);
				return 1;
			}

			//��������
			Point4D point;
			sscanf(token_string, "%f %f %f", &point.m_x, &point.m_y, &point.m_z);
			point.m_w = 1;

			//���Ŷ�������
			point.m_x *= scale.m_x;
			point.m_y *= scale.m_y;
			point.m_z *= scale.m_z;

			obj->m_vlist_local.push_back(point);

			Log::WriteError("vectex %d = %f, %f, %f, %f\n", i, point.m_x, point.m_y, point.m_z, point.m_w);
		}

		//����ƽ���뾶�����뾶 TODO
		Log::WriteError("Object average radius = %f, max radius\n", obj->m_attr, obj->m_max_radisus);

		int poly_surface_desc = 0; //plg/plx�����������
		int poly_num_verts = 0; //��ǰ����εĶ�����  ������ʼ��Ϊ3
		char tmp_string[8]; //����ε�������

		//���ض�����б�
		for (int poly = 0; poly < obj->m_num_polys; ++poly)
		{
			//��ȡ�����������
			if (!(token_string = GetLinePLG(buffer, 256, fp)))
			{
				Log::WriteError("plg file error with file %s (polygon descriptor invaild).\n", filename);
				return 1;
			}

			Log::WriteError("Polypon %d:\n", poly);

			Triangle triangle;
			sscanf(token_string, "%s %d %f %f %f", tmp_string, &poly_num_verts, &triangle.m_vertices[0], &triangle.m_vertices[1], &triangle.m_vertices[2]);
			
			//������������16���� ��Ҫ�ж�
			if (tmp_string[0] == '0' && tmp_string[1] == 'X')  //ʮ������
				sscanf(tmp_string, "%x", &poly_surface_desc);
			else
				poly_surface_desc = atoi(tmp_string);

			triangle.m_vlist = &obj->m_vlist_local[0];
			Log::WriteError("Surface Desc = 0x%.4x, num_verts = %d, vert_indices[%d, %d, %d]", poly_surface_desc, poly_num_verts, triangle.m_vertices[0], triangle.m_vertices[1], triangle.m_vertices[3]);

			//���������������
			//��ȡ����εĵ�ÿ��λ�ֶ�
			//�ӵ���˫�濪ʼ
			if (poly_surface_desc & PLX_2SIDED_FLAG)
			{
				SET_BIT(obj->m_plist[poly].m_attr, POLY4DV1_ATTR_2SIDED);
				Log::WriteError("2 sides.\n");
			}
			else
			{
				Log::WriteError("1 side.\n");
			}

			//������ɫģʽ  16λrgb��8λ��ɫ����
			if (poly_surface_desc & PLX_COLOR_MODE_RGB_FLAG)
			{
				SET_BIT(obj->m_plist[poly].m_attr, POLY4DV1_ATTR_RGB16);

				//��ȡ��ɫ
				int red = (poly_surface_desc & 0x0f00) >> 8;
				int green = (poly_surface_desc & 0x00f0) >> 4;
				int blue = (poly_surface_desc & 0x000f);

				obj->m_plist[poly].m_color = RGB1
			}
		}
	}
}
