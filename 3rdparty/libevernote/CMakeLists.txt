project(libevernote)

find_package(Thrift REQUIRED)
message(STATUS "Searching libevernote sources and headers")
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
# Search for source and headers in source directory
file(GLOB_RECURSE SRC "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE HDR "${SRC_DIR}/*.h")

# This project will generate library
add_library(libevernote SHARED ${SRC} ${MOC_SRC} ${HDR} ${UIS_H})

include_directories(${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
	${THRIFT_INCLUDE_DIRS}
)

update_compiler_flags(libevernote)

target_link_libraries(libevernote
	${THRIFT_LIBRARIES}
	)

install(TARGETS libevernote
	RUNTIME DESTINATION ${BIN_DIR_DEF}
	LIBRARY DESTINATION lib${LIB_SUFFIX}
	ARCHIVE DESTINATION lib${LIB_SUFFIX}
)

install(FILES ${HDR}
	DESTINATION include/libevernote
)
