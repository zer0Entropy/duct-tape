#include "../../include/utilities/window.hpp"

const DuctTape::Window& DuctTape::WindowManager::GetMainWindow() const {
    return mainWindow;
}

void DuctTape::WindowManager::Init() {
    if(!mainWindow.windowPtr) {
        mainWindow.properties.width = 800;
        mainWindow.properties.height = 600;
        mainWindow.properties.title = "DuctTape Test";
        mainWindow.properties.fullscreen = true;
        mainWindow.Init();
    } // if(!mainWindow.windowPtr)
}
