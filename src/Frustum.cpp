#include "Frustum.h"

namespace T3D {

	Frustum::Frustum() : m_near(0.1f), m_far(1000.0f), m_fov(90), m_aspect(1.3333f), m_projType(PT_PERSPECTIVE)
	{

	}

	Frustum::Frustum(const Frustum &rhs)
	{

	}

	Frustum::Frustum(float near, float far, float xfov, float yfov, bool ortho /*= false*/)
	{

	}

	Frustum::~Frustum()
	{

	}

	void Frustum::SetProjType(ProjectionType type)
	{
		m_projType = type;
	}

	void Frustum::updateFrustum()
	{

	}

	bool Frustum::operator==(const Frustum &rhs)
	{

	}

	T3D::Frustum & Frustum::operator=(const Frustum &rhs)
	{

	}

}