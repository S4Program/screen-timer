cmake_minimum_required(VERSION 3.28)
project(ScreenTimerProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(ScreenTimer 

gui/UIElement/uiElement.cpp
gui/TextBox/textBox.cpp
gui/MouseHandle/mouseHandle.cpp
gui/LabelElement/labelElement.cpp

src/RenderHandler/renderHandler.cpp
src/main.cpp

extlibs/tinyfiledialogs/tinyfiledialogs.cpp)
target_compile_features(ScreenTimer PRIVATE cxx_std_17)
target_link_libraries(ScreenTimer PRIVATE SFML::Graphics)