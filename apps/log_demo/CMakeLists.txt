cmake_minimum_required(VERSION 3.5)
project(log_demo)

set (TARGET log_demo)
set (ARTIFACT app)
set (ULIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)

set (APP_SRC ${APP_SRC} main.cpp)

message (${APP_SRC})

add_definitions("-I${ULIB_DIR}/inc")

add_subdirectory(wrappers)

include (${ULIB_DIR}/mk/ulib.mk)
