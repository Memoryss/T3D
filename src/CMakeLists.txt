

include_directories(${CMAKE_SOURCE_DIR}/dep/tmath/src)
include_directories(${CMAKE_SOURCE_DIR}/dep/assimp/include)
include_directories(${CMAKE_SOURCE_DIR}/dep/glog/include)

set (PUB_HDR
	Mesh.h
	Vertex.h
	Texture.h
	Model.h
	Color.h
	Camera.h
	Vertex.h
	Node.h
	Shader.h
	BasicShaders.h
	Scene.h
	T3DMath.h
	T3DLog.h
	T3DMesh.h
	T3DUtil.h
	T3DCamera.h
	T3DDevice.h
	T3DWindow.h
	T3DRasterizer.h
	Rasterizer.h
	Renderer.h
)

add_library(T3DEngine
	Vertex.cpp
	Texture.cpp
	Model.cpp
	Mesh.cpp
	Camera.cpp
	Vertex.cpp
	Node.cpp
	BasicShaders.cpp
	Scene.cpp
	T3DMath.cpp
	T3DLog.cpp
	T3DMesh.cpp
	T3DUtil.cpp
	T3DCamera.cpp
	T3DDevice.cpp
	T3DWindow.cpp
	T3DRasterizer.cpp
	Rasterizer.cpp
	Renderer.cpp
	${PUB_HDR}
)

set_target_properties (T3DEngine PROPERTIES
  DEBUG_POSTFIX "_d"
  PUBLIC_HEADER "${PUB_HDR}"
  )

install (TARGETS T3DEngine
	ARCHIVE DESTINATION lib
	PUBLIC_HEADER DESTINATION include/T3DEngine)