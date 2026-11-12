# CMakeList.txt : CMake project for DrivingSimulation, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.20)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(DrivingSimulation LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
  asio
  GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
  GIT_TAG asio-1-30-2
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(asio)

FetchContent_Declare(
  sdl2
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG release-2.30.9
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(sdl2)

add_library(DisplayServer DisplayServer.cpp DisplayServer.h)
target_include_directories(DisplayServer PRIVATE ${asio_SOURCE_DIR}/asio/include)
target_compile_definitions(DisplayServer PRIVATE ASIO_STANDALONE)

add_executable(DrivingSimulation main.cpp WindowsDisplay.h WindowsDisplay.cpp)
add_executable(DigitalDisplay DigitalDisplay.cpp)
add_executable(AnalogDisplay AnalogDisplay.cpp)

foreach(target DrivingSimulation DisplayServer DigitalDisplay AnalogDisplay)
  target_include_directories(${target} PRIVATE ${asio_SOURCE_DIR}/asio/include)
  target_compile_definitions(${target} PRIVATE ASIO_STANDALONE)
  set_target_properties(${target} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO)
endforeach()

target_link_libraries(DigitalDisplay PRIVATE DisplayServer SDL2::SDL2main SDL2::SDL2)
target_link_libraries(AnalogDisplay PRIVATE DisplayServer SDL2::SDL2main SDL2::SDL2)
