# MachZero

MachZero is a Mach-O visualization tool and spiritual re-implementation of [MachOView](https://sourceforge.net/projects/machoview/) with the aim of supporting Windows and Linux in addition to macOS hosts.

## Building

```sh
$ mkdir build/
$ cd build/
$ cmake ../ -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PROJECT_INCLUDE_BEFORE:FILEPATH="/Users/reverett/Qt/Qt Creator.app/Contents/Resources/package-manager/auto-setup.cmake" -DQT_QMAKE_EXECUTABLE:FILEPATH="/Users/reverett/Qt/6.3.1/macos/bin/qmake" -DCMAKE_PREFIX_PATH:PATH="/Users/reverett/Qt/6.3.1/macos"
$ cmake --build .
```

Note: MachZero must be built for at least macOS 12.0 or there will be linker errors when linking-in LLVM.

## Manually Building LLVM

```sh
$ git clone https://github.com/llvm/llvm-project
$ cd llvm-project
$ git checkout llvmorg-16.0.2
$ mkdir build
$ cd build
$ cmake ../llvm -DCMAKE_BUILD_TYPE=RelWithDebInfo -DLLVM_ENABLE_ASSERTIONS=ON -DLLVM_ENABLE_PROJECTS=clang -DLLVM_TARGETS_TO_BUILD="X86;ARM;AArch64"
$ cmake --build .
$ cmake --build . --target install
```