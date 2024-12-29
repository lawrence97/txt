cmake_minimum_required(VERSION 3.31)

project(txt LANGUAGES C)

set(SOURCES
	main.c
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
	PRIVATE ${CMAKE_SOURCE_DIR}/
	PUBLIC ${CMAKE_SOURCE_DIR}/include/
)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	EXPORT_COMPILE_COMMANDS ON
)
