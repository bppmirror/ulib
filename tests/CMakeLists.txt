cmake_minimum_required(VERSION 3.5)
set(APP_SRC ${APP_SRC} 
        ${CMAKE_CURRENT_SOURCE_DIR}/list.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/str.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/strstream.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/observer.cpp
        PARENT_SCOPE)

if (WITH_ULIB_TESTS)
    set(APP_SRC ${APP_SRC}        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
    add_subdirectory(wrappers)
endif()