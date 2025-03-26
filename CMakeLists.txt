cmake_minimum_required(VERSION 3.15)
project(ACRoLib)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/FRCMake/cmake/modules)
include(FRCMake)

frcmake_set_toolchain_roborio()
frcmake_get_wpilib()

include(${CMAKE_CURRENT_SOURCE_DIR}/build_acrolib.cmake OPTIONAL)
