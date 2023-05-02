find_package(Qt6 REQUIRED COMPONENTS Core Sql)

set(SOURCES "server.cpp")

add_executable(Server
    ${SOURCES}
)

target_link_libraries(Server PRIVATE Qt6::Core Qt6::Sql)
