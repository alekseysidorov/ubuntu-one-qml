project(qmlbinding)

message(STATUS "Searching qmlbinding sources and headers")

set(QMLDIR "${CMAKE_CURRENT_SOURCE_DIR}/qmldir")
set(QML_OBJECT_LIST_DIR ../3rdparty/qml-object-model)

# Search for source and headers in source directory
file(GLOB_RECURSE SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HDR "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB_RECURSE RESOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.qrc")
file(GLOB_RECURSE QML "${QMLDIR}/*.*")


list(APPEND HDR ${QML_OBJECT_LIST_DIR}/qobjectlistmodel.h)
list(APPEND SRC ${QML_OBJECT_LIST_DIR}/qobjectlistmodel.cpp)
qt4_add_resources(RCC ${RESOURCES})
moc_wrap_cpp(MOC_SRCS ${HDR})

# This project will generate library
add_library(qmlbinding SHARED ${SRC} ${HDR} ${QML} ${RCC} ${MOC_SRCS})

include_directories(${CMAKE_CURRENT_BINARY_DIR}
    .
    ..
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../3rdparty/k8json-build/
    ../3rdparty/qoauth/include
    ${QML_OBJECT_LIST_DIR}
    ${QCA2_INCLUDE_DIR}
)

update_compiler_flags(qmlbinding)

target_link_libraries(qmlbinding
    k8json
    qoauth
    ${QT_LIBRARIES}
    )

add_custom_command(
    TARGET		qmlbinding
    POST_BUILD
    COMMAND		${CMAKE_COMMAND}
    ARGS		-E copy_if_different "${QMLDIR}" "${CMAKE_CURRENT_BINARY_DIR}"
)

set(IMPORT_DESTINATION ${IMPORTSDIR}/com.ubuntu.one)
install(TARGETS qmlbinding
    RUNTIME DESTINATION ${IMPORT_DESTINATION}
    LIBRARY DESTINATION ${IMPORT_DESTINATION}
)
install(FILES ${QMLDIR}
    DESTINATION ${IMPORT_DESTINATION}
)
