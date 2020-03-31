cmake_minimum_required(VERSION 3.5)

set (ULIB_SRC ${ULIB_SRC}
     ${CMAKE_CURRENT_SOURCE_DIR}/heapman_default.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/heapman_impl.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/new.cpp      
     PARENT_SCOPE
    )

set (ULIB_INC ${ULIB_INC}
     ${CMAKE_CURRENT_SOURCE_DIR}/heapman_default.h  
     ${CMAKE_CURRENT_SOURCE_DIR}/heapman_impl.h
     PARENT_SCOPE
    )
