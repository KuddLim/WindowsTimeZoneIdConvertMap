cmake_minimum_required(VERSION 3.0)
project(DialogExample C CXX)

set(project_name WindowsTimezoneIdConvertMap)
set(output_name WindowsTimezoneIdConvertMap)

# "cmake.parallelJobs": 4

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-function -fpermissive -fPIC")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")

set(CMAKE_EXE_LINKER_FLAGS )

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    add_definitions(-D_DEBUG)
    add_definitions(-DDEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
    set(output_name "${output_name}d")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -o3")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -o3")
endif()

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

set(SOURCE_FILES
    main.cpp
)

add_executable(${output_name} ${SOURCE_FILES})

target_link_libraries(${output_name} boost_system)
