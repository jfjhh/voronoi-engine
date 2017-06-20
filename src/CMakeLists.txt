# Create entries for target: `voronoi`.
#######################################

add_executable(voronoi
	apollonius.h
	apollonius.cpp
	bullet.cpp
	bulletdata.cpp
	bulletdata.h
	bullet.h
	circle.cpp
	circle.h
	common.h
	commont.h
	danmaku.cpp
	danmaku.h
	ellipse.cpp
	ellipse.h
	geometry.h
	main.cpp
	player.cpp
	player.h
	pobject.cpp
	pobject.h
	point.cpp
	point.h
	polygon.cpp
	polygon.h
	ptexture.cpp
	ptexture.h
	ptimer.cpp
	ptimer.h
	range.h
	rectangle.cpp
	rectangle.h
	shape.cpp
	shape.h
	stage.cpp
	stage.h
	unionshape.cpp
	unionshape.h
	vertex.cpp
	vertex.h
	)
add_sanitizers(voronoi)

# add_to_cached_list(CGAL_EXECUTABLE_TARGETS voronoi)

# Link the executable to CGAL and third-party libraries
include_directories(
	${SDL2_INCLUDE_DIR}
	${SDL2_IMAGE_INCLUDE_DIR}
	${SDL2TTF_INCLUDE_DIR}
	${SDL2GFX_INCLUDE_DIR}
	)
target_link_libraries(
	voronoi
	${CGAL_LIBRARIES}
	${CGAL_3RD_PARTY_LIBRARIES}
	${SDL2_LIBRARY}
	${SDL2_IMAGE_LIBRARY}
	${SDL2TTF_LIBRARY}
	${SDL2GFX_LIBRARY}
	)

