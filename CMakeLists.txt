cmake_minimum_required(VERSION 3.16)
project(DeltaFM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# libmagic: also search the Homebrew folders used on macOS
find_library(MAGIC_LIB magic
    HINTS /opt/homebrew/lib /usr/local/lib)
find_path(MAGIC_INCLUDE_DIR magic.h
    HINTS /opt/homebrew/include /usr/local/include)

if(NOT MAGIC_LIB OR NOT MAGIC_INCLUDE_DIR)
    message(FATAL_ERROR
        "libmagic not found.\n"
        "Install it with:\n"
        "  Ubuntu/Debian:  sudo apt install libmagic-dev\n"
        "  Arch:           sudo pacman -S file\n"
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

)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${MAGIC_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ftxui::screen
    ftxui::dom
    ftxui::component
    ${MAGIC_LIB}
)
install(PROGRAMS $<TARGET_FILE:${PROJECT_NAME}>
        DESTINATION bin
        RENAME dfm${CMAKE_EXECUTABLE_SUFFIX})
