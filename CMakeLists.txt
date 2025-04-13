cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD		23)
set(CMAKE_CXX_STANDARD_REQUIRED	True)

set(PROJECT_NAME		"Shooter-Trainer")
set(EXE_NAME			"${PROJECT_NAME}.exe")

# All CPP files
file(GLOB sources CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp" )

project(${PROJECT_NAME} VERSION 0.0.1)

# Add exe
add_executable("${PROJECT_NAME}" "${sources}")

# Set EXE Output path
set(EXECUTABLE_OUTPUT_PATH	"${CMAKE_SOURCE_DIR}/bin")

# Set EXE name
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${EXE_NAME})




# SDL Stuff
# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

# This assumes the SDL_image source is available in vendored/SDL_image
add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)

# Add headers
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/src")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")

# Link to SDL3 libraries
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)
