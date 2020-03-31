cmake_minimum_required(VERSION 3.5)

get_directory_property(hasParent PARENT_DIRECTORY)
if(hasParent)
  message(STATUS "Has a parent scope.")
  add_subdirectory(src)
  add_subdirectory(inc)
  set (ULIB_SRC ${ULIB_SRC}
     PARENT_SCOPE
    )
  set (ULIB_INC ${ULIB_INC}
     PARENT_SCOPE
    )
else()

    option(WITH_ULIB_TESTS "Build test programs" OFF)
    project(ulib_tests)
    set (ULIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/)

    if (WITH_ULIB_TESTS)

        set (TARGET ulib_tests)
        set (ARTIFACT app)

    add_definitions("-I${ULIB_DIR}/inc")
    add_subdirectory(tests)
    message (STATUS "Building tests")

    else()
        project(BPP_uLib)
        set (TARGET bpp_ulib)
        set (ARTIFACT staticlib)
    endif()

    include (./mk/ulib.mk)
endif()


#target_compile_definitions(bpp_ulib PRIVATE ${TARGET_LIBS})

#target_link_libraries(bpp_ulib PRIVATE ${TARGET_LIBS})

#set (ULIB_SRC ${ULIB_SRC} PARENT_SCOPE)
