cmake_minimum_required(VERSION 3.16)
project(cutie-phone-daemon VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(QT_DEFAULT_MAJOR_VERSION 6)

find_package(PkgConfig REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Quick)
pkg_check_modules(CUTIEMODEM cutiemodem REQUIRED IMPORTED_TARGET)

qt_standard_project_setup()

set(cutie-phone-daemon_SOURCES 
        src/main.cpp
        src/phone.cpp
        src/phone.h
)

qt_add_executable(cutie-phone-daemon ${cutie-phone-daemon_SOURCES})

target_include_directories(cutie-phone-daemon PUBLIC src)

target_link_libraries(cutie-phone-daemon PUBLIC Qt::Core Qt::Quick PkgConfig::CUTIEMODEM)

install(TARGETS cutie-phone-daemon RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
