cmake_minimum_required (VERSION 3.15)

project (WindowsLocaleDb CXX)

add_executable (WindowsLocaleDb main.cpp)
set_target_properties(WindowsLocaleDb PROPERTIES
  CMAKE_CXX_STANDARD 14
  CMAKE_CXX_STANDARD_REQUIRED TRUE
)

target_compile_definitions(WindowsLocaleDb PRIVATE _UNICODE UNICODE)
