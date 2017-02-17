#include "T3DMesh.h"

#include "T3DLog.h"
#include "T3DUtil.h"

namespace T3D {

	char * PLGLoader::GetLinePLG(char *buffer, int maxlength, FILE * fp)
	{
		size_t index = 0;
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

	int PLGLoader::LoadObjectPLG(Object *obj, const char *filename, const Vec4 &scale, const Vec4 &pos, const Vec4 &rot)
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
			Vec4 point;
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

		for (size_t i = 0; i < m_vlist_local.size(); ++i)
		{
			float dist_to_vertex = sqrt(m_vlist_local[i].m_x * m_vlist_local[i].m_x + m_vlist_local[i].m_y * m_vlist_local[i].m_y + m_vlist_local[i].m_z * m_vlist_local[i].m_z);

			m_avg_radius += dist_to_vertex;
			if (dist_to_vertex > m_max_radisus) m_max_radisus = dist_to_vertex;
		}

		if (m_vlist_local.size() > 0) m_avg_radius /= m_vlist_local.size();

		return m_max_radisus;
	}

	void Object::Transform(const Matrix44 & mt, int coord_select, int transform_basis)
	{
		switch (coord_select)
		{
		case TRANSFORM_LOCAL_ONLY:
			for (size_t vertex = 0; vertex < m_vlist_local.size(); ++vertex)
			{
				Vec4 presult; //������ʱ�洢�任�Ľ��
				CommonMath::V4dMulMat44(m_vlist_local[vertex], mt, presult);
				m_vlist_local[vertex].InitWithVec4(presult); //��������ȥ
			}
			break;
		case TRANSFORM_TRANS_ONLY:
			for (size_t vertex = 0; vertex < m_vlist_trans.size(); ++vertex)
			{
				Vec4 presult; 
				CommonMath::V4dMulMat44(m_vlist_trans[vertex], mt, presult);
				m_vlist_trans[vertex].InitWithVec4(presult);
			}
			break;
		case TRANSFORM_LOCAL_TO_TRANS:
			for (size_t vertex = 0; vertex < m_vlist_local.size(); ++vertex)
			{
				CommonMath::V4dMulMat44(m_vlist_local[vertex], mt, m_vlist_trans[vertex]);
			}
			break;
		default:
			break;
		}

		//���������仯
		if (transform_basis)
		{
			Vec4 vresult;

			//x
			CommonMath::V4dMulMat44(m_ux, mt, vresult);
			m_ux.InitWithVec4(vresult);

			//y
			CommonMath::V4dMulMat44(m_uy, mt, vresult);
			m_uy.InitWithVec4(vresult);

			//z
			CommonMath::V4dMulMat44(m_uz, mt, vresult);
			m_uz.InitWithVec4(vresult);
		}
	}

	void Object::ModelToWorld(int coord_select)
	{
		if (coord_select == TRANSFORM_LOCAL_TO_TRANS)
		{
			for (size_t vertex = 0; vertex < m_vlist_local.size(); ++vertex)
			{
				CommonMath::Vec4Add(m_vlist_local[vertex], m_world_pos, m_vlist_trans[vertex]);
			}
		}
		else  //TRANSFORM_TRANS_ONLY
		{
			for (size_t vertex = 0; vertex < m_vlist_local.size(); ++vertex)
			{
				CommonMath::Vec4Add(m_vlist_trans[vertex], m_world_pos, m_vlist_trans[vertex]);
			}
		}
	}

	void Object::BuildModelToWorldMat44(Matrix44 & mt)
	{
		mt.InitZero();
		mt.m_mat[0][0] = 1;
		mt.m_mat[1][1] = 1;
		mt.m_mat[2][2] = 1;
		mt.m_mat[3][3] = 1;
		mt.m_mat[3][0] = m_world_pos.m_x;
		mt.m_mat[3][1] = m_world_pos.m_y;
		mt.m_mat[3][2] = m_world_pos.m_z;
	}

	void Object::WorldToCamera(const Camera &cam)
	{
		for (size_t vertex = 0; vertex < m_vlist_trans.size(); ++vertex)
		{
			CommonMath::V4dMulMat44(m_vlist_trans[vertex], cam.m_cam, m_vlist_trans[vertex]);
		}
	}

