cmake_minimum_required(VERSION 3.25)

project(TestAPI)

set(CMAKE_CXX_STANDARD 20)

include(source/CMakeLists.txt)
foreach(FILE ${FILES})
  set(source ${source} source/${FILE})
endforeach()

add_executable(TestAPI ${source} ${framework} ${collisions} ${geometry} ${level_container} ${level_objects} ${level_data} ${play_screen} ${renderers} ${user_interface})

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(TestAPI PRIVATE /MP /MTd /Zi /W4 /WX /fp:fast)
  target_link_options(TestAPI PRIVATE /SUBSYSTEM:WINDOWS)
endif()

target_precompile_headers(TestAPI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/source/pch.h)

target_include_directories(TestAPI PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/source
)
