# CMakeList.txt : CMake project for Player, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Player")

# Add source to this project's executable.
add_executable (Player main.cpp
        Object.h
        Object.cpp
        Player.h
        PlayerClient.cpp
        PlayerClient.h
        Media.cpp
        Media.h
        Video.cpp
        Video.h
        Song.cpp
        Song.h
        VideoPlayer.cpp
        VideoPlayer.h
        MusicPlayer.cpp
        MusicPlayer.h
        VideoAdapter.cpp
        VideoAdapter.h
        MusicAdapter.cpp
        MusicAdapter.h)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Player PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
