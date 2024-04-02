cmake_minimum_required(VERSION 3.5..)
include(FetchContent)

# Setting up options for later
# ------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(VULKAN_VER_MAJOR 1)
set(VULKAN_VER_MINOR 3)
set(VULKAN_VER_PATCH 278)

set(VULKAN_VERSION ${VULKAN_VER_MAJOR}.${VULKAN_VER_MINOR}.${VULKAN_VER_PATCH})

set(GLAD_VERSION 2.0.6)

set(GLFW3_VERSION 3.4)

set(IMGUI_VERSION 1.90.4)

set(GLM_VERSION 1.0.1)

set(CATCH2_VERSION 3.5.3)
# https://github.com/catchorg/Catch2/blob/devel/CMakeLists.txt

# IMPORTANT:
# Later, update git tag names to use hashes


set(BUILD_SHARED_LIBS OFF)


# GLAD 
# ----------------------------
message(STATUS "Pulling GLAD")
FetchContent_Declare(
	libglad
	GIT_REPOSITORY https://github.com/Dav1dde/glad.git
	GIT_TAG v${GLAD_VERSION}
	GIT_SHALLOW TRUE
	GIT_PROGRESS TRUE
	GIT_SHALLOW 1
)

FetchContent_GetProperties(libglad)
FetchContent_Populate(libglad)
set(GLAD_SOURCES_DIR ${libglad_SOURCE_DIR})
add_subdirectory(${libglad_SOURCE_DIR}/cmake ${CMAKE_CURRENT_BINARY_DIR}/cmake)
glad_add_library(glad_vulkan STATIC REPRODUCIBLE LOADER API vulkan=${VULKAN_VER_MAJOR}.${VULKAN_VER_MINOR})
# gl:core=4.6


# GLFW
# ----------------------------
message(STATUS "Pulling GLFW")
FetchContent_Declare(
	libglfw
	GIT_REPOSITORY https://github.com/glfw/glfw.git
	GIT_TAG ${GLFW_VERSION}
	GIT_PROGRESS TRUE
	GIT_SHALLOW 1
)

set(GLFW_INSTALL OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_COCOA OFF)
set(GLFW_BUILD_WAYLAND OFF)
FetchContent_MakeAvailable(libglfw)


# Vulkan C Headers
# --------------------------------------
message(STATUS "Pulling Vulkan-Headers")
FetchContent_Declare(
	vulkanheaders
	GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Headers.git
	GIT_TAG v${VULKAN_VERSION}
	GIT_SHALLOW TRUE
	GIT_PROGRESS TRUE
	GIT_SHALLOW 1
)

set(PROJECT_IS_TOP_LEVEL OFF)
FetchContent_MakeAvailable(vulkanheaders)


# Vulkan C++ Wrapper
# ----------------------------------
message(STATUS "Pulling Vulkan-Hpp")
FetchContent_Declare(
	vulkanhpp
	GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Hpp.git
	GIT_TAG v${VULKAN_VERSION}
	GIT_SHALLOW TRUE
	GIT_PROGRESS TRUE
	GIT_SHALLOW 1
)

FetchContent_GetProperties(vulkanhpp)
FetchContent_Populate(vulkanhpp)

# Library setup
add_library(vulkan INTERFACE)
target_include_directories(vulkan INTERFACE ${vulkanhpp_SOURCE_DIR})
target_link_libraries(vulkan INTERFACE Vulkan::Headers glfw glad_vulkan)


# IMGUI
# -----------------------------
message(STATUS "Pulling ImGui")
FetchContent_Declare(
	imgui
	GIT_REPOSITORY https://github.com/ocornut/imgui.git
	GIT_TAG v${IMGUI_VERSION}
	GIT_PROGRESS TRUE
	GIT_SHALLOW 1
)

FetchContent_GetProperties(imgui)
FetchContent_Populate(imgui)
set(IMGUI_SOURCES_DIR ${imgui_SOURCES_DIR})


# GLM
# ---------------------------
message(STATUS "Pulling glm")
FetchContent_Declare(
	libglm
	GIT_REPOSITORY https://github.com/g-truc/glm.git
	GIT_TAG ${GLM_VERSION}
	GIT_PROGRESS TRUE
	GIT_SHALLOW 1
)

set(GLM_ENABLE_CXX_20 ON)
FetchContent_MakeAvailable(libglm)


# =====================
# Mimic, finally
# ======================
project(mimic VERSION 0.1.0 LANGUAGES C CXX)

# because MS doesn't respect standards..
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	add_compile_options(/permissive- /volatile:iso /Zc:preprocessor /EHsc /Zc:__cplusplus /Zc:externConstexpr /Zc:throwingNew /EHsc)
endif()

set(MIMIC_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(mimic STATIC)

# eventually, this will be the actual game executable
# in a separate repository
add_executable(mimic_test)

target_include_directories(mimic PUBLIC ${IMGUI_SOURCES_DIR})
target_link_libraries(mimic PUBLIC vulkan)

target_include_directories(mimic_test PRIVATE ${IMGUI_SOURCES_DIR})
target_link_libraries(mimic_test PRIVATE mimic)

target_sources(mimic PRIVATE ${MIMIC_SRC_DIR}/mimic.cpp ${MIMIC_SRC_DIR}/mimic.hpp PRIVATE ${MIMIC_SRC_DIR}/vars.cpp ${MIMIC_SRC_DIR}/vars.hpp)
target_sources(mimic_test PRIVATE ${MIMIC_SRC_DIR}/test.cpp)