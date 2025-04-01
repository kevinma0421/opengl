cmake_minimum_required(VERSION 3.10)
project(satelliteSimulation)

set(CMAKE_CXX_STANDARD 17)

# Print Debug Info
message(STATUS "Configuring satelliteSimulation...")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")

# Add include and library paths
set(GLFW_INCLUDE_DIR "C:/Users/123ke/OneDrive/Documents/Projects/lib/glfw/glfw/include")
set(GLFW_LIB_DIR "C:/Users/123ke/OneDrive/Documents/Projects/lib/glfw/glfw/lib-mingw-w64")
set(GLAD_INCLUDE_DIR "C:/Users/123ke/OneDrive/Documents/Projects/lib/glad/include")
set(GLAD_SRC "C:/Users/123ke/OneDrive/Documents/Projects/lib/glad/src/glad.c")
set(GLM "C:/Users/123ke/OneDrive/Documents/Projects/lib/glm/install/include/glm")
set(IMGUI "C:/Users/123ke/OneDrive/Documents/Projects/lib/imgui")

# Print Paths
message(STATUS "GLFW Include Directory: ${GLFW_INCLUDE_DIR}")
message(STATUS "GLFW Library Directory: ${GLFW_LIB_DIR}")
message(STATUS "GLAD Include Directory: ${GLAD_INCLUDE_DIR}")
message(STATUS "GLAD Source File: ${GLAD_SRC}")
message(STATUS "GLM Include Directory: ${GLM}")
message(STATUS "IMGUI Library Directory: ${IMGUI}")

# Include directories
include_directories(${GLFW_INCLUDE_DIR} ${GLAD_INCLUDE_DIR} ${CMAKE_SOURCE_DIR} ${GLM})

# Link directories
link_directories(${GLFW_LIB_DIR})

# Check file existence
if (EXISTS ${GLAD_SRC})
    message(STATUS "GLAD source file found!")
else()
    message(FATAL_ERROR "Error: GLAD source file not found at ${GLAD_SRC}")
endif()

if (EXISTS ${GLM})
    message(STATUS "GLM file found!")
else()
    message(FATAL_ERROR "Error: GLM file not found at ${GLM}")
endif()

# Add GLAD as a static library
add_library(glad ${GLAD_SRC})

# Recursively collect all source and header files in core
file(GLOB_RECURSE CORE_SRC "core/src/*.cpp")
file(GLOB_RECURSE CORE_HEADERS "core/inc/*.h")

# Add ImGui source files
file(GLOB IMGUI_SRC
    ${IMGUI}/imgui*.cpp
    ${IMGUI}/backends/imgui_impl_glfw.cpp
    ${IMGUI}/backends/imgui_impl_opengl3.cpp
)

# Add executable target
add_executable(sat_sim ${CORE_SRC})

# Add IMGUI as static library
add_library(imgui ${IMGUI_SRC})
target_include_directories(imgui PUBLIC
    ${IMGUI}
    ${IMGUI}/backends
)

# Link libraries
target_include_directories(sat_sim PRIVATE core/inc)
target_link_libraries(sat_sim glad glfw3 opengl32 imgui)

# Add shaders as a folder
file(GLOB SHADERS "shaders/*")
source_group("Shaders" FILES ${SHADERS})

# Print Final Configuration
message(STATUS "Configuration Complete!")


#cmake -S . -B build
#cmake --build build
