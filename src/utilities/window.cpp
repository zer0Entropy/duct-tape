#include "../../include/utilities/window.hpp"

const DuctTape::Window& DuctTape::WindowManager::GetMainWindow() const {
    return mainWindow;
}

DuctTape::Window& DuctTape::WindowManager::GetMainWindow() {
    return static_cast<Window&>(mainWindow);
}

bool DuctTape::WindowManager::SetResolution(unsigned int width, unsigned int height) {
    WindowProperties properties{width, height, "", false};
    bool valid{ValidateProperties(properties)};
    if(valid) {
        mainWindow.properties.width = width;
        mainWindow.properties.height = height;
    } // if valid
    return valid;
}

bool DuctTape::WindowManager::SetTitle(std::string_view title) {
    WindowProperties properties{MaxWindowWidth, MaxWindowHeight, std::string{title}, false};
    bool valid{ValidateProperties(properties)};
    if(valid) {
        mainWindow.properties.title = std::string{title};
    } // if valid
    return valid;
}

void DuctTape::WindowManager::SetFullscreen(bool fullscreen) {
    mainWindow.properties.fullscreen = fullscreen;
}

void DuctTape::WindowManager::Init() {
    bool propertiesValid{ValidateProperties(mainWindow.properties)};
    if(!mainWindow.windowPtr && propertiesValid) {
        mainWindow.Init();
    } // if(!mainWindow.windowPtr)
}

void DuctTape::WindowManager::Shutdown() {
    if(mainWindow.windowPtr) {
        mainWindow.Shutdown();
    } // if mainWindow.windowPtr
}
