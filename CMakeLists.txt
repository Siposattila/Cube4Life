# This file is automatically generated from cmake.toml - DO NOT EDIT
# See https://github.com/build-cpp/cmkr for more information

cmake_minimum_required(VERSION 3.15)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
	message(FATAL_ERROR "In-tree builds are not supported. Run CMake from a separate directory: cmake -B build")
endif()

set(CMKR_ROOT_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
	set(CMKR_ROOT_PROJECT ON)

	# Bootstrap cmkr and automatically regenerate CMakeLists.txt
	include(cmkr.cmake OPTIONAL RESULT_VARIABLE CMKR_INCLUDE_RESULT)
	if(CMKR_INCLUDE_RESULT)
		cmkr()
	endif()

	# Enable folder support
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)

	# Create a configure-time dependency on cmake.toml to improve IDE support
	configure_file(cmake.toml cmake.toml COPYONLY)
endif()

project(Cube4Life)

include(after.cmake)

include(FetchContent)

# Fix warnings about DOWNLOAD_EXTRACT_TIMESTAMP
if(POLICY CMP0135)
	cmake_policy(SET CMP0135 NEW)
endif()
message(STATUS "Fetching gtest (v1.14.0)...")
FetchContent_Declare(gtest
	GIT_REPOSITORY
		"https://github.com/google/googletest"
	GIT_TAG
		v1.14.0
)
FetchContent_MakeAvailable(gtest)

# Target: Cube4Life
set(Cube4Life_SOURCES
	"src/Cube4Life/cube4life.cpp"
	"src/Cube4Life/main.cpp"
	cmake.toml
)

add_executable(Cube4Life)

target_sources(Cube4Life PRIVATE ${Cube4Life_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${Cube4Life_SOURCES})

target_compile_features(Cube4Life PRIVATE
	cxx_std_17
)

target_link_libraries(Cube4Life PRIVATE
	gtest
	Vulkan::Vulkan
	glfw
)

get_directory_property(CMKR_VS_STARTUP_PROJECT DIRECTORY ${PROJECT_SOURCE_DIR} DEFINITION VS_STARTUP_PROJECT)
if(NOT CMKR_VS_STARTUP_PROJECT)
	set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Cube4Life)
endif()
