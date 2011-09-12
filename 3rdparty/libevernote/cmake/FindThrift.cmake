include(FindPkgConfig)

pkg_check_modules(THRIFT thrift)

message(STATUS ${THRIFT_INCLUDE_DIRS})