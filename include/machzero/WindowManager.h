#pragma once
#include "machzero/views/SplashScreen.h"
#include "machzero/views/MainWindow.h"
#include <vector>

class WindowManager {
    public:
        WindowManager(WindowManager const&)               = delete;
        void operator=(WindowManager const&)              = delete;
        static WindowManager& getInstance();
 
        void showBinaryWindow(std::unique_ptr<llvm::object::Binary>& binary,
                              std::unique_ptr<llvm::WritableMemoryBuffer>& memoryBuffer);
        void windowDied(MainWindow* window);
        void showSplashScreen();

    private:
        WindowManager(); 
        SplashScreen _splashScreen;
        std::vector<std::unique_ptr<MainWindow>> _windows;
};