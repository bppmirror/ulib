
if (NOT DEFINED BPP_PLATFORM)
    set(BPP_PLATFORM qt)
endif()

if (BPP_PLATFORM MATCHES esp32)
    include (${ULIB_DIR}./mk/platforms/esp_settings.mk NO_POLICY_SCOPE)
else()
if (BPP_PLATFORM MATCHES qt)
    include (${ULIB_DIR}./mk/platforms/qt_settings.mk)
endif()


endif()
   
if (NOT DEFINED BPP_OS)
    set(BPP_OS Qt)
endif()

message (STATUS "OS: ${BPP_OS}")
message (STATUS "Platform: ${BPP_PLATFORM}")
message (STATUS "Artifact: ${ARTIFACT}")
message (STATUS "Target name: ${TARGET}")

if (BPP_OS MATCHES FreeRTOS)
    include (${ULIB_DIR}./mk/os/freertos.mk NO_POLICY_SCOPE)
else()
    include (${ULIB_DIR}./mk/os/qt.mk NO_POLICY_SCOPE)
endif()


add_subdirectory(${ULIB_DIR}/src ulib_bin)
add_subdirectory(${ULIB_DIR}/inc ulib_inc)


if (ARTIFACT MATCHES staticlib)
    include (${ULIB_DIR}./mk/artifacts/staticlib.mk)
else()
    if (BPP_PLATFORM MATCHES qt)
	include (${ULIB_DIR}./mk/artifacts/qtapp.mk)
    endif()
    if (BPP_PLATFORM MATCHES esp32)
	include (${ULIB_DIR}./mk/artifacts/espapp.mk)
    endif()
endif()


if (WITH_ULIB_TESTS)
    add_definitions(-D BPP_UNIT_TESTS)    
endif()

#message ( ${BPP_PLATFORM} ${ARTIFACT} ${APP_SRC})

if (BPP_PLATFORM MATCHES qt)
    include (${ULIB_DIR}./mk/platforms/qt.mk)
endif()

if (BPP_PLATFORM MATCHES esp32)
    include (${ULIB_DIR}./mk/platforms/esp.mk)
endif()
