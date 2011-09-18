project(k8json)

message(STATUS "Searching k8json sources and headers")

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../k8json)

# Search for source and headers in source directory
file(GLOB SRC "${SRC_DIR}/*.cpp")
file(GLOB HDR "${SRC_DIR}/*.h")

list(APPEND HDR json.h)
list(APPEND SRC json.cpp)

wrap_cpp(MOC_SRC ${HDR})

# This project will generate library
add_library(k8json SHARED ${SRC} ${MOC_SRC} ${HDR} ${UIS_H})

include_directories(${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
)

update_compiler_flags(k8json)
add_definitions(-DJSON_LIBRARY)

target_link_libraries(k8json
	${QT_LIBRARIES}
	)

install(TARGETS k8json
	RUNTIME DESTINATION ${BIN_DIR_DEF}
	LIBRARY DESTINATION lib${LIB_SUFFIX}
	ARCHIVE DESTINATION lib${LIB_SUFFIX}
)
