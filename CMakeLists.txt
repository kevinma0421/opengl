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
# Print Paths to Ensure They Exist
message(STATUS "GLFW Include Directory: ${GLFW_INCLUDE_DIR}")
message(STATUS "GLFW Library Directory: ${GLFW_LIB_DIR}")
message(STATUS "GLAD Include Directory: ${GLAD_INCLUDE_DIR}")
message(STATUS "GLAD Source File: ${GLAD_SRC}")
message(STATUS "GLM Include Directory: ${GLM}")

# Include directories
include_directories(${GLFW_INCLUDE_DIR} ${GLAD_INCLUDE_DIR} ${CMAKE_SOURCE_DIR} ${GLM})

# Link directories
link_directories(${GLFW_LIB_DIR})

# Check if glad.c Exists
if (EXISTS ${GLAD_SRC})
    message(STATUS "GLAD source file found!")
else()
    message(FATAL_ERROR "Error: GLAD source file not found at ${GLAD_SRC}")
endif()

# Check if glm exists
if (EXISTS ${GLM})
    message(STATUS "GLM file found!")
else()
    message(FATAL_ERROR "Error: GLM file not found at ${GLAD_SRC}")
endif()

# Add GLAD as a static library
add_library(glad ${GLAD_SRC})

# Create the executable, adding Sphere.cpp
add_executable(sat_sim sat_sim.cpp Sphere.cpp)

# Link the libraries
target_link_libraries(sat_sim glad glfw3 opengl32)

# Print Final Configuration
message(STATUS "Configuration Complete!")

#cmake -S . -B build
#cmake --build build
