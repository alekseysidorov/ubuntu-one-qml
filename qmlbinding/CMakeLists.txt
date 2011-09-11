project(qmlbinding)

message(STATUS "Searching qmlbinding sources and headers")
# Search for source and headers in source directory
FILE(GLOB_RECURSE SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
FILE(GLOB_RECURSE HDR "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
FILE(GLOB_RECURSE FORMS "${CMAKE_CURRENT_SOURCE_DIR}/*.ui" )

wrap_cpp(MOC_SRC ${HDR})
qt4_wrap_ui(UIS_H ${FORMS})

# This project will generate library
add_library(qmlbinding STATIC ${SRC} ${MOC_SRC} ${HDR} ${UIS_H})

include_directories(${CMAKE_CURRENT_BINARY_DIR}
	.
	..
	../3rdparty
	${CMAKE_CURRENT_SOURCE_DIR}
)

if(MSVC)
	list(APPEND COMPILER_FLAGS "/W3")
else()
	list(APPEND COMPILER_FLAGS "-Wall -Wextra -Wnon-virtual-dtor")
	if(NOT WIN32)
		#TODO возможно стоит использовать чекалку аттрибута -fvisibility
		set(COMPILER_FLAGS "${COMPILER_FLAGS} -fvisibility=hidden")
	endif(NOT WIN32)
endif()

set_target_properties(qmlbinding PROPERTIES COMPILE_FLAGS "${COMPILER_FLAGS}")

target_link_libraries(qmlbinding
	kqoauth
	${QT_LIBRARIES}
	)

install(TARGETS qmlbinding
	RUNTIME DESTINATION ${BIN_DIR_DEF}
	LIBRARY DESTINATION lib${LIB_SUFFIX}
	ARCHIVE DESTINATION lib${LIB_SUFFIX}
)
