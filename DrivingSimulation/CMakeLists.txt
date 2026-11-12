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

# SDL2 statisch bauen: so muss unter Windows keine SDL2.dll neben den .exe liegen
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_TEST OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  sdl2
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG release-2.30.9
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(sdl2)

find_package(Threads REQUIRED)

# Gemeinsames Asio-Target (header-only) inkl. plattformspezifischer Einstellungen
add_library(asio_headers INTERFACE)
target_include_directories(asio_headers INTERFACE ${asio_SOURCE_DIR}/asio/include)
target_compile_definitions(asio_headers INTERFACE ASIO_STANDALONE)
target_link_libraries(asio_headers INTERFACE Threads::Threads)
if (WIN32)
  # Windows 10/11 als Zielplattform, Winsock-Bibliotheken (fuer MinGW noetig)
  target_compile_definitions(asio_headers INTERFACE _WIN32_WINNT=0x0A00 WIN32_LEAN_AND_MEAN NOMINMAX)
  target_link_libraries(asio_headers INTERFACE ws2_32 mswsock)
endif()

add_library(DisplayServer STATIC DisplayServer.cpp DisplayServer.h)
target_link_libraries(DisplayServer PUBLIC asio_headers)

add_executable(DrivingSimulation main.cpp WindowsDisplay.h WindowsDisplay.cpp)
target_link_libraries(DrivingSimulation PRIVATE asio_headers)

add_executable(DigitalDisplay DigitalDisplay.cpp)
add_executable(AnalogDisplay AnalogDisplay.cpp)

foreach(target DrivingSimulation DisplayServer DigitalDisplay AnalogDisplay)
  set_target_properties(${target} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO)
endforeach()

foreach(target DigitalDisplay AnalogDisplay)
  if (TARGET SDL2::SDL2main)
    target_link_libraries(${target} PRIVATE SDL2::SDL2main)
  endif()
  target_link_libraries(${target} PRIVATE DisplayServer SDL2::SDL2-static)
endforeach()
