cmake_minimum_required(VERSION 3.2)
project(merger)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_subdirectory(third_party)

# add source files
add_executable(${PROJECT_NAME}
    "src/file.c"
    "src/lua_api.c"
    "src/lua_findfile.c"
    "src/lua_finialize.c"
    "src/lua_readfile.c"
    "src/lua_sha256.c"
    "src/main.c"
    "src/map.c"
    "src/misc.c"
    "src/runtime.c"
    "src/sha256.c")

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        lua5.4.4)

# define target include search paths
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src)

function(setup_target_wall name)
    if (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${name} PRIVATE /W4 /WX)
    else ()
        target_compile_options(${name} PRIVATE -Wall -Wextra -Werror)
    endif ()
endfunction()

# add warning check
setup_target_wall(${PROJECT_NAME})

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(test)
endif()
