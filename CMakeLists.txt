cmake_minimum_required(VERSION 4.0 FATAL_ERROR)
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
# GLAD (local)
# -------------------
add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# -------------------
# imnodes (just sources, no find_package)
# -------------------
add_library(imnodes STATIC ${imnodes_SOURCE_DIR}/imnodes.cpp)
target_include_directories(imnodes PUBLIC ${imnodes_SOURCE_DIR} ${imgui_SOURCE_DIR})

# -------------------
# Create executable
# -------------------
add_executable(${PROJECT_NAME} src/main.cpp
        src/Window.cpp
        include/Window.h
        include/Window.h
        src/NodeGraph.cpp
        include/Utils.h
        include/Utils.h
        include/UiManager.h
        src/UiManager.cpp
        include/Pin.h
        src/Pin.cpp
        include/Node.h
        src/Node.cpp
        include/NodeGraph.h
        include/Command.h
        include/EditorContext.h
)

# -------------------
# ImGui sources
# -------------------
target_sources(${PROJECT_NAME} PRIVATE
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

# -------------------
# Include directories
# -------------------
target_include_directories(${PROJECT_NAME} PRIVATE
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
        ${imnodes_SOURCE_DIR}
)

# -------------------
# Link libraries
# -------------------
target_link_libraries(${PROJECT_NAME} PRIVATE
        glfw
        glad
        imnodes
        ${CMAKE_DL_LIBS}
)
