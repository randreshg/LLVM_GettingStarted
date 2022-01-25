# A CMake option is defined that controls whether the content of this 
# directory is compiled
create_subdirectory_options(TINYLANG TOOL)
# Driver subdirectory is added
add_tinylang_subdirectory(driver)