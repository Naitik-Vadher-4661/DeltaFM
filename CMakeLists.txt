cmake_minimum_required(VERSION 3.16)

project(DeltaFM)


include(FetchContent)

FetchContent_Declare(
    ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
    GIT_TAG main
)

FetchContent_MakeAvailable(ftxui)

add_executable(${PROJECT_NAME}
   src/main.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ftxui::screen
    ftxui::dom
    ftxui::component
)
