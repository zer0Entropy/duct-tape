#include "../duct-tape.hpp"

int main() {
    DuctTape::Engine& engine{GetInstance()};

    Init();

    while(engine.running) {
        const DuctTape::Window& mainWindow{engine.windowManager.GetMainWindow()};
        if(mainWindow.windowPtr->isOpen()) {
            while(const std::optional event = mainWindow.windowPtr->pollEvent()) {
                if(event->is<sf::Event::Closed>()) {
                    engine.running = false;
                    break;
                } // if main window closed
            } // while event
        } // if main window is open
        else {
            engine.running = false;
            break;
        } // if main window is not open, stop the engine
        mainWindow.windowPtr->display();
    } // while engine is running

    Shutdown();

    return 0;
}