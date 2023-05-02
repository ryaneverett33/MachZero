cmake_minimum_required(VERSION 3.5)

project(MachZero VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

# To use the bundled libc++ please add the following LDFLAGS:
# LDFLAGS="-L/usr/local/opt/llvm/lib -Wl,-rpath,/usr/local/opt/llvm/lib"
#export LDFLAGS="-L/usr/local/opt/llvm/lib"
#export CPPFLAGS="-I/usr/local/opt/llvm/include"
list(APPEND CMAKE_PREFIX_PATH /usr/local/opt/)
find_package(LLVM REQUIRED CONFIG)

set(LLVM_LINK_COMPONENTS
  AllTargetsDescs
  AllTargetsDisassemblers
  AllTargetsInfos
  BinaryFormat
  DebugInfoDWARF
  DebugInfoPDB
  Demangle
  MC
  #MCDisassembler
  Object
  Option
  Support
  Symbolize
)

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})
llvm_map_components_to_libnames(llvm_libs ${LLVM_LINK_COMPONENTS})

set(TS_FILES MachZero_en_US.ts)

# Views
set(VIEW_SOURCES
    src/views/splashscreen.ui
    src/views/mainwindow.ui
    src/views/MainWindow.cpp
    src/views/SplashScreen.cpp
)
set(VIEW_INCLUDES
    include/machzero/views/SplashScreen.h
    include/machzero/views/MainWindow.h
)

# Models
set(MODEL_SOURCES
    src/models/MachObjectModel.cpp
    src/models/MachHeaderModel.cpp
    src/models/LoadCommandModel.cpp
    src/models/ContentsModel.cpp
    src/models/HexDumpModel.cpp
    src/models/EditableSheetModel.cpp
    src/models/LCMainModel.cpp
)
set(MODEL_INCLUDES
    include/machzero/models/MachObjectModel.h
    include/machzero/models/MachHeaderModel.h
    include/machzero/models/LoadCommandModel.h
    include/machzero/models/ContentsModel.h
    include/machzero/models/HexDumpModel.h
    include/machzero/models/EditableSheetModel.h
    include/machzero/models/LCMainModel.h
)
# Items
set(ITEM_SOURCES
    src/items/PositionItem.cpp
    src/items/DataItem.cpp
    src/items/ContentItem.cpp
)
set(ITEM_INCLUDES
    include/machzero/items/DataItem.h
    include/machzero/items/PositionItem.h
    include/machzero/items/ContentItem.h
)

set(PROJECT_SOURCES
        ${VIEW_SOURCES}
        ${VIEW_INCLUDES}
        ${MODEL_SOURCES}
        ${MODEL_INCLUDES}
        ${ITEM_SOURCES}
        ${ITEM_INCLUDES}

        include/machzero/WindowManager.h
        include/machzero/Utils.h
        include/machzero/Constants.h
        src/WindowManager.cpp
        src/Utils.cpp
        src/Constants.cpp
        src/main.cpp
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MachZero
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MachZero APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(MachZero SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MachZero
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(MachZero PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${llvm_libs})
target_include_directories(MachZero PRIVATE include/)

set_target_properties(MachZero PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MachZero)
endif()