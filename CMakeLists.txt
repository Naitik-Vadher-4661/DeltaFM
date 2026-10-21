cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
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
   src/Filesystemitem.cpp
   src/Fileitem.cpp
   src/Directoryitem.cpp
   src/Filemanager.cpp
   src/Logger.cpp
   src/FilemanagerUI.cpp
   src/previewer.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ftxui::screen
    ftxui::dom
    ftxui::component
)
