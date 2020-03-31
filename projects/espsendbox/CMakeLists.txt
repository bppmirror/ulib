cmake_minimum_required(VERSION 3.5)
project(esp_sandbox)

set (ULIB_REL_DIR ${CMAKE_CURRENT_LIST_DIR}/../../)

get_filename_component (ULIB_DIR ${ULIB_REL_DIR} ABSOLUTE)

message ("uLib dir: ${ULIB_DIR}")

set (BPP_OS FreeRTOS)
add_subdirectory(${ULIB_DIR}/src ${CMAKE_BINARY_DIR}/bpp_lib)

#set(ULIB_SRCS      ${ULIB_DIR}/src/assert/assert.cpp
#                   ${ULIB_DIR}/src/mem/heapman_default.cpp
#                   ${ULIB_DIR}/src/mem/heapman_impl.cpp
#                   ${ULIB_DIR}/src/mem/new.cpp
#                   ${ULIB_DIR}/src/ulib.cpp
#                   ${ULIB_DIR}/src/os/freertos/frmutex.cpp)

message ( STATUS "MY: ${ULIB_SRC}")

set (SRCS ${ULIB_SRC} main.cpp )                  
                   
message ( STATUS " ALL: ${SRCS}" )

# The source file main.c contains app_main() definition
add_executable(${CMAKE_PROJECT_NAME}.elf ${SRCS})

# Provides idf_import_components() and idf_link_components()
include($ENV{IDF_PATH}/tools/cmake/idf_functions.cmake)

# Create artifacts used for flashing the project to target chip
set(IDF_BUILD_ARTIFACTS ON)
set(IDF_PROJECT_EXECUTABLE ${CMAKE_PROJECT_NAME}.elf)
set(IDF_BUILD_ARTIFACTS_DIR ${CMAKE_BINARY_DIR})

# Trim down components included in the build. Although freertos and spi_flash are the ones needed by the application
# itself, the bootloader and esptool_py components are also needed in order to create the artifacts to be used
# for flashing to the target chip
set(IDF_COMPONENTS freertos spi_flash bootloader esptool_py)

#set (BPP_OS FreeRTOS)
#add_subdirectory(${ULIB_DIR} ${CMAKE_BINARY_DIR}/bpp_lib)
#target_include_directories(bpp_ulib PRIVATE ${IDF_INCLUDE_DIRECTORIES})
#target_compile_options(bpp_ulib PRIVATE "${IDF_COMPILE_OPTIONS}")
#target_compile_options(bpp_ulib PRIVATE "${IDF_CXX_COMPILE_OPTIONS}")

# Wraps add_subdirectory() to create library targets for components, and then return them using the specified variable
idf_import_components(components $ENV{IDF_PATH} esp-idf)


# Wraps target_link_libraries() to link processed components by idf_import_components to target
idf_link_components(${CMAKE_PROJECT_NAME}.elf "${components} bpp_ulib")
