cmake_minimum_required(VERSION 3.5)

set (ULIB_INC ${ULIB_INC}
     ${CMAKE_CURRENT_SOURCE_DIR}/asrt_halt_stdio.h 
     ${CMAKE_CURRENT_SOURCE_DIR}/asrt_pc_stdio.h
     PARENT_SCOPE
    )