	int Object::Cull(const Camera &cam, int cull_flags)
	{
		Vec4 sphere_pos;
		//ת��������ռ�
		CommonMath::V4dMulMat44(this->m_world_pos, cam.m_cam, sphere_pos);

		//������ѡ��Ĳü���ʽ���вü�
		if (cull_flags & CULL_OBJECT_Z_PLANE)
		{
			if (sphere_pos.m_z - this->m_max_radisus > cam.m_far_clip_z || sphere_pos.m_z + this->m_max_radisus < cam.m_near_clip_z)
			{
				SET_BIT(this->m_state, OBJECT_STATE_CULLED);
				return 0;
			}
		}

		if (cull_flags & CULL_OBJECT_X_PLANE)
		{
			float x_test = 0.5 * cam.m_viewport_width * sphere_pos.m_z / cam.m_view_dist;
			if (sphere_pos.m_x - this->m_max_radisus > x_test || sphere_pos.m_x + this->m_max_radisus < -x_test)
			{
				SET_BIT(this->m_state, OBJECT_STATE_CULLED);
				return 0;
			}
		}

		if (cull_flags & CULL_OBJECT_Z_PLANE)
		{
			float y_test = 0.5 * cam.m_viewport_height * sphere_pos.m_z / cam.m_view_dist;
			if (sphere_pos.m_y - this->m_max_radisus > y_test || sphere_pos.m_y + this->m_max_radisus - y_test)
			{
				SET_BIT(this->m_state, OBJECT_STATE_CULLED);
				return 0;
			}
		}

		return 1;
	}// end cull object

	void Object::Reset()
	{
		RESET_BIT(this->m_state, OBJECT_STATE_CULLED);  //ȡ��culled���
		for (size_t vertex; vertex < this->m_plist.size(); ++vertex)
		{
			Triangle &face = this->m_plist[vertex];
			//�ж��Ƿ�ɼ�
			if (!(face.m_state & POLY4DV1_STATE_ACTIVE)) continue;

			RESET_BIT(face.m_state, POLY4DV1_STATE_BACKFACE);
			RESET_BIT(face.m_state, POLY4DV1_STATE_CLIPPED);
		} //END OF POLY
	} // END object reset

	void Object::RemoveBackfaces(const Camera &cam)
	{
		if (this->m_state & OBJECT_STATE_CULLED)
			return;

		for (size_t vertex; vertex < this->m_plist.size(); ++vertex)
		{
			Triangle &face = m_plist[vertex];
			if (!(face.m_state & POLY4DV1_STATE_ACTIVE) || face.m_state & POLY4DV1_STATE_BACKFACE || face.m_state & POLY4DV1_STATE_CLIPPED)
				continue;

			int vertex_0 = face.m_vertices[0];
			int vertex_1 = face.m_vertices[1];
			int vertex_2 = face.m_vertices[2];

			Vec4 u, v, n;
			CommonMath::Vec4Build(face.m_vlist[vertex_0], face.m_vlist[vertex_1], u);
			CommonMath::Vec4Build(face.m_vlist[vertex_1], face.m_vlist[vertex_2], v);
			CommonMath::Vec4Cross(u, v, n);

			Vec4 view;
			CommonMath::Vec4Build(face.m_vlist[vertex_0], cam.m_pos, view);
			
			float dp = CommonMath::Vec4Dot(n, view);
			if (dp < 0.0f) 
			{
				SET_BIT(face.m_state, POLY4DV1_STATE_BACKFACE);
			}
		}
	}// END BACKFACE

