include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(/usr/local/include)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
link_directories(/usr/local/lib/)

add_executable(${PROJECT_NAME} bank_account.cpp)

add_compile_options(--std=c++17)

add_compile_definitions("PROJECT_DIR=\"${PROJECT_SOURCE_DIR}\"")

include(${PROJECT_SOURCE_DIR}/cmake/CPM.cmake)

find_package(Threads REQUIRED)
CPMAddPackage("gh:chriskohlhoff/asio#asio-1-21-0@1.21.0")


if(asio_ADDED)
  add_library(asio INTERFACE)

  target_include_directories(asio SYSTEM INTERFACE ${asio_SOURCE_DIR}/asio/include)

  target_compile_definitions(asio INTERFACE ASIO_STANDALONE ASIO_NO_DEPRECATED)

  target_link_libraries(asio INTERFACE Threads::Threads)
  if(WIN32)
    # macro see @ https://stackoverflow.com/a/40217291/1746503
    macro(get_win32_winnt version)
      if(CMAKE_SYSTEM_VERSION)
        set(ver ${CMAKE_SYSTEM_VERSION})
        string(REGEX MATCH "^([0-9]+).([0-9])" ver ${ver})
        string(REGEX MATCH "^([0-9]+)" verMajor ${ver})
        # Check for Windows 10, b/c we'll need to convert to hex 'A'.
        if("${verMajor}" MATCHES "10")
          set(verMajor "A")
          string(REGEX REPLACE "^([0-9]+)" ${verMajor} ver ${ver})
        endif("${verMajor}" MATCHES "10")
        # Remove all remaining '.' characters.
        string(REPLACE "." "" ver ${ver})
        # Prepend each digit with a zero.
        string(REGEX REPLACE "([0-9A-Z])" "0\\1" ver ${ver})
        set(${version} "0x${ver}")
      endif()
    endmacro()

    if(NOT DEFINED _WIN32_WINNT)
      get_win32_winnt(ver)
      set(_WIN32_WINNT ${ver})
    endif()

    message(STATUS "Set _WIN32_WINNET=${_WIN32_WINNT}")

    target_compile_definitions(asio INTERFACE _WIN32_WINNT=${_WIN32_WINNT} WIN32_LEAN_AND_MEAN)
  endif()

endif()

target_link_libraries(${PROJECT_NAME} asio)
# unmark the following if you want to use nlohmann/json
# CPMAddPackage("gh:nlohmann/json@3.10.5")
# target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)
