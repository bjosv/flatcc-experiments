cmake_minimum_required(VERSION 3.11)
project(enum LANGUAGES C)
include(ExternalProject)

# Use local install directory
set(install_dir ${CMAKE_CURRENT_BINARY_DIR}/install)

ExternalProject_Add(flatcc_proj
  PREFIX flatcc
  GIT_REPOSITORY  https://github.com/dvidelabs/flatcc
  GIT_TAG         v0.6.1
  CMAKE_ARGS
    "-DBUILD_SHARED_LIBS=on"
    "-DCMAKE_BUILD_TYPE=Release"
    "-DCMAKE_INSTALL_PREFIX:PATH=${install_dir}"
    "-DFLATCC_INSTALL=on"
    "-DFLATCC_TEST=off"
    "-DFLATCC_CXX_TEST=off"
)

set(GEN_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(FBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

add_custom_target(gen_example_fbs ALL)
add_custom_command(
  TARGET gen_example_fbs
  COMMAND ${CMAKE_COMMAND} -E make_directory "${GEN_DIR}"
  COMMAND LD_LIBRARY_PATH=install/lib ./install/bin/flatcc -a --json --verifier -o "${GEN_DIR}" "${FBS_DIR}/example.fbs"
  DEPENDS "${FBS_DIR}/example.fbs"
)

include_directories("${GEN_DIR}" "${install_dir}/include")
link_directories("${install_dir}/lib")

add_executable(enum main.c)
add_dependencies(enum gen_example_fbs)
target_link_libraries(enum flatccrt)