	void RenderList::TransForm(const Matrix44 & mt, int coord_select)
	{
		switch (coord_select)
		{
		case TRANSFORM_LOCAL_ONLY:
			//forѭ��Ӧ�÷�������õ㣬����switch�����ͱ�ö��� ���ܻ�Ӱ��Ч��
			//�Ծֲ�������б仯
			for (size_t poly = 0; poly < m_facePtrs.size(); ++poly)
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
					Vec4 presult;  //������ʱ�洢�仯�Ľ��
					CommonMath::V4dMulMat44(face->m_vlist[vertex], mt, presult);
					face->m_vlist[vertex].InitWithVec4(presult); //���ȥ
				}
			}
			break;
		case TRANSFORM_TRANS_ONLY:
			//����Ⱦ�б��б仯��Ķ�����б任
			// tvlist���ڴ洢�ۻ��仯�Ľ��
			for (size_t poly = 0; poly < m_facePtrs.size(); ++poly)
			{
				TriangleFace *face = m_facePtrs[poly];
				if (face == NULL || !(face->m_state & POLY4DV1_STATE_ACTIVE) || face->m_state & POLY4DV1_STATE_BACKFACE || face->m_state & POLY4DV1_STATE_CLIPPED)
				{
					continue;
				}

				for (int vertex = 0; vertex < 3; ++vertex)
				{
					Vec4 presult;  //������ʱ�洢�仯�Ľ��
					CommonMath::V4dMulMat44(face->m_tvlist[vertex], mt, presult);
					face->m_tvlist[vertex].InitWithVec4(presult); //���ȥ
				}

			}
			break;
		case TRANSFORM_LOCAL_TO_TRANS:
			//����Ⱦ�б��еľֲ���ģ�Ͷ����б���б仯
			//��������洢���任��Ķ����б���
			for (size_t poly = 0; poly < m_facePtrs.size(); ++poly)
			{
				TriangleFace *face = m_facePtrs[poly];
				if (face == NULL || !(face->m_state & POLY4DV1_STATE_ACTIVE) || face->m_state & POLY4DV1_STATE_BACKFACE || face->m_state & POLY4DV1_STATE_CLIPPED)
				{
					continue;
				}

				for (int vertex = 0; vertex < 3; ++vertex)
				{
					CommonMath::V4dMulMat44(face->m_vlist[vertex], mt, face->m_vlist[vertex]);
				}

			}
			break;
		default:
			break;
		}
	}

	void RenderList::ModelToWorld(Vec4 world_pos, int coord_select)
	{
		if (coord_select == TRANSFORM_LOCAL_TO_TRANS)
		{
			for (size_t poly = 0; poly < m_facePtrs.size(); ++poly)
			{
				TriangleFace *face = m_facePtrs[poly];
				if (face == NULL || face->m_state != POLY4DV1_STATE_ACTIVE || face->m_state == POLY4DV1_STATE_BACKFACE || face->m_state == POLY4DV1_STATE_CLIPPED) continue;

				for (int vertex = 0; vertex < 3; ++vertex)
				{
					CommonMath::Vec4Add(face->m_vlist[vertex], world_pos, face->m_tvlist[vertex]);
				}
			}
		}
		else // TRANSFORM_TRANS_ONLY
		{
			for (size_t poly = 0; poly < m_facePtrs.size(); ++poly)
			{
				TriangleFace *face = m_facePtrs[poly];
				if (face == NULL || face->m_state != POLY4DV1_STATE_ACTIVE || face->m_state == POLY4DV1_STATE_BACKFACE || face->m_state == POLY4DV1_STATE_CLIPPED) continue;

				for (int vertex = 0; vertex < 3; ++vertex)
				{
					CommonMath::Vec4Add(face->m_tvlist[vertex], world_pos, face->m_tvlist[vertex]);
				}
			}
		}
	}

	void RenderList::BuildModelToWorldMat44(Vec4 world_pos, Matrix44 & mt)
	{
		mt.InitZero();
		mt.m_mat[0][0] = 1;
		mt.m_mat[1][1] = 1;
		mt.m_mat[2][2] = 1;
		mt.m_mat[3][3] = 1;
		mt.m_mat[3][0] = world_pos.m_x;
		mt.m_mat[3][1] = world_pos.m_y;
		mt.m_mat[3][2] = world_pos.m_z;
	}

	void RenderList::WorldToCamera(const Camera &cam)
	{
		for (size_t vertex = 0; vertex < m_facePtrs.size(); ++vertex)
		{
			if (m_facePtrs[vertex] != NULL || !(m_facePtrs[vertex]->m_attr & POLY4DV1_STATE_ACTIVE) || m_facePtrs[vertex]->m_attr & POLY4DV1_STATE_CLIPPED || m_facePtrs[vertex]->m_attr & POLY4DV1_STATE_BACKFACE) continue;

			CommonMath::V4dMulMat44(m_facePtrs[vertex]->m_tvlist[0], cam.m_cam, m_facePtrs[vertex]->m_tvlist[0]);
			CommonMath::V4dMulMat44(m_facePtrs[vertex]->m_tvlist[1], cam.m_cam, m_facePtrs[vertex]->m_tvlist[1]);
			CommonMath::V4dMulMat44(m_facePtrs[vertex]->m_tvlist[2], cam.m_cam, m_facePtrs[vertex]->m_tvlist[2]);
		}
	}
	
} //T3D
