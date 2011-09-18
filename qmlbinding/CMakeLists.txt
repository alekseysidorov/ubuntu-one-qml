project(qmlbinding)

message(STATUS "Searching qmlbinding sources and headers")
# Search for source and headers in source directory
file(GLOB_RECURSE SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HDR "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB_RECURSE FORMS "${CMAKE_CURRENT_SOURCE_DIR}/*.ui" )
set(QMLDIR "${CMAKE_CURRENT_SOURCE_DIR}/qmldir")

wrap_cpp(MOC_SRC ${HDR})
qt4_wrap_ui(UIS_H ${FORMS})

# This project will generate library
add_library(qmlbinding MODULE ${SRC} ${MOC_SRC} ${HDR} ${UIS_H})

include_directories(${CMAKE_CURRENT_BINARY_DIR}
	.
	..
	${CMAKE_CURRENT_SOURCE_DIR}
	../3rdparty/kqoauth/src
	../3rdparty/k8json-build/
)

update_compiler_flags(qmlbinding)

target_link_libraries(qmlbinding
	kqoauth
	k8json
	${QT_LIBRARIES}
	)

add_custom_command(
	TARGET		qmlbinding
	POST_BUILD
	COMMAND		${CMAKE_COMMAND}
	ARGS		-E copy_if_different "${QMLDIR}" "${CMAKE_CURRENT_BINARY_DIR}"
)

set(QT_DECLARATIVE_IMPORT imports)
set(IMPORT_DESTINATION ${QT_DECLARATIVE_IMPORT}/evernote)

install(TARGETS qmlbinding
	LIBRARY DESTINATION ${IMPORT_DESTINATION}
)

install(FILES ${QMLDIR}
	DESTINATION ${IMPORT_DESTINATION}
)
