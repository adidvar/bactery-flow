# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(bactery-flowTests LANGUAGES CXX)

# ---- Dependencies ----

find_package(Catch2 REQUIRED)
include(Catch)

# ---- Tests ----

add_executable(bactery-flow_test source/bactery-flow_test.cpp)
target_link_libraries(
    bactery-flow_test PRIVATE
    bactery-flow_lib
    Catch2::Catch2WithMain
)
target_compile_features(bactery-flow_test PRIVATE cxx_std_20)

catch_discover_tests(bactery-flow_test)

# ---- End-of-file commands ----

add_folders(Test)
