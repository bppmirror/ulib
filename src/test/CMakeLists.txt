cmake_minimum_required(VERSION 3.5)
if (WITH_ULIB_TESTS)
set (ULIB_SRC ${ULIB_SRC}
     ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp 
     PARENT_SCOPE
    )
endif()
