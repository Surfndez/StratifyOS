
if( ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin" )
  message(STATUS "Use CLANG on Darwin")
  include(${CMAKE_CURRENT_LIST_DIR}/link-clang-toolchain.cmake)
endif()
if( ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows" )
  message(STATUS "Use MinGW on Windows")
  set(CMAKE_MAKE_PROGRAM "C:/StratifyLabs-SDK/Tools/gcc/bin/mingw32-make.exe")
  set(CMAKE_SET_GENERATOR "MinGW Makefiles" CACHE INTERNAL "cmake generator mingw makefiles")
  include(${CMAKE_CURRENT_LIST_DIR}/link-mingw-toolchain.cmake)
endif()
