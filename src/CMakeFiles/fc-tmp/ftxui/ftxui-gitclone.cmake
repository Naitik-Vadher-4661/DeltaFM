# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

if(EXISTS "/home/naitik/Documents/projects/DeltaFM/src/CMakeFiles/fc-stamp/ftxui/ftxui-gitclone-lastrun.txt" AND EXISTS "/home/naitik/Documents/projects/DeltaFM/src/CMakeFiles/fc-stamp/ftxui/ftxui-gitinfo.txt" AND
  "/home/naitik/Documents/projects/DeltaFM/src/CMakeFiles/fc-stamp/ftxui/ftxui-gitclone-lastrun.txt" IS_NEWER_THAN "/home/naitik/Documents/projects/DeltaFM/src/CMakeFiles/fc-stamp/ftxui/ftxui-gitinfo.txt")
  message(VERBOSE
    "Avoiding repeated git clone, stamp file is up to date: "
    "'/home/naitik/Documents/projects/DeltaFM/src/CMakeFiles/fc-stamp/ftxui/ftxui-gitclone-lastrun.txt'"
  )
  return()
endif()

# Even at VERBOSE level, we don't want to see the commands executed, but
# enabling them to be shown for DEBUG may be useful to help diagnose problems.
cmake_language(GET_MESSAGE_LOG_LEVEL active_log_level)
if(active_log_level MATCHES "DEBUG|TRACE")
  set(maybe_show_command COMMAND_ECHO STDOUT)
else()
  set(maybe_show_command "")
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/home/naitik/Documents/projects/DeltaFM/src/_deps/ftxui-src"
  RESULT_VARIABLE error_code
  ${maybe_show_command}
)
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/home/naitik/Documents/projects/DeltaFM/src/_deps/ftxui-src'")
endif()

# try the clone 1 + N times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
math(EXPR max_tries "1 + 2")
while(error_code AND number_of_tries LESS ${max_tries})
  if(number_of_tries GREATER 0 AND 0 GREATER 0)
    message(STATUS "Retry #${number_of_tries}, waiting 0 seconds before next attempt...")
    execute_process(COMMAND ${CMAKE_COMMAND} -E sleep 0)
  endif()
  execute_process(
    COMMAND "/usr/bin/git"
            clone --no-checkout --config "advice.detachedHead=false" "https://github.com/ArthurSonzogni/FTXUI.git" "ftxui-src"
    WORKING_DIRECTORY "/home/naitik/Documents/projects/DeltaFM/src/_deps"
    RESULT_VARIABLE error_code
    ${maybe_show_command}
  )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(NOTICE "Had to git clone more than once: ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository:\n  'https://github.com/ArthurSonzogni/FTXUI.git'")
endif()

execute_process(
  COMMAND "/usr/bin/git"
          checkout "main" --
  WORKING_DIRECTORY "/home/naitik/Documents/projects/DeltaFM/src/_deps/ftxui-src"
  RESULT_VARIABLE error_code
  ${maybe_show_command}
)
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'main'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/usr/bin/git" 
            submodule update --recursive --init 
    WORKING_DIRECTORY "/home/naitik/Documents/projects/DeltaFM/src/_deps/ftxui-src"
    RESULT_VARIABLE error_code
    ${maybe_show_command}
  )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/home/naitik/Documents/projects/DeltaFM/src/_deps/ftxui-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy "/home/naitik/Documents/projects/DeltaFM/src/CMakeFiles/fc-stamp/ftxui/ftxui-gitinfo.txt" "/home/naitik/Documents/projects/DeltaFM/src/CMakeFiles/fc-stamp/ftxui/ftxui-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  ${maybe_show_command}
)
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/home/naitik/Documents/projects/DeltaFM/src/CMakeFiles/fc-stamp/ftxui/ftxui-gitclone-lastrun.txt'")
endif()
