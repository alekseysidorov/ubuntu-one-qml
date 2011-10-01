include(CheckCXXCompilerFlag)

macro(WRAP_CPP outfiles)
	# get include dirs
	QT4_GET_MOC_FLAGS(moc_flags)
	QT4_EXTRACT_OPTIONS(moc_files moc_options ${ARGN})

	foreach(it ${moc_files})
		get_filename_component(_abs_FILE ${it} ABSOLUTE)
		get_filename_component(_abs_PATH ${_abs_FILE} PATH)
		get_filename_component(_basename ${it} NAME_WE)

		set(_HAS_MOC false)

		if(EXISTS ${_abs_PATH}/${_basename}.cpp)
			set(_header ${_abs_PATH}/${_basename}.cpp)
			file(READ ${_header} _contents)
			string(REGEX MATCHALL "# *include +[^ ]+\\.moc[\">]" _match "${_contents}")
			if(_match)
				set(_HAS_MOC true)
				foreach(_current_MOC_INC ${_match})
					string(REGEX MATCH "[^ <\"]+\\.moc" _current_MOC "${_current_MOC_INC}")
					set(_moc    ${CMAKE_CURRENT_BINARY_DIR}/${_current_MOC})
					QT4_CREATE_MOC_COMMAND(${_abs_FILE} ${_moc} "${_moc_INCS}" "")
					macro_add_file_dependencies(${_abs_FILE} ${_moc})
				endforeach(_current_MOC_INC)
			endif()
		endif()
		if(NOT _HAS_MOC)
			file(READ ${_abs_FILE} _contents)
			string(REGEX MATCHALL "Q_OBJECT" _match2 "${_contents}")
			if(_match2)
				qt4_make_output_file(${_abs_FILE} moc_ cxx outfile)
				qt4_create_moc_command(${_abs_FILE} ${outfile} "${moc_flags}" "${moc_options}")
				set(${outfiles} ${${outfiles}} ${outfile})
			endif()
		endif()
	endforeach(it)
endmacro(WRAP_CPP)

macro(UPDATE_CXX_COMPILER_FLAG flag name)
	check_cxx_compiler_flag(${flag} COMPILER_SUPPORTS_${name}_FLAG)
	if(COMPILER_SUPPORTS_${name}_FLAG)
		add_definitions(${flag})
	endif()
endmacro()

macro(UPDATE_COMPILER_FLAGS target)

	if(MSVC)
		list(APPEND COMPILER_FLAGS "/W3")
	else()
		list(APPEND COMPILER_FLAGS "-Wall -Wextra -Wnon-virtual-dtor")
	endif()

	update_cxx_compiler_flag("-std=c++0x" CXX_0X)
        if(NOT APPLE)
                update_cxx_compiler_flag("-stdlib=libc++" LIBCXX)
        endif()
	update_cxx_compiler_flag("-fvisibility=hidden" HIDDEN_VISIBILITY)

        get_target_property(${target}_TYPE ${target} TYPE)
        if (${target}_TYPE STREQUAL "STATIC_LIBRARY")
            update_cxx_compiler_flag("-fPIC" PIC)
        endif()

	set_target_properties(${target} PROPERTIES COMPILE_FLAGS "${COMPILER_FLAGS}")
endmacro()

#Простейший макрос
macro(ADD_SIMPLE_LIBRARY target)
	message(STATUS "Searching ${target} source and headers")

	# Search for source and headers in source directory
	file(GLOB_RECURSE SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
	file(GLOB_RECURSE HDR "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
	file(GLOB_RECURSE FORMS "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")
	if (apple)
		file(GLOB_RECURSE SOURCES_MM RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/" "${CMAKE_CURRENT_SOURCE_DIR}/*.mm" )
		list(APPEND SOURCE SOURCE_MM} )
	endif()

	wrap_cpp(MOC_SRC ${HDR})
	qt4_wrap_ui(UIS_H ${FORMS})

	# This project will generate library
	add_library(${target} STATIC ${SRC} ${MOC_SRC} ${HDR} ${UIS_H} ${SOURCE_MM})

	include_directories(${CMAKE_CURRENT_BINARY_DIR}
		.
	)

	update_compiler_flags_library(${target})

	TARGET_LINK_LIBRARIES (${target}
		${QT_LIBRARIES}
		)

	INSTALL(TARGETS ${target}
		RUNTIME DESTINATION ${BIN_DIR_DEF}
		LIBRARY DESTINATION lib${LIB_SUFFIX}
		ARCHIVE DESTINATION lib${LIB_SUFFIX}
	)
endmacro()

#Вытаскиваем у таргета location и дописываем в список
macro(APPEND_TARGET_LOCATION target list)
        get_target_property(${target}_LOCATION ${target} LOCATION)
        list(APPEND ${list} ${${target}_LOCATION})
endmacro()
