cmake_minimum_required(VERSION 3.31)

project(txt LANGUAGES C)

set(SOURCES
	main.c
	txt.c
	util.c
)

set(GLAD ${CMAKE_SOURCE_DIR}/lib/glad.c)

find_library(GLFW NAMES glfw3 HINTS ${CMAKE_SOURCE_DIR}/lib/)

add_executable(${PROJECT_NAME} ${SOURCES} ${GLAD})

set_target_properties(${PROJECT_NAME} PROPERTIES EXPORT_COMPILE_COMMANDS ON)

target_link_libraries(${PROJECT_NAME} ${GLFW})

target_include_directories(${PROJECT_NAME}
	PRIVATE ${CMAKE_SOURCE_DIR}/
	PUBLIC ${CMAKE_SOURCE_DIR}/include/
)

