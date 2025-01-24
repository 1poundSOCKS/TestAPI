cmake_minimum_required(VERSION 3.25)

project(TestAPI)

set(CMAKE_CXX_STANDARD 23)

include(source/SOAP/CMakeLists.txt)
foreach(FILE ${FILES})
  set(source ${source} source/SOAP/${FILE})
endforeach()

include(source/common/CMakeLists.txt)
foreach(FILE ${FILES})
  set(source ${source} source/common/${FILE})
endforeach()

add_executable(Login source/login.cpp ${source} ${CMAKE_CURRENT_SOURCE_DIR}/gsoap-2.8/stdsoap2.cpp)

add_executable(GetJob source/getjob.cpp ${source} ${CMAKE_CURRENT_SOURCE_DIR}/gsoap-2.8/stdsoap2.cpp)

add_custom_command(
  TARGET Login
  PRE_BUILD
  COMMAND gsoap-2.8/bin/win64/wsdl2h -o source/SOAP/sp.h source/SOAP/sp.wsdl
)

add_custom_command(
  TARGET Login
  PRE_BUILD
  COMMAND gsoap-2.8/bin/win64/soapcpp2 -I gsoap-2.8/import -j source/SOAP/sp.h -dsource/SOAP
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(Login PRIVATE /MP /MTd /Zi /W3 /WX /fp:fast)
  target_link_options(Login PRIVATE /SUBSYSTEM:CONSOLE)
  target_compile_options(GetJob PRIVATE /MP /MTd /Zi /W3 /WX /fp:fast)
  target_link_options(GetJob PRIVATE /SUBSYSTEM:CONSOLE)
endif()

target_precompile_headers(Login PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/source/pch.h)
target_precompile_headers(GetJob PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/source/pch.h)

target_include_directories(Login PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/gsoap-2.8
  ${CMAKE_CURRENT_SOURCE_DIR}/gsoap-2.8/import
  ${CMAKE_CURRENT_SOURCE_DIR}/source/SOAP
)

target_include_directories(GetJob PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/gsoap-2.8
  ${CMAKE_CURRENT_SOURCE_DIR}/gsoap-2.8/import
  ${CMAKE_CURRENT_SOURCE_DIR}/source/SOAP
)
