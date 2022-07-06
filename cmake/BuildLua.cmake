option(LUA_ROOT "Root to lua source code")

set(lua_source
    ${LUA_ROOT}/src/lapi.c
    ${LUA_ROOT}/src/lcode.c
    ${LUA_ROOT}/src/lctype.c
    ${LUA_ROOT}/src/ldebug.c
    ${LUA_ROOT}/src/ldo.c
    ${LUA_ROOT}/src/ldump.c
    ${LUA_ROOT}/src/lfunc.c
    ${LUA_ROOT}/src/lgc.c
    ${LUA_ROOT}/src/llex.c
    ${LUA_ROOT}/src/lmem.c
    ${LUA_ROOT}/src/lobject.c
    ${LUA_ROOT}/src/lopcodes.c
    ${LUA_ROOT}/src/lparser.c
    ${LUA_ROOT}/src/lstate.c
    ${LUA_ROOT}/src/lstring.c
    ${LUA_ROOT}/src/ltable.c
    ${LUA_ROOT}/src/ltm.c
    ${LUA_ROOT}/src/lundump.c
    ${LUA_ROOT}/src/lvm.c
    ${LUA_ROOT}/src/lzio.c
    ${LUA_ROOT}/src/lauxlib.c
    ${LUA_ROOT}/src/lbaselib.c
    ${LUA_ROOT}/src/lcorolib.c
    ${LUA_ROOT}/src/ldblib.c
    ${LUA_ROOT}/src/liolib.c
    ${LUA_ROOT}/src/lmathlib.c
    ${LUA_ROOT}/src/loadlib.c
    ${LUA_ROOT}/src/loslib.c
    ${LUA_ROOT}/src/lstrlib.c
    ${LUA_ROOT}/src/ltablib.c
    ${LUA_ROOT}/src/lutf8lib.c
    ${LUA_ROOT}/src/linit.c 
)

add_library(lua5.4.4 ${lua_source})
target_include_directories(lua5.4.4
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${LUA_ROOT}/src>)
if(NOT WIN32)
    target_link_libraries(lua5.4.4
        PRIVATE
            m)
endif()

add_executable(lua-5.4.4 ${LUA_ROOT}/src/lua.c)
target_link_libraries(lua-5.4.4
    PRIVATE
        lua5.4.4)

add_executable(luac-5.4.4 ${LUA_ROOT}/src/luac.c)
target_link_libraries(luac-5.4.4
    PRIVATE
        lua5.4.4)
