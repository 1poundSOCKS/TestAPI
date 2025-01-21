cmake_minimum_required(VERSION 3.25)

project(TestAPI)

if (NOT "$ENV{GSOAP_HOME}" STREQUAL "")
    set(GSOAP_HOME "$ENV{GSOAP_HOME}" CACHE INTERNAL "GSOAP_HOME copied from environment variable")
endif()

message("GSOAP_HOME=${GSOAP_HOME}")

set(CMAKE_CXX_STANDARD 23)

include(source/CMakeLists.txt)
foreach(FILE ${FILES})
  set(source ${source} source/${FILE})
endforeach()

include(source/SOAP/CMakeLists.txt)
foreach(FILE ${FILES})
  set(source ${source} source/SOAP/${FILE})
endforeach()

add_executable(TestAPI ${source} ${GSOAP_HOME}/gsoap-2.8/gsoap/stdsoap2.cpp)

add_custom_command(
  TARGET TestAPI
  PRE_BUILD
  COMMAND ${GSOAP_HOME}/gsoap-2.8/gsoap/bin/win64/wsdl2h -o source/SOAP/sp.h source/SOAP/sp.wsdl
)

add_custom_command(
  TARGET TestAPI
  PRE_BUILD
  COMMAND ${GSOAP_HOME}/gsoap-2.8/gsoap/bin/win64/soapcpp2 -I ${GSOAP_HOME}/gsoap-2.8/gsoap/import -j source/SOAP/sp.h -dsource/SOAP
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(TestAPI PRIVATE /MP /MTd /Zi /W3 /WX /fp:fast)
  target_link_options(TestAPI PRIVATE /SUBSYSTEM:CONSOLE)
endif()

target_precompile_headers(TestAPI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/source/pch.h)

target_include_directories(TestAPI PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/source/SOAP
  ${GSOAP_HOME}/gsoap-2.8/gsoap
)

#target_link_libraries(TestAPI PRIVATE LIBCMTD.lib)
