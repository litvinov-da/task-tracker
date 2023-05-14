set(SOURCES
    actionCode.h
    employeeInfo.h
    taskInfo.h
    )

add_library(actionCode
    ${SOURCES}
    )

set_target_properties(actionCode PROPERTIES LINKER_LANGUAGE CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
