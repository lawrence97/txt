cmake_minimum_required(VERSION 3.31)

project(txt LANGUAGES C)

set(SOURCES
	main.c
	txt.c
	util.c
)

set(GLAD ${CMAKE_SOURCE_DIR}/lib/glad.c)
set(STB_IMAGE ${CMAKE_SOURCE_DIR}/lib/stb_image.c)

find_library(GLFW NAMES glfw3 HINTS ${CMAKE_SOURCE_DIR}/lib/)

add_compile_definitions(RES_DIR="${CMAKE_SOURCE_DIR}/")

add_executable(${PROJECT_NAME} ${SOURCES} ${GLAD} ${STB_IMAGE})

set_target_properties(${PROJECT_NAME} PROPERTIES EXPORT_COMPILE_COMMANDS ON)

target_link_libraries(${PROJECT_NAME} ${GLFW})

target_include_directories(${PROJECT_NAME}
	PRIVATE ${CMAKE_SOURCE_DIR}/
	PUBLIC ${CMAKE_SOURCE_DIR}/include/
)

