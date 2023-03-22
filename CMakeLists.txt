CMAKE_MINIMUM_REQUIRED(VERSION 3.14 FATAL_ERROR)
PROJECT(LTC2943_Sim VERSION 0.0.1 LANGUAGES C)
INCLUDE(CheckCCompilerFlag)

# Define ${CMAKE_INSTALL_...} variables
include(GNUInstallDirs)

option(ENABLE_WARNINGS_SETTINGS "Allow target_set_warnings to add flags and defines.
                                 Set this to OFF if you want to provide your own warning parameters." ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(ConfigSafeGuards)
include(Colors)
include(CTest)
include(Warnings)

# --------------------------------------------------------------------------------
#                         Check for C17 support.
# --------------------------------------------------------------------------------
CHECK_C_COMPILER_FLAG("-std=c17" COMPILER_SUPPORTS_C17)
IF(COMPILER_SUPPORTS_C17)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c17")
ELSE()
    MESSAGE(STATUS "The compiler ${CMAKE_C_COMPILER} has no C17 support. Please use a different C compiler.")
ENDIF()

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-deprecated-register -Wno-ignored-attributes")

set(TESTFILES        # All .cpp files in tests/
    tests/main.c
)
# --------------------------------------------------------------------------------
#                         Add CppUTest Dependency
# --------------------------------------------------------------------------------
add_library(unity STATIC external/Unity/src/unity.c)
target_include_directories(unity PUBLIC external/Unity/src)
ENABLE_TESTING()

ADD_SUBDIRECTORY(test)
ADD_SUBDIRECTORY(src)
