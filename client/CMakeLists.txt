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
add_executable(client ${SRC} ${MOC_SRC} ${HDR} ${UIS_H} ${QML_DIR})

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

add_custom_target(qml-desktop
	ALL
	DEPENDS ${QML}
)

if(APPLE)
	set(QML_DESKTOP_CLIENT_DIR "${CMAKE_CURRENT_BINARY_DIR}/../Resources/qml/client")
else()
	set(QML_DESKTOP_CLIENT_DIR "${CMAKE_CURRENT_BINARY_DIR}/qml/client")
endif()

add_custom_command(
	TARGET		qml-desktop
	POST_BUILD
	COMMAND		${CMAKE_COMMAND}
	ARGS		-E copy_directory "${QML_DIR}" "${QML_DESKTOP_CLIENT_DIR}"
)

if(WIN32)
        append_target_location(k8json CLIENT_DEPEND_LIBS)
        append_target_location(qoauth CLIENT_DEPEND_LIBS)

        foreach(_lib ${CLIENT_DEPEND_LIBS})
                add_custom_command(
                        TARGET		client
                        POST_BUILD
                        COMMAND		${CMAKE_COMMAND}
                        ARGS		-E copy "${_lib}" "${CMAKE_CURRENT_BINARY_DIR}"
                )
        endforeach()
endif()

install(TARGETS client
	RUNTIME DESTINATION ${BIN_DIR_DEF}
	LIBRARY DESTINATION lib${LIB_SUFFIX}
	ARCHIVE DESTINATION lib${LIB_SUFFIX}
)

