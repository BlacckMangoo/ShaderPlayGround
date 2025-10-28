cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(ShaderPlayground LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# -------------------
# GLFW
# -------------------
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        3.4
)
FetchContent_MakeAvailable(glfw)

# -------------------
# ImGui
# -------------------
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG        docking
)
FetchContent_MakeAvailable(imgui)

# -------------------
# imnodes (fetch source only, no CMakeLists.txt)
# -------------------
FetchContent_Declare(
        imnodes
        GIT_REPOSITORY https://github.com/Nelarius/imnodes.git
        GIT_TAG        master
)
FetchContent_GetProperties(imnodes)
if(NOT imnodes_POPULATED)
    FetchContent_Populate(imnodes)
endif()

# -------------------
# GLAD (local)
# -------------------
add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# -------------------
# ImGui library
# -------------------
add_library(imgui_lib STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui_lib PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(imgui_lib PUBLIC glfw glad)

# -------------------
# imnodes library
# -------------------
add_library(imnodes STATIC
        ${imnodes_SOURCE_DIR}/imnodes.cpp
)
target_include_directories(imnodes PUBLIC
        ${imnodes_SOURCE_DIR}
)
target_link_libraries(imnodes PUBLIC imgui_lib)

# -------------------
# Create executable
# -------------------
add_executable(${PROJECT_NAME}
        src/main.cpp
        src/Window.cpp
        src/NodeGraph.cpp
        src/UiManager.cpp
        src/Pin.cpp
        src/Node.cpp
        src/EditorContext.cpp
        src/OutputImage.cpp
        include/Window.h
        include/Utils.h
        include/UiManager.h
        include/Pin.h
        include/Node.h
        include/NodeGraph.h
        include/Command.h
        include/EditorContext.h
        include/OutputImage.h
)

# -------------------
# Include directories
# -------------------
target_include_directories(${PROJECT_NAME} PRIVATE
        include
)

# -------------------
# Link libraries
# -------------------
target_link_libraries(${PROJECT_NAME} PRIVATE
        imgui_lib
        imnodes
        ${CMAKE_DL_LIBS}
)