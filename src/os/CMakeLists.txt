cmake_minimum_required(VERSION 3.5)

if (BPP_OS MATCHES FreeRTOS)
    add_subdirectory(freertos)
elseif(BPP_OS MATCHES qt OR BPP_OS MATCHES Qt)
    add_subdirectory(qt)
else()
    add_subdirectory(posix)
endif()

set (ULIB_SRC ${ULIB_SRC}
     PARENT_SCOPE
    )

