#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/raw_ostream.h"
#include "tinylang/Basic/Version.h"

int main(int argc_, const char **argv_) {
    // Basic initialization
    llvm::InitLLVM X(argc_, argv_);
    // LLVM output stream
    llvm::outs() << "Hello, I am Tinylang "
                 << tinylang::getTinyLangVersion()
                 <<"\n";
}