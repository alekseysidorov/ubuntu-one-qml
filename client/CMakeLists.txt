project(ubuntuNotes)

message(STATUS "Searching client sources and headers")
# Search for source and headers in source directory

if(HARMATTAN)
    set(CLIENT_TYPE meego)
    message(STATUS "Using meego harmattan client")
else()
    set(CLIENT_TYPE desktop)
    list(APPEND QML_MODULES QtDesktop)
    message(STATUS "Using desktop client")
endif()

set(QML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/qml/${CLIENT_TYPE}")

file(GLOB_RECURSE SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HDR "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB_RECURSE FORMS "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")
qt4_wrap_ui(UIS_H ${FORMS})
moc_wrap_cpp(MOC_SRCS ${HDR})

if(APPLE)
    # set how it shows up in the Info.plist file
    SET(MACOSX_BUNDLE_INFO_STRING "TODO")
    SET(MACOSX_BUNDLE_LONG_VERSION_STRING "0.1")
    SET(MACOSX_BUNDLE_BUNDLE_NAME "ubuntuNotes")
    SET(MACOSX_BUNDLE_BUNDLE_VERSION "0.1")
endif()

# This project will generate library
add_executable(ubuntuNotes WIN32 MACOSX_BUNDLE ${SRC} ${HDR} ${UIS_H} ${QML_DIR} ${MOC_SRCS})

include_directories(${CMAKE_CURRENT_BINARY_DIR}
    .
    ..
    ../3rdparty
    ${CMAKE_CURRENT_SOURCE_DIR}
)

update_compiler_flags(ubuntuNotes)
target_link_libraries(ubuntuNotes ${QT_LIBRARIES} ${QT_QTMAIN_LIBRARY})

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

install(TARGETS ubuntuNotes
    RUNTIME DESTINATION ${BINDIR}
    LIBRARY DESTINATION ${LIBDIR}
    ARCHIVE DESTINATION ${LIBDIR}
    BUNDLE DESTINATION .
)
install(DIRECTORY ${QML_DESKTOP_CLIENT_DIR} DESTINATION ${SHAREDIR}/qml)

if(CREATE_BUNDLE)
    set(APPS ${BUNDLE_PATH})
    list(APPEND DIRS
        ${QT_LIBRARY_DIR}
        ${CMAKE_INSTALL_PREFIX}/${LIBDIR}
    )
    if(WIN32)
        get_filename_component(_dir ${QT_QMAKE_EXECUTABLE} PATH)
        list(APPEND DIRS ${_dir})
    endif()

    list(APPEND QML_MODULES
        Qt
        QtDesktop
    )

    list(APPEND QT_PLUGINS
        bearer/qgenericbearer
        bearer/qnativewifibearer
        codecs/qcncodecs
        codecs/qjpcodecs
        codecs/qjpcodecs
        codecs/qkrcodecs
        codecs/qtwcodecs
        imageformats/qsvg
        imageformats/qgif
        imageformats/qjpeg
        imageformats/qico
        imageformats/qmng
        imageformats/qtga
        imageformats/qtiff
        iconengines/qsvgicon
		sqldrivers/qsqlite
        crypto/qca-ossl
    )

    deploy_qml_modules(${QML_MODULES})
    deploy_qt_plugins(${QT_PLUGINS})

    INSTALL(CODE "
        file(GLOB_RECURSE QTPLUGINS
          \"\${CMAKE_INSTALL_PREFIX}/*${CMAKE_SHARED_LIBRARY_SUFFIX}\")
        include(BundleUtilities)
        fixup_bundle(\"${APPS}\" \"\${QTPLUGINS}\" \"${DIRS}\")
        " COMPONENT Runtime)
endif()
