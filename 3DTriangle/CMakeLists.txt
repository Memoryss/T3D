

include_directories(${CMAKE_INSTALL_PREFIX}/include)


add_executable(3DTriangle WIN32
	main.cpp
)

set_target_properties (3DTriangle PROPERTIES
  DEBUG_POSTFIX "_d"
  )

target_link_libraries(3DTriangle T3DEngine)
