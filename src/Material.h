#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <vector>

#include <Vector.h>
#include "Color.h"


namespace T3D {
	
	class Texture;

	class Material
	{
	public:
		Material();
		~Material();

		Color m_specular = { 0.f, 0.f, 0.f, 1.f };
		Color m_diffuse = { 0.f, 0.f, 0.f, 1.f };
		Color m_ambient = { 0.f, 0.f, 0.f, 1.f };
		Color m_transmittance = { 0.f, 0.f, 0.f, 1.f };
		
		float m_shininess;
		float m_ior; //index of refraction
		float m_dissolve; //1 == opaque 0 == fully transparent

		int m_illum;

		int dummy;  //Suppress padding warning

		std::string m_ambient_texname;  //map_ka
		std::string m_diffuse_texname;  //map_kd
		std::string m_specular_texname; //map_ks
		std::string m_specular_highlight_texname; //map_ns
		std::string m_bump_texname; //map_bump, bump
		std::string m_displacement_texname; //disp
		std::string m_alpha_texname; //map_d

		//pbr
		Color m_emission = { 0.f, 0.f, 0.f, 1.f };
		float m_roughness = 0.f;            // [0, 1] default 0
		float m_metallic = 0.f;             // [0, 1] default 0
		float m_sheen = 0.f;                // [0, 1] default 0
		float m_clearcoat_thickness = 0.f;  // [0, 1] default 0
		float m_clearcoat_roughness = 0.f;  // [0, 1] default 0
		float m_anisotropy = 0.f;           // aniso. [0, 1] default 0
		float m_anisotropy_rotation = 0.f;  // anisor. [0, 1] default 0
		float m_pad0;
		float m_pad1;
		std::string roughness_texname;  // map_Pr
		std::string metallic_texname;   // map_Pm
		std::string sheen_texname;      // map_Ps
		std::string emissive_texname;   // map_Ke
		std::string normal_texname;     // norm. For normal mapping.

		float m_d = 1.0;  //渐隐指数   0.0~1.0   0.0 表示完全透明，1.0表示完全不透明
		float m_ns = 500; //反射指数   0~1000   值越高 高光越密集
		float m_sharpness = 500; //清晰度  0~1000 越大越清晰
		float m_ni = 1.0; //折射度   0.001 ~ 10   1.0光通过的不发生弯曲  玻璃的折射率是1.5

		std::string m_mapKd; 
		std::string m_mapKa;
		std::string m_mapKs;

		std::vector<Texture *> m_textures;
	};

}

#endif