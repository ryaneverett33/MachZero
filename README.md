# MachOViewer


# Building
`cmake -S /Users/reverett/MachOViewer -B /Users/reverett/MachOViewer/build -DCMAKE_GENERATOR:STRING=Ninja -DCMAKE_BUILD_TYPE:STRING=Debug '-DCMAKE_PROJECT_INCLUDE_BEFORE:FILEPATH=/Users/reverett/Qt/Qt Creator.app/Contents/Resources/package-manager/auto-setup.cmake' -DQT_QMAKE_EXECUTABLE:FILEPATH=/Users/reverett/Qt/6.3.1/macos/bin/qmake -DCMAKE_PREFIX_PATH:PATH=/Users/reverett/Qt/6.3.1/macos -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/clang -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++`
`cmake --build build --target all`

Additionally, set the macOS SDK to be at least 12.0.

# Building LLVM

```
mkdir build
cd build
cmake ../llvm -DCMAKE_BUILD_TYPE=RelWithDebInfo -DLLVM_ENABLE_ASSERTIONS=ON -DLLVM_ENABLE_PROJECTS=clang -DLLVM_TARGETS_TO_BUILD="X86;ARM;AArch64"
cmake --build .
cmake --build . --target install
```