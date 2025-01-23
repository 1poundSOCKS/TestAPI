cmake_minimum_required(VERSION 3.25)

project(TestAPI)

set(CMAKE_CXX_STANDARD 23)

include(source/CMakeLists.txt)
foreach(FILE ${FILES})
  set(source ${source} source/${FILE})
endforeach()

include(source/SOAP/CMakeLists.txt)
foreach(FILE ${FILES})
  set(source ${source} source/SOAP/${FILE})
endforeach()

add_executable(TestAPI ${source} ${CMAKE_CURRENT_SOURCE_DIR}/gsoap-2.8/stdsoap2.cpp)

add_custom_command(
  TARGET TestAPI
  PRE_BUILD
  COMMAND gsoap-2.8/bin/win64/wsdl2h -o source/SOAP/sp.h source/SOAP/sp.wsdl
)

add_custom_command(
  TARGET TestAPI
  PRE_BUILD
  COMMAND gsoap-2.8/bin/win64/soapcpp2 -I gsoap-2.8/import -j source/SOAP/sp.h -dsource/SOAP
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(TestAPI PRIVATE /MP /MTd /Zi /W3 /WX /fp:fast)
  target_link_options(TestAPI PRIVATE /SUBSYSTEM:CONSOLE)
endif()

target_precompile_headers(TestAPI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/source/pch.h)

target_include_directories(TestAPI PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/gsoap-2.8
  ${CMAKE_CURRENT_SOURCE_DIR}/gsoap-2.8/import
  ${CMAKE_CURRENT_SOURCE_DIR}/source/SOAP
)
