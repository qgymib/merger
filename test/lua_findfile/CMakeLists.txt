add_test(NAME lua_findfile
    COMMAND $<TARGET_FILE:lua-5.4.4> ${JUDGE_SCRIPT}
        --pattern=${CMAKE_CURRENT_SOURCE_DIR}/findfile_1.pattern
        --matcher=${CMAKE_CURRENT_BINARY_DIR}/findfile_1.out
        --
        $<TARGET_FILE:merger>
        -c ${CMAKE_CURRENT_SOURCE_DIR}/findfile_1.lua
        -o ${CMAKE_CURRENT_BINARY_DIR}/findfile_1.out
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
