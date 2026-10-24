cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(DeltaFM)

find_library(MAGIC_LIB magic REQUIRED)
find_path(MAGIC_INCLUDE_DIR magic.h REQUIRED)

if(NOT MAGIC_LIB OR NOT MAGIC_INCLUDE_DIR)
    message(FATAL_ERROR
        "libmagic not found.\n"
        "Install it with:\n"
        "  Ubuntu/Debian:  sudo apt install libmagic-dev\n"
        "  macOS:          brew install libmagic\n"
        "  Windows:        vcpkg install libmagic"
    )
endif()

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
    ${MAGIC_LIB}
)
