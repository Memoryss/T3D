set (PUB_HDR
	T3DMath.h
	T3DLog.h
	T3DMesh.h
	T3DUtil.h
	T3DCamera.h
	T3DDevice.h
	T3DWindow.h
	T3DRasterizer.h
)

add_library(T3DEngine
	T3DMath.cpp
	T3DLog.cpp
	T3DMesh.cpp
	T3DUtil.cpp
	T3DCamera.cpp
	T3DDevice.cpp
	T3DWindow.cpp
	T3DRasterizer.cpp
	${PUB_HDR}
)

set_target_properties (T3DEngine PROPERTIES
  DEBUG_POSTFIX "_d"
  PUBLIC_HEADER "${PUB_HDR}"
  )

install (TARGETS T3DEngine
	ARCHIVE DESTINATION lib
	PUBLIC_HEADER DESTINATION include/T3DEngine)