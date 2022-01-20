Cmake_minimum_required(VERSION 3.4.3)
# CMAKE_SOURCE_DIR variable is the top-level source directory }
# that is given on the cmake command line. The directory of the
# CMakeLists.txt file that CMake currently processes is recorded 
# in the CMAKE_CURRENT_SOURCE_DIR variable.

# If both variables have the same string value, then the project is 
# built standalone. Otherwise, CMAKE_SOURCE_DIR would be the llvm directory:

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    # project name
    project(Tinylang)
    # The LLVM package is searched and the found LLVM directory is added 
    # to the CMake module path
    find_package(LLVM REQUIRED HINTS "${LLVM_CMAKE_PATH}")
    list(APPEND CMAKE_MODULE_PATH ${LLVM_DIR})
    # add the macros used by LLVM and configure the build based on the provided options
    include(AddLLVM)
    include(HandleLLVMOptions)
    # The include directory from the build directory is added because auto-generated files 
    # are saved here. The other include directory is the one inside the source directory
    include_directories("${LLVM_BINARY_DIR}/include" "${LLVM_INCLUDE_DIR}")
    link_directories("${LLVM_LIBRARY_DIR}")
    # With link_directories(), the path of the LLVM libraries is added for the linker
    link_directories("${LLVM_LIBRARY_DIR}")
    # a flag is set to denote that the project is built standalone
    set(TINYLANG_BUILT_STANDALONE 1)
endif()

# The cmake/modules directory is added to the CMake modules search path. 
# This allows us to later add our own CMake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

# Next, we check whether the user is performing an out-of-tree build.
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR AND NOT MSVC_IDE)
    message(FATAL_ERROR "In-source builds are not allowed.")
endif()

# The version number of tinylang is written to a generated file with the
# configure_file()command.
set(TINYLANG_VERSION_STRING "0.1")
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tinylang/Basic/Version.inc.in
    ${CMAKE_CURRENT_BINARY_DIR}/include/tinylang/Basic/Version.inc)

# AddTinylang module has some helper functionality:
include(AddTinylang)

# adds our own include directories to the beginning of the search path. 
# As in the standalone build, two directories are added
include_directories(BEFORE
    ${CMAKE_CURRENT_BINARY_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

# the lib and the tools directories are declared as further directories
add_subdirectory(lib)
add_subdirectory(tools)