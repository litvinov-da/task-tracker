find_package(Qt5 REQUIRED COMPONENTS Core Widgets Network)

set(SOURCES
    "main.cpp"
    "client.cpp"
    "client.h"
    "client.ui")

add_executable(Client
    ${SOURCES}
)

target_link_libraries(Client PRIVATE Qt5::Core Qt5::Widgets Qt5::Network)
