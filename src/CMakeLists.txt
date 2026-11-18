set(CMAKE_CXX_EXTENSIONS OFF)

add_library(src_common INTERFACE)

target_link_libraries(
    src_common INTERFACE hip_cpu_rt::hip_cpu_rt)
target_compile_options(src_common INTERFACE -Wall)

add_subdirectory(hip)
