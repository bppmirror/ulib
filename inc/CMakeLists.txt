cmake_minimum_required(VERSION 3.5)

add_subdirectory(assert)
add_subdirectory(test)
add_subdirectory(stdfn)

set (ULIB_INC ${ULIB_INC}
     ${CMAKE_CURRENT_SOURCE_DIR}/asrt.h
     ${CMAKE_CURRENT_SOURCE_DIR}/autoptr.h
     ${CMAKE_CURRENT_SOURCE_DIR}/heapman.h
     ${CMAKE_CURRENT_SOURCE_DIR}/list.h
     ${CMAKE_CURRENT_SOURCE_DIR}/locker.h
     ${CMAKE_CURRENT_SOURCE_DIR}/log.h
     ${CMAKE_CURRENT_SOURCE_DIR}/mutex.h
     ${CMAKE_CURRENT_SOURCE_DIR}/new.h
     ${CMAKE_CURRENT_SOURCE_DIR}/observer.h
     ${CMAKE_CURRENT_SOURCE_DIR}/str.h
     ${CMAKE_CURRENT_SOURCE_DIR}/strstream.h
     ${CMAKE_CURRENT_SOURCE_DIR}/trace.h
     ${CMAKE_CURRENT_SOURCE_DIR}/streamops.h
     ${CMAKE_CURRENT_SOURCE_DIR}/ulib.h
     PARENT_SCOPE
    )
