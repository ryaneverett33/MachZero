#include "machzero/WindowManager.h"
#include <algorithm>

WindowManager::WindowManager() {
    _splashScreen.hide();
}

void WindowManager::showSplashScreen() {
    _splashScreen.show();
}

void WindowManager::showBinaryWindow(std::unique_ptr<llvm::object::Binary>& binary, 
                                     std::unique_ptr<llvm::WritableMemoryBuffer>& memoryBuffer) {
    // create a window for the binary
    std::unique_ptr<MainWindow> window = std::make_unique<MainWindow>();
    window->setActiveBinary(binary, memoryBuffer);
    window->show();

    _windows.push_back(std::move(window));
    if (_windows.size() == 1) {
        _splashScreen.hide();
    }
}

void WindowManager::windowDied(MainWindow* window) {
    // if a window died, free it
    auto eraser = [&window](std::unique_ptr<MainWindow>& candidate) {
        return candidate.get() == window;
    };

    size_t sizeBefore = _windows.size();
    std::vector<std::unique_ptr<MainWindow>>::iterator erased = 
        _windows.erase(std::remove_if(_windows.begin(), _windows.end(), eraser), _windows.end());
    
    if (sizeBefore == _windows.size()) {
        printf("failed to erase window\n");
    }
}


WindowManager& WindowManager::getInstance() {
    // why is this Singleton access a pointer and not a reference type?
    // because I'm too stupid to properly use C++ and a pointer lets me not
    // seg fault. Fuck you C++.
    static WindowManager _instance;
    return _instance;
}