cmake_minimum_required(VERSION 3.18)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) #for intellisense


project(TwoClocks VERSION 0.1.0)

if(NOT APPLE)
    message("Error, currenly only mac is supported")
    return()
endif()


if(${CMAKE_VERSION} VERSION_LESS "3.18.0")
    message("Please consider to switch to CMake 3.18.0")
endif()

add_subdirectory(vendor/SDL)

add_executable(TwoClocks
	src/main.c
	src/glyph.c
	src/load_bmp.c
	src/print_time.c
	src/core.c
	src/convert_string_to_int.c
	src/audio.m
	src/construct_absolute_paths.c)



add_library(commongWarnings INTERFACE)

target_compile_options(commongWarnings
	INTERFACE "-Wall"
    INTERFACE "-Wextra"
    INTERFACE "-pedantic"
    INTERFACE "-Wconversion"
    INTERFACE "-Wcast-align"
    INTERFACE "-Wunused"
    INTERFACE "-Wshadow"
    INTERFACE "-Wold-style-cast"
    INTERFACE "-Wpointer-arith"
    INTERFACE "-Wmissing-prototypes"
    INTERFACE "-Wno-missing-braces"
    INTERFACE "-Werror"
    INTERFACE "-Wno-deprecated" # only because apple deprecated tons of things
    # INTERFACE "-fsanitize=address"
    # INTERFACE "-fno-omit-frame-pointer" 
)

# target_link_options(commongWarnings

# 	INTERFACE "-fsanitize=address"
#     INTERFACE "-fno-omit-frame-pointer")


target_include_directories(TwoClocks PRIVATE include)
target_include_directories(TwoClocks PRIVATE ${SDL2_INCLUDE_DIR})


target_link_libraries(TwoClocks
	PRIVATE SDL2main
	PRIVATE SDL2
	PRIVATE "-framework AppKit" #for playing Audio
	PRIVATE commongWarnings
)

set_target_properties(TwoClocks PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY_DEBUG    ${CMAKE_CURRENT_LIST_DIR}/bin/Debug
	RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${CMAKE_CURRENT_LIST_DIR}/bin/Release
	LIBRARY_OUTPUT_DIRECTORY_DEBUG    ${CMAKE_CURRENT_LIST_DIR}/bin/Debug
	LIBRARY_OUTPUT_DIRECTORY_RELEASE  ${CMAKE_CURRENT_LIST_DIR}/bin/Release
	ARCHIVE_OUTPUT_DIRECTORY_DEBUG    ${CMAKE_CURRENT_LIST_DIR}/bin/Debug
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE  ${CMAKE_CURRENT_LIST_DIR}/bin/Release
	C_STANDARD 99
)




#copying compile commands.json
set(copySource ${CMAKE_CURRENT_LIST_DIR}/build/compile_commands.json)
set(copyDest ${CMAKE_CURRENT_LIST_DIR})
add_custom_command(TARGET TwoClocks
	POST_BUILD
	COMMAND cp ${copySource} ${copyDest}
	COMMENT "Copying ${copySource} to the ${copyDest}"
)


