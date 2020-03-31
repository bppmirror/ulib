cmake_minimum_required(VERSION 3.5)

if (BPP_PLATFORM MATCHES esp32)
    set(APP_SRC ${APP_SRC} 
        ${CMAKE_CURRENT_SOURCE_DIR}/esp32.cpp
        PARENT_SCOPE)
else()
    set(APP_SRC ${APP_SRC} 
        ${CMAKE_CURRENT_SOURCE_DIR}/pc.cpp
        PARENT_SCOPE)
endif()
