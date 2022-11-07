cmake_minimum_required(VERSION 3.11)
project(fallthrough)
include(ExternalProject)

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
    # "-DPORTABLE_EXPOSE_ATTRIBUTES=0"
    # "-DFLATCC_RTONLY=on"
)

ExternalProject_Add(boost_proj
  PREFIX         boost
  URL            https://boostorg.jfrog.io/artifactory/main/release/1.80.0/source/boost_1_80_0.tar.bz2
  URL_HASH       SHA256=1e19565d82e43bc59209a168f5ac899d3ba471d55c7610c677d4ccf2c9c500c0
  # GIT_REPOSITORY https://github.com/boostorg/boost
  # GIT_TAG        boost-1.80.0

  # b2 needs to be run in source
  BUILD_IN_SOURCE   true
  CONFIGURE_COMMAND ./bootstrap.sh --prefix=${install_dir}
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ./b2 install --prefix=${install_dir}
)

set(GEN_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(FBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

add_custom_target(gen_example_fbs ALL)
add_custom_command (
  TARGET gen_example_fbs
  COMMAND ${CMAKE_COMMAND} -E make_directory "${GEN_DIR}"
  COMMAND LD_LIBRARY_PATH=install/lib ./install/bin/flatcc -a --json --verifier -o "${GEN_DIR}" "${FBS_DIR}/example.fbs"
  DEPENDS "${FBS_DIR}/example.fbs"
)


list(APPEND CMAKE_PREFIX_PATH ${install_dir})

include_directories("${GEN_DIR}" "${install_dir}/include")
link_directories("${install_dir}/lib")

add_executable(fallthrough main.cc)
add_dependencies(fallthrough gen_example_fbs)

target_compile_options(fallthrough PRIVATE -Wall -Wextra -Wpedantic -Werror)

# Only using Boost headers, no Boost linkage needed.
target_link_libraries(fallthrough flatccrt)
