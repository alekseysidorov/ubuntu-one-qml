project(client)

message(STATUS "Searching client sources and headers")
# Search for source and headers in source directory

set(QML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/qml")

file(GLOB_RECURSE SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HDR "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB_RECURSE FORMS "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")

wrap_cpp(MOC_SRC ${HDR})
qt4_wrap_ui(UIS_H ${FORMS})

# This project will generate library
add_executable(client ${SRC} ${MOC_SRC} ${HDR} ${UIS_H} ${QML_DIR} ${QML})

include_directories(${CMAKE_CURRENT_BINARY_DIR}
	.
	..
	../3rdparty
	${CMAKE_CURRENT_SOURCE_DIR}
)

update_compiler_flags(client)

target_link_libraries(client
	${QT_LIBRARIES}
	)

add_custom_command(
	TARGET		client
	POST_BUILD
	COMMAND		${CMAKE_COMMAND}
	ARGS		-E copy_directory "${QML_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/qml/client"
)

install(TARGETS client
	RUNTIME DESTINATION ${BIN_DIR_DEF}
	LIBRARY DESTINATION lib${LIB_SUFFIX}
	ARCHIVE DESTINATION lib${LIB_SUFFIX}
)

