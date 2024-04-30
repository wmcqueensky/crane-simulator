enable_testing()
cmake_minimum_required(VERSION 3.4)
project(Library)

set(SOURCE_FILES
        include/Container.h
        include/ContainerStack.h
        include/Crane.h
        include/Loadable.h
        include/Truck.h
        src/Container.cpp
        src/ContainerStack.cpp
        src/Crane.cpp
        src/Loadable.cpp
        src/Truck.cpp
        include/LoadStrategy.h
        src/LoadStrategy.cpp)


add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCE_TEST_CONTAINER_FILES
        test/master.cpp
        test/ContainerTest.cpp
        test/ContainerStackTest.cpp
        test/CraneTest.cpp
        test/TruckTest.cpp)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

find_package (Boost 1.60.0 COMPONENTS "unit_test_framework" REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable (TestContainer ${SOURCE_TEST_CONTAINER_FILES})

target_link_libraries (TestContainer
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        Library
)

add_test(TestLibrary1 TestContainer
        --report_level=detailed
        --log_level=all
        --color_output=yes
)

add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
