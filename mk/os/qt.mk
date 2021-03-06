set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5 COMPONENTS Core REQUIRED)

set (TARGET_LIBS, ${TARGET_LIBS} Qt5::Core)

add_definitions(-DBPP_OS_QT -std=c++11)

message (STATUS "OS: Qt")
