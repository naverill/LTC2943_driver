add_library(chip_control STATIC
    chip_control.c
)

target_include_directories(chip_control PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
