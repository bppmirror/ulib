cmake_minimum_required(VERSION 3.5)

add_subdirectory(assert)
add_subdirectory(log)
add_subdirectory(mem)
add_subdirectory(os)
add_subdirectory(stdfn)
add_subdirectory(string)
add_subdirectory(trace)
if (WITH_ULIB_TESTS)
add_subdirectory(test)
endif()
#add_subdirectory(string)

set (ULIB_SRC ${ULIB_SRC}
     ${CMAKE_CURRENT_SOURCE_DIR}/ulib.cpp 
     PARENT_SCOPE
    )
