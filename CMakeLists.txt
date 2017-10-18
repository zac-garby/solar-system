cmake_minimum_required(VERSION 3.0)
project(solar_system)

set(CMAKE_CXX_STANDARD 11)

set(GLOB SOURCE_FILES "*.h" "*.cpp")

add_executable(solar_system ${SOURCE_FILES})

set(CMAKE_EXE_LINKER_FLAGS "-lsfml-graphics -lsfml-window -lsfml-system")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED COMPONENTS system window graphics)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(solar_system ${SFML_LIBRARIES})
endif()