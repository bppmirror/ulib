cmake_minimum_required(VERSION 3.5)

add_subdirectory(wrappers)

set(APP_SRC ${APP_SRC} 
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/list.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/str.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/strstream.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/observer.cpp
        PARENT_SCOPE)
