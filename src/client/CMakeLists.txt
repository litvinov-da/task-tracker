find_package(Qt5 REQUIRED COMPONENTS Core)

set(SOURCES "client.cpp")

add_executable(Client
    ${SOURCES}
)

target_link_libraries(Client PRIVATE Qt5::Core)
