# CMakeList.txt : CMake project for MusicPlayer (Visitor, Composite, Factory)
#
cmake_minimum_required (VERSION 3.10)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("MusicPlayer")

# Add source to this project's executable.
add_executable (MusicPlayer main.cpp
        Object.h
        Media.cpp
        Media.h
        Publication.cpp
        Publication.h
        Song.cpp
        Song.h
        Album.cpp
        Album.h
        Collection.cpp
        Collection.h
        ICollection.h
        Visitor.h
        VisitorSearch.cpp
        VisitorSearch.h
        VisitorPlay.cpp
        VisitorPlay.h
        SimpleMediaFactory.cpp
        SimpleMediaFactory.h
        MusicPlayer.cpp
        MusicPlayer.h)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MusicPlayer PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
