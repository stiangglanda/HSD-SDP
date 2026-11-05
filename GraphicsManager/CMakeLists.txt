# CMakeList.txt : CMake project for GraphicsManager (SDP3 Uebung 4)
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("GraphicsManager")

# Add source to this project's executable.
add_executable (GraphicsManager main.cpp
        Object.cpp
        Object.h
        GraphicObject.cpp
        GraphicObject.h
        Circle.cpp
        Circle.h
        Rectangle.cpp
        Rectangle.h
        FilledCircle.cpp
        FilledCircle.h
        BlankCircle.cpp
        BlankCircle.h
        FilledRectangle.cpp
        FilledRectangle.h
        BlankRectangle.cpp
        BlankRectangle.h
        GraphicsObjectFactory.cpp
        GraphicsObjectFactory.h
        FillGraphicsObjectFactory.cpp
        FillGraphicsObjectFactory.h
        BlankGraphicsObjectFactory.cpp
        BlankGraphicsObjectFactory.h
        Image.cpp
        Image.h
        GraphicsManagement.cpp
        GraphicsManagement.h)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GraphicsManager PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
