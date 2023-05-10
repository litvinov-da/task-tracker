find_package(Qt5 REQUIRED COMPONENTS Core Widgets Network)

set(SOURCES
    "main.cpp"
    "mainwindow.cpp"
    "mainwindow.h"
    "mainwindow.ui"
    "createnewtaskdialog.cpp"
    "createnewtaskdialog.h"
    "createnewtaskdialog.ui"
    )

add_executable(Client
    ${SOURCES}
)

target_link_libraries(Client PUBLIC actionCode)
target_link_libraries(Client PRIVATE Qt5::Core Qt5::Widgets Qt5::Network)
