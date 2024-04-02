cmake_minimum_required(VERSION 3.5..)
include(FetchContent)

project(mimic VERSION 0.1.0)

if (POLICY CMP0115)
	cmake_policy(SET CMP0115 NEW)
endif()
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

add_subdirectory(src)

add_executable(mimic_test ${CMAKE_SOURCE_DIR}/test/test.cpp)

target_include_directories(mimic_test PRIVATE ${IMGUI_SOURCES_DIR} src)
target_link_libraries(mimic_test PRIVATE mimic)
