#include <iostream>
#include "../include/duct-tape.hpp"
#include "../include/utilities/window.hpp"

int main() {
    DuctTape::Engine& engine{GetInstance()};
    engine.running = true;

    if(engine.running) {
        WindowInitTest windowInitTest{engine.windowManager};
        const TestResult initTestResult{
            windowInitTest.Run()
        };
        std::cout << "Running test #" << std::to_string(static_cast<int>(windowInitTest.GetID()));
        std::cout << ": (" << windowInitTest.GetName() << ")" << std::endl;
        std::cout << "Result: ";
        if(initTestResult.passed) {
            std::cout << "Passed!" << std::endl;
        } // if windowInitTest passed
        else {
            std::cout << "Failed!" << std::endl;
            std::cout << "Details: " << initTestResult.details << std::endl;
        } // else windowInitTest failed

        WindowCloseTest windowCloseTest{engine.windowManager};
        const TestResult closeTestResult{
            windowCloseTest.Run()
        };
        std::cout << "Running test #" << std::to_string(static_cast<int>(windowCloseTest.GetID()));
        std::cout << ": (" << windowCloseTest.GetName() << ")" << std::endl;
        std::cout << "Result: ";
        if(initTestResult.passed) {
            std::cout << "Passed!" << std::endl;
        } // if windowCloseTest passed
        else {
            std::cout << "Failed!" << std::endl;
            std::cout << "Details: " << initTestResult.details << std::endl;
        } // else windowCloseTest failed

        DuctTape::Window& window{engine.windowManager.GetMainWindow()};
        while(window.IsOpen()) {
            while(const std::optional event = window.windowPtr->pollEvent()) {
                if(event->is<sf::Event::Closed>()) {
                    engine.running = false;
                    break;
                } // if window is closed
            } // while event
            window.windowPtr->display();
        } // while window is open
    } // if(engine.running)
    Shutdown();
    return 0;
}