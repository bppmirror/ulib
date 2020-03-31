cmake_minimum_required(VERSION 3.5)

find_package(Qt5 COMPONENTS REQUIRED Core)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
#qt5_wrap_cpp(MOC_SRCS  ${CMAKE_CURRENT_SOURCE_DIR}/qtmutex.h ) 

set (ULIB_SRC ${ULIB_SRC}
    ${CMAKE_CURRENT_SOURCE_DIR}/qtmutex.cpp 
    ${MOC_SRCS}
    PARENT_SCOPE
    )


