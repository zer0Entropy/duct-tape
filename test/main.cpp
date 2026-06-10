#include "../duct-tape.hpp"

int main() {
    DuctTape::Engine& engine{GetInstance()};

    Init();

    while(engine.running) {
        const DuctTape::Window& mainWindow{engine.windowManager.GetMainWindow()};
        if(!mainWindow.windowPtr->isOpen()) {
            engine.running = false;
            break;
        } // if mainWindow is not open, stop the engine
        mainWindow.windowPtr->display();
    } // while engine is running

    return 0;
}