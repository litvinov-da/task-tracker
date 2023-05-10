find_package(Qt5 REQUIRED COMPONENTS Core Sql Network)

set(SOURCES "main.cpp"
    "server.cpp"
    "server.h"
    "logger.h"
    "loggingcategories.h"
    "loggingcategories.cpp"
    "consolelogger.cpp"
    "consolelogger.h"
    )

add_executable(Server
    ${SOURCES}
)

set(QT_DEBUG_PLUGINS True)

target_link_libraries(Server PRIVATE Qt5::Core Qt5::Network Qt5::Sql)
