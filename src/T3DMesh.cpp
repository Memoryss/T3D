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

		//����ƽ���뾶�����뾶 
		obj->ComputeRadius();
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

				//�ļ��� rgb��ɫֵ����4.4.4��ʽ��ͼ�ο���rgb��ɫ5.5.5����5.6.5
				//�����Ҫ��4.4.4��rgbֵת��Ϊ8.8.8
				obj->m_plist[poly].m_color = RGB16Bit(red, green, blue);
				Log::WriteError("RGB Color = [%d, %d, %d]\n", red, green, blue);
			}
			else
			{
				//ʹ�õ�ʱ8λ��ɫ����
				SET_BIT(obj->m_plist[poly].m_attr, POLY4DV1_ATTR_8BITCOLOR);
				//��ȡ���8λ���ɵõ���ɫ����
				obj->m_plist[poly].m_color = (poly_surface_desc & 0x00ff);
				Log::WriteError("8-bit color index = %d\n", obj->m_plist[poly].m_color);
			}

			//������ɫģʽ
			int shade_mode = (poly_surface_desc & PLX_SHADE_MODE_MASK);

			//���ö���ε���ɫģʽ
			switch (shade_mode)
			{
			case PLX_SHADE_MODE_PURE_FLAG:
				SET_BIT(obj->m_plist[poly].m_attr, POLY4DV1_ATTR_SHADE_MODE_PURE);
				Log::WriteError("Shade mode = pure\n");
				break;
			case PLX_SHADE_MODE_FLAT_FLAG:
				SET_BIT(obj->m_plist[poly].m_attr, POLY4DV1_ATTR_SHADE_MODE_FLAT);
				Log::WriteError("Shade mode = flat\n");
				break;
			case PLX_SHADE_MODE_PLONG_FLAG:
				SET_BIT(obj->m_plist[poly].m_attr, POLY4DV1_ATTR_SHADE_MODE_PHONG);
				Log::WriteError("Shade mode = plong\n");
				break;
			case PLX_SHADE_MODE_GOURAUD_FLAG:
				SET_BIT(obj->m_plist[poly].m_attr, POLY4DV1_ATTR_SHADE_MODE_GOURAUD);
				Log::WriteError("Shade mode = gouraud\n");
				break;
			default:
				break;
			}

			obj->m_plist[poly].m_state = POLY4DV1_STATE_ACTIVE;
		} //End of poly

		//��ʼ�����峯�� ��������ƽ��
		obj->m_ux.InitXYZW(1, 0, 0, 1);
		obj->m_uy.InitXYZW(0, 1, 0, 1);
		obj->m_uz.InitXYZW(0, 0, 1, 1);

		fclose(fp);
		return 0;
	}//end of load plg

	int Object::ComputeRadius()
	{
		m_avg_radius = 0;
		m_max_radisus = 0;

		for (int i = 0; i < m_vlist_local.size(); ++i)
		{
			float dist_to_vertex = sqrt(m_vlist_local[i].m_x * m_vlist_local[i].m_x + m_vlist_local[i].m_y * m_vlist_local[i].m_y + m_vlist_local[i].m_z * m_vlist_local[i].m_z);

			m_avg_radius += dist_to_vertex;
			if (dist_to_vertex > m_max_radisus) m_max_radisus = dist_to_vertex;
		}

		if (m_vlist_local.size() > 0) m_avg_radius /= m_vlist_local.size();

		return m_max_radisus;
	}

	void RenderList::TransForm(const Matrix44 & mt, int coord_select)
	{
		switch (coord_select)
		{
		case TRANSFORM_LOCAL_ONLY:
			for (int poly = 0; poly < m_facePtrs.size(); ++poly)
			{
				TriangleFace *face = m_facePtrs[poly];
				//�ж϶�����Ƿ���ڣ��Ƿ���Ч
				//���������� �����޹ؽ�Ҫ
				if (face == NULL || !(face->m_state & POLY4DV1_STATE_ACTIVE) || face->m_state & POLY4DV1_STATE_BACKFACE || face->m_state & POLY4DV1_STATE_CLIPPED)
				{
					continue;
				}

				//����������������б仯
				for (int vertex = 0; vertex < 3; ++vertex)
				{
					Point4D presult;  //������ʱ�洢�仯�Ľ��
					CommonMath::V4dMulMat44(face->m_vlist[vertex])
				}
			}
			break;
		case TRANSFORM_TRANS_ONLY:
			break;
		case TRANSFORM_LOCAL_TO_TRANS:
			break;
		default:
			break;
		}
	}
	
} //T3D
