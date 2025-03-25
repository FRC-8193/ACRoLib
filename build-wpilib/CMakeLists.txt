cmake_minimum_required(VERSION 3.15)
project(WPILibBuild)

option(CUSTOM_WPILIB_PATH "Path(s) to search for AllWPILib" "")

find_path(WPILIB_TOOLCHAIN_PATH
	NAMES "toolchain-config.cmake"
	PATHS
		"/usr/local/"
		"~/wpilib/${FRC_SEASON}/roborio/"
	NO_DEFAULT_PATH
)

find_path(WPILIB_PATH
	NAMES "wpilib-config.cmake.in"
	PATHS
		"/wpilib/"
		${CUSTOM_WPILIB_PATH}
	NO_DEFAULT_PATH
)

if (NOT WPILIB_TOOLCHAIN_PATH)
	message(FATAL_ERROR "Failed to find WPILib RoboRIO toolchain file, ensure WPILib is installed or build with Docker.")
else()
	message(STATUS "Found WPILib RoboRIO toolchain file in ${WPILIB_TOOLCHAIN_PATH}")
endif()

if (NOT WPILIB_PATH)
	message(FATAL_ERROR "Failed to find AllWPILib, if you have it cloned locally please set CUSTOM_WPILIB_PATH or build with Docker.")
else()
	message(STATUS "Found AllWPILib in ${WPILIB_PATH}")
endif()

list(APPEND CMAKE_MODULE_PATH "${WPILIB_PATH}/cmake/modules/")

add_subdirectory("${WPILIB_PATH}/wpimath" "${CMAKE_BINARY_DIR}/wpimath")
add_subdirectory("${WPILIB_PATH}/wpinet" "${CMAKE_BINARY_DIR}/wpinet")
add_subdirectory("${WPILIB_PATH}/wpiunits" "${CMAKE_BINARY_DIR}/wpiunits")
add_subdirectory("${WPILIB_PATH}/wpiutil" "${CMAKE_BINARY_DIR}/wpiutil")
add_subdirectory("${WPILIB_PATH}/hal" "${CMAKE_BINARY_DIR}/wpihal")
add_subdirectory("${WPILIB_PATH}/ntcore" "${CMAKE_BINARY_DIR}/ntcore")

add_subdirectory("${WPILIB_PATH}/wpilibc" "${CMAKE_BINARY_DIR}/wpilibc")

set(CMAKE_TOOLCHAIN_FILE "${WPILIB_TOOLCHAIN_PATH}/toolchain-config.cmake")
