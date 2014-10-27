CMAKE_MINIMUM_REQUIRED (VERSION 2.4.7 FATAL_ERROR)
project (cpugauge)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

add_definitions (-Wl,-z,defs)

SET (CMAKE_C_FLAGS "-Wall -Winvalid-pch -ffunction-sections -fdata-sections")
SET (CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS})
SET (CMAKE_C_FLAGS_RELEASE "-Wall -Winvalid-pch -ffunction-sections -fdata-sections -ffast-math -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE})
 
SET (CMAKE_VERBOSE_MAKEFILE 0)

#find_package (Boost REQUIRED)
#include_directories(${Boost_INCLUDE_DIRS})
#link_directories(${Boost_LIBRARY_DIRS})
#message (${Boost_INCLUDE_DIRS})

#find_package(GLUT REQUIRED)
#include_directories(${GLUT_INCLUDE_DIRS})
#link_directories(${GLUT_LIBRARY_DIRS})

include (FindPkgConfig)
pkg_check_modules (GLIB REQUIRED "glib-2.0")
INCLUDE_DIRECTORIES (${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
include (FindLibGtop)
include_directories (${GLIBTOP_INCLUDE_DIR})

AUX_SOURCE_DIRECTORY (../src SOURCES)
INCLUDE_DIRECTORIES (../src)

add_executable (${PROJECT_NAME} ${SOURCES})
TARGET_LINK_LIBRARIES (${PROJECT_NAME} ${GLIBTOP_LIBRARY_OPTIMIZED})
TARGET_LINK_LIBRARIES (${PROJECT_NAME} ${GLIB_LIBRARIES})
#TARGET_LINK_LIBRARIES (${PROJECT_NAME} ${GLUT_LIBRARIES})
#TARGET_LINK_LIBRARIES (${PROJECT_NAME} boost_timer)
#TARGET_LINK_LIBRARIES (${PROJECT_NAME} boost_system) # Timer requires that
