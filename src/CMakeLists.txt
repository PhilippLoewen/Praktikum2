set(core_SRCS Priorityqueue.cpp Priorityqueue.h)

add_definitions(-std=c++14)

add_library(core ${core_SRCS})
add_executable(exe main.cpp)
target_link_libraries(exe core)