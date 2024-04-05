# GLAD
# ----------------------------
message(STATUS "Pulling GLAD")
FetchContent_Declare(
    libglad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v${GLAD_VERSION}
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)

FetchContent_GetProperties(libglad)
FetchContent_Populate(libglad)
set(GLAD_SOURCES_DIR ${libglad_SOURCE_DIR})
add_subdirectory(${libglad_SOURCE_DIR}/cmake ${CMAKE_CURRENT_BINARY_DIR}/cmake)
glad_add_library(glad_vulkan STATIC REPRODUCIBLE LOADER API vulkan=${VULKAN_VER_MAJOR}.${VULKAN_VER_MINOR})
# gl:core=4.6


# GLFW
# ----------------------------
if (${PkgConfig_FOUND})
	pkg_check_modules(GLFW3 glfw3)

    if(NOT ${GLFW3_FOUND})
        pkg_check_modules(X11 x11)
        pkg_check_modules(WAYLAND wayland-client)
    endif()
endif()

if(${GLFW3_FOUND})
    message(STATUS "Using system GLFW")
else()
	message(STATUS "Pulling GLFW")
	FetchContent_Declare(
		libglfw
		GIT_REPOSITORY https://github.com/glfw/glfw.git
		GIT_TAG ${GLFW_VERSION}
		GIT_PROGRESS TRUE
		GIT_SHALLOW TRUE
	)

	set(GLFW_INSTALL OFF)
	set(GLFW_BUILD_DOCS OFF)
	set(GLFW_BUILD_COCOA OFF)

    if(${X11_FOUND})
        set(GLFW_BUILD_X11 ON)
    elseif(${WAYLAND_FOUND})
	    set(GLFW_BUILD_WAYLAND ON)
    elseif(${LINUX})
        message(WARNING "GLFW should have either Wayland or X11 on Linux")
    endif()

	FetchContent_MakeAvailable(libglfw)
endif()

# Vulkan C Headers
# --------------------------------------
message(STATUS "Pulling Vulkan-Headers")
FetchContent_Declare(
    vulkanheaders
    GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Headers.git
    GIT_TAG v${VULKAN_VERSION}
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
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
)

FetchContent_GetProperties(vulkanhpp)
FetchContent_Populate(vulkanhpp)

# Library setup
add_library(vulkan INTERFACE)
target_include_directories(vulkan INTERFACE ${vulkanhpp_SOURCE_DIR})
target_link_libraries(vulkan INTERFACE Vulkan::Headers glfw glad_vulkan)


# =====================
# Mimic, finally
# ======================


# because MS doesn't respect standards..
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/permissive- /volatile:iso /Zc:preprocessor /EHsc /Zc:__cplusplus /Zc:externConstexpr /Zc:throwingNew /EHsc /W4 /wd4146 /wd4245 /RTCcsu)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(/Z7)
    endif()
endif()

# Adding extra warning flags
# --------------------------
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wall -Wextra -Wdouble-promotion -Wno-unused-parameter -Wno-unused-function -Wconversion -Wno-sign-conversion -fsanitize=undefined -fsanitize-trap)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-g3)
    endif()
endif()


configure_file(build_info.cpp.in build_info.cpp @ONLY)

add_library(mimic STATIC
    mimic.cpp mimic.hpp
    window.cpp window.hpp
    build_info.cpp build_info.hpp
)

target_link_libraries(mimic PUBLIC vulkan)
target_include_directories(mimic PUBLIC ${IMGUI_SOURCES_DIR})

