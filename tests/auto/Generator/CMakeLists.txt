
project( test.generator )

set( SRC main.cpp
	custom.hpp
	${CMAKE_CURRENT_BINARY_DIR}/test.hpp )

file( COPY test.cfg
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )

add_custom_command( OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/test.hpp
	PRE_BUILD
	COMMAND ${CMAKE_CURRENT_BINARY_DIR}/../../../generator/cfgfile.generator -i test.cfgfile -o ${CMAKE_CURRENT_BINARY_DIR}/test.hpp
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
    
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/../../..
	${CMAKE_CURRENT_BINARY_DIR} )

add_executable( test.generator ${SRC} )

add_test( NAME test.generator
	COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test.generator
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} )
