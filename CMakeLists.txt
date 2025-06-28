cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    bactery-flow
    VERSION 0.1.0
    DESCRIPTION "This project uses genetic algorithms to create captivating real-time animations"
    HOMEPAGE_URL "https://github.com/adidvar/bactery-flow"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    bactery-flow_lib OBJECT

    source/bacterium.hpp
    source/field.hpp
    source/food.hpp
    source/lmath.hpp
    source/mainwindow.hpp
    source/network.hpp
    source/nparam.hpp
    source/ptransform.hpp
    source/selection.hpp
    source/simulation.hpp

    source/bacterium.cpp
    source/field.cpp
    source/food.cpp
    source/lmath.cpp
    source/mainwindow.cpp
    source/network.cpp
    source/ptransform.cpp
    source/selection.cpp
    source/simulation.cpp
)

target_include_directories(
    bactery-flow_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(bactery-flow_lib PUBLIC cxx_std_20)

find_package(Eigen3 REQUIRED)
find_package(SFML REQUIRED)
target_link_libraries(bactery-flow_lib PUBLIC Eigen3::Eigen PUBLIC sfml-window PUBLIC sfml-graphics PUBLIC sfml-system)

# ---- Declare executable ----

add_executable(bactery-flow_exe source/main.cpp)
add_executable(bactery-flow::exe ALIAS bactery-flow_exe)

set_property(TARGET bactery-flow_exe PROPERTY OUTPUT_NAME bactery-flow)

target_compile_features(bactery-flow_exe PRIVATE cxx_std_20)

target_link_libraries(bactery-flow_exe PRIVATE bactery-flow_lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT bactery-flow_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of bactery-flow"
  )
endif()

include(cmake/dev-mode.cmake)
