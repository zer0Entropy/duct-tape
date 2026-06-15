#include <iostream>
#include "../include/duct-tape.hpp"
#include "../include/utilities/window.hpp"

int main() {
    DuctTape::Engine& engine{GetInstance()};
    engine.Init();

    WindowInitTest windowInitTest{engine.windowManager};
    engine.testQueue.push_back(&windowInitTest);

    WindowCloseTest windowCloseTest{engine.windowManager};
    engine.testQueue.push_back(&windowCloseTest);

    while(engine.running) {
        if(!engine.testQueue.empty()) {
            const Test& nextTest{*engine.testQueue.front()};
            DisplayTestIntro(nextTest);
            TestResult result{engine.RunNextTest()};
            DisplayTestResult(result);
        } // if test queue is not empty
        else {
            engine.Shutdown();
        } // when tests are done, shutdown engine

        DuctTape::Window& window{engine.windowManager.GetMainWindow()};
        if(window.IsOpen()) {
            while(const std::optional event = window.windowPtr->pollEvent()) {
                if(event->is<sf::Event::Closed>()) {
                    engine.running = false;
                    break;
                } // if Closed event
            } // while events remain in queue
            window.windowPtr->display();
        } // if window is open
    } // while engine is running

    Shutdown();
    return 0;
}