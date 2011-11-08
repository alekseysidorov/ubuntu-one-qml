project(client)

message(STATUS "Searching client sources and headers")
# Search for source and headers in source directory

check_qml_module(desktopHarmattan HARMATTAN)

if(${HARMATTAN} STREQUAL "FOUND")
    set(CLIENT_TYPE meego)
else()
    set(CLIENT_TYPE desktop)
endif()

set(QML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/qml/${CLIENT_TYPE}")

file(GLOB_RECURSE SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HDR "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB_RECURSE FORMS "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")
qt4_wrap_ui(UIS_H ${FORMS})

if(APPLE)
    # set how it shows up in the Info.plist file
    SET(MACOSX_BUNDLE_INFO_STRING "Foo")
    SET(MACOSX_BUNDLE_LONG_VERSION_STRING "0.1")
    SET(MACOSX_BUNDLE_BUNDLE_NAME "ubuntuOne")
    SET(MACOSX_BUNDLE_BUNDLE_VERSION "0.1")
endif()

# This project will generate library
add_executable(client WIN32 MACOSX_BUNDLE ${SRC} ${HDR} ${UIS_H} ${QML_DIR})

include_directories(${CMAKE_CURRENT_BINARY_DIR}
    .
    ..
    ../3rdparty
    ${CMAKE_CURRENT_SOURCE_DIR}
)


if(WIN32)
    set(QT_USE_QTMAIN TRUE)
endif(WIN32)

update_compiler_flags(client)
target_link_libraries(client ${QT_LIBRARIES})

add_custom_target(qml-${CLIENT_TYPE}
	ALL
	DEPENDS ${QML}
)

if(APPLE)
        set(QML_DESKTOP_CLIENT_DIR "${CMAKE_CURRENT_BINARY_DIR}/${BUNDLE_NAME}/Contents/Resources/qml/client")
else()
	set(QML_DESKTOP_CLIENT_DIR "${CMAKE_CURRENT_BINARY_DIR}/qml/client")
endif()

add_custom_command(
	TARGET		qml-${CLIENT_TYPE}
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
    RUNTIME DESTINATION ${BINDIST}
    LIBRARY DESTINATION ${LIBDIST}
    ARCHIVE DESTINATION ${LIBDIST}
    BUNDLE DESTINATION .
)
install(DIRECTORY ${QML_DESKTOP_CLIENT_DIR} DESTINATION ${SHAREDIR}/qml)

#--------------------------------------------------------------------------------
# Now the installation stuff below
#--------------------------------------------------------------------------------
SET(plugin_dest_dir bin)
SET(qtconf_dest_dir bin)
SET(APPS "\${CMAKE_INSTALL_PREFIX}/bin/client")
IF(APPLE)
  SET(plugin_dest_dir client.app/Contents/MacOS)
  SET(qtconf_dest_dir client.app/Contents/Resources)
  SET(APPS "\${CMAKE_INSTALL_PREFIX}/client.app")
ENDIF(APPLE)
IF(WIN32)
  SET(APPS "\${CMAKE_INSTALL_PREFIX}/bin/client.exe")
ENDIF(WIN32)

INSTALL(DIRECTORY "${QT_PLUGINS_DIR}/imageformats" DESTINATION ${PLUGINSDIR} COMPONENT Runtime)
INSTALL(DIRECTORY "${QT_PLUGINS_DIR}/crypto" DESTINATION ${PLUGINSDIR} COMPONENT Runtime)
#INSTALL(DIRECTORY "${QT_IMPORTS_DIR}/Qt" DESTINATION ${BINDIR} COMPONENT Runtime)

# fixup the bundle
SET(DIRS ${QT_LIBRARY_DIRS})

INSTALL(CODE "
    file(GLOB_RECURSE QTPLUGINS
      \"\${CMAKE_INSTALL_PREFIX}/*${CMAKE_SHARED_LIBRARY_SUFFIX}\")
    include(BundleUtilities)
    fixup_bundle(\"${APPS}\" \"\${QTPLUGINS}\" \"${DIRS}\")
    " COMPONENT Runtime)
