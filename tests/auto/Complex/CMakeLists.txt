
project( test.complex )

set( SRC main.cpp
	cfg.hpp
	cfg.cpp )

file( COPY all_is_ok.cfg
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
file( COPY all_is_ok_with_comments.cfg
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
file( COPY empty_file.cfg
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
file( COPY inconsistency_to_int_constraint.cfg
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
file( COPY inconsistency_to_string_constraint.cfg
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
file( COPY undefined_child_mandatory_tag.cfg
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
file( COPY undefined_mandatory_tag.cfg
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
    
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/../../.. )

add_executable( test.complex ${SRC} )

add_test( NAME test.complex
	COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test.complex
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} )
