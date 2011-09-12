project(kqoauth)

message(STATUS "Searching kqoauth sources and headers")

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../kqoauth/src/)

# Search for source and headers in source directory
file(GLOB_RECURSE SRC "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE HDR "${SRC_DIR}/*.h")
file(GLOB_RECURSE FORMS "${SRC_DIR}/*.ui")

wrap_cpp(MOC_SRC ${HDR})
qt4_wrap_ui(UIS_H ${FORMS})

# This project will generate library
add_library(kqoauth SHARED ${SRC} ${MOC_SRC} ${HDR} ${UIS_H})

include_directories(${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
)

update_compiler_flags(kqoauth)

target_link_libraries(kqoauth
	${QT_LIBRARIES}
	)

install(TARGETS kqoauth
	RUNTIME DESTINATION ${BIN_DIR_DEF}
	LIBRARY DESTINATION lib${LIB_SUFFIX}
	ARCHIVE DESTINATION lib${LIB_SUFFIX}
)
