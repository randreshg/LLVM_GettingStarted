# The LLVM_LINK_COMPONENTS is set to the list of LLVM 
# components that we need to link our tool against
set(LLVM_LINK_COMPONENTS 
    Support
)
# A new installable application is defined
add_tinylang_tool(tinylang
    Driver.cpp
)
# To link against our own libraries we have to specify them with
# target_link_libraries.
target_link_libraries(tinylang
    PRIVATE
    tinylangBasic
)