cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD		23)
set(CMAKE_CXX_STANDARD_REQUIRED	True)

set(PROJECT_NAME		"Shooter-Trainer")
set(EXE_NAME			"${PROJECT_NAME}.exe")

# All CPP files
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")

project(${PROJECT_NAME} VERSION 0.0.1)

# Add exe
add_executable("${PROJECT_NAME}" "${sources}")

# Set EXE Output path
set(EXECUTABLE_OUTPUT_PATH	"${CMAKE_SOURCE_DIR}/bin")

# Set EXE name
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${EXE_NAME})

# From SDL Install Instructions
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(SDL_image REQUIRED)

# Add headers
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/src")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")

# Link to SDL3 library
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
