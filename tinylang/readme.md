### TINYLANG ###

Compile tinylang as a standalone project using previous compiled version on LLVM

Build LLVM
```
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release \
-DCMAKE_INSTALL_PREFIX=../llvm-12 \
../llvm-project/llvm

ninja
sudo ninja install
```

Build tinylang
```
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release \
-DLLVM_EXTERNAL_PROJECTS=tinylang \
-DLLVM_EXTERNAL_TINYLANG_SOURCE_DIR=../tinylang/tinylang \
-DCMAKE_INSTALL_PREFIX=../llvm-12 \
../llvm-project/llvm

ninja
sudo ninja install
```

Tutorial by: https://github.com/PacktPublishing/Learn-LLVM-12

