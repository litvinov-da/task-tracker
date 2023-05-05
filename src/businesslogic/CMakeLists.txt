find_package(Qt5 REQUIRED COMPONENTS Core)

set(SOURCES
    employee.cpp
    employee.h
    task.cpp
    task.h
    )

add_library(business_logic
    ${SOURCES}
    )

target_link_libraries(business_logic PRIVATE Qt5::Core)
