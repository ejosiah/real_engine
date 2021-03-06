cmake_minimum_required(VERSION 3.17)
project(real_engine VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 17)

option(AUTO_LOCATE_VULKAN "AUTO_LOCATE_VULKAN" ON)

if(AUTO_LOCATE_VULKAN)
    message(STATUS "Attempting auto locate Vulkan using CMake......")

    # Find Vulkan Path using CMake's Vulkan Module
    # This will return Boolean 'Vulkan_FOUND' indicating the status of find as success(ON) or fail(OFF).
    # Include directory path - 'Vulkan_INCLUDE_DIRS' and 'Vulkan_LIBRARY' with required libraries.
    find_package(Vulkan)

    # Try extracting VulkanSDK path from ${Vulkan_INCLUDE_DIRS}
    if (NOT ${Vulkan_INCLUDE_DIRS} STREQUAL "")
        set(VULKAN_PATH ${Vulkan_INCLUDE_DIRS})
        STRING(REGEX REPLACE "/Include" "" VULKAN_PATH ${VULKAN_PATH})
    endif()

    if(NOT Vulkan_FOUND)
        # CMake may fail to locate the libraries but could be able to
        # provide some path in Vulkan SDK include directory variable
        # 'Vulkan_INCLUDE_DIRS', try to extract path from this.
        message(STATUS "Failed to locate Vulkan SDK, retrying again...")
        if(EXISTS "${VULKAN_PATH}")
            message(STATUS "Successfully located the Vulkan SDK: ${VULKAN_PATH}")
        else()
            message("Error: Unable to locate Vulkan SDK. Please turn off auto locate option by specifying 'AUTO_LOCATE_VULKAN' as 'OFF'")
            message("and specify manually path using 'VULKAN_SDK' and 'VULKAN_VERSION' variables in the CMakeLists.txt.")
            return()
        endif()
    endif()
else()
    message(STATUS "Attempting to locate Vulkan SDK using manual path......")
    if(DEFINED ENV{VK_SDK_PATH})
        set(VULKAN_PATH $ENV{VK_SDK_PATH})
    elseif(DEFINED ENV{VK_SDK_PATH})
        set(VULKAN_PATH $ENV{VULKAN_SDK})
    endif()

    message(STATUS "Using manual specified path: ${VULKAN_PATH}")

    # Check if manual set path exists
    if(NOT EXISTS "${VULKAN_PATH}")
        message("Error: Unable to locate this Vulkan SDK path VULKAN_PATH: ${VULKAN_PATH}, please specify correct path.
		For more information on correct installation process, please refer to subsection 'Getting started with Lunar-G SDK'
		and 'Setting up first project with CMake' in Chapter 3, 'Shaking hands with the device' in this book 'Learning Vulkan', ISBN - 9781786469809.")
        return()
    endif()
endif()

add_definitions(
        -DVK_USE_PLATFORM_WIN32_KHR
        -DGLFW_INCLUDE_VULKAN
)

# Define include path
include_directories(include)
include_directories(glfw)
include_directories(glfw/include)
include_directories(vulkan/include)
include_directories(external)


# Gather list of header and source files for compilation
file(GLOB_RECURSE CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
file(GLOB_RECURSE HPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.*)

file(GLOB_RECURSE GLFW_CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/glfw/source/*.cpp)
file(GLOB_RECURSE GLFW_HPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include/*.*)

file(GLOB_RECURSE VULKAN_CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/vulkan/source/*.cpp)
file(GLOB_RECURSE VULKAN_HPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/vulkan/include/*.*)

# vulkan-1 library for build Vulkan application.
set(VULKAN_LIB_LIST "vulkan-1")

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    # Include Vulkan header files from Vulkan SDK
    include_directories(AFTER ${VULKAN_PATH}/Include)

    # Link directory for vulkan-1
    link_directories(${VULKAN_PATH}/Bin)
    link_directories(${VULKAN_PATH}/Lib)
endif()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


set(ALL_LIBS ${CONAN_LIBS} ${VULKAN_LIB_LIST})

add_library(vma "external/vk_mem_alloc.h" "external/vk_mem_alloc.cpp")
add_library(real_engine ${HPP_FILES} ${GLFW_HPP_FILES} ${VULKAN_HPP_FILES} ${CPP_FILES} ${GLFW_CPP_FILES} ${VULKAN_CPP_FILES})
target_link_libraries(real_engine ${ALL_LIBS} vma)

add_executable(real_engine_test EXCLUDE_FROM_ALL source/main.cpp)
target_link_libraries(real_engine_test real_engine)