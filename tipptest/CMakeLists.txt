cmake_minimum_required(VERSION 3.19)
project(tipptest LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(tipptest
    WIN32 MACOSX_BUNDLE
        src/source/main.cpp
        src/source/mainwindow.cpp
        src/header/mainwindow.h

        src/header/character.h src/source/character.cpp
        src/header/countdown.h src/source/countdown.cpp
        src/source/CustomScrollArea.cpp
        src/header/CustomScrollArea.h


)

target_link_libraries(tipptest
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS tipptest
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET tipptest
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
