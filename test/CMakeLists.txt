cmake_minimum_required(VERSION 3.3)


project(Example)

#include(CTest)

#enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#include(DownloadProject.cmake)
#download_project(
#        PROJ                googletest
#        GIT_REPOSITORY      https://github.com/google/googletest.git
#        GIT_TAG             master
#        UPDATE DISCONNECTED 1
#)


#add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

set(test_SRCS test.cpp)
add_executable(runUnitTests gtest.cpp ${test_SRCS})
target_link_libraries(runUnitTests ${GTEST_BOTH_LIBRARIES} core)
add_test(runUnitTests runUnitTests) #included in all tutorials but I don't know what it actually does.