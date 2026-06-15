//
// Created by dgmuller on 6/15/26.
//

#include "../../include/core/engine.hpp"
#include "../../test/include/test.hpp"

DuctTape::Engine::Engine():
    initialized{false},
    running{false} {

}

void DuctTape::Engine::Init() {

#ifdef DT_TEST
    initialized = true;
    running = true;
#endif

#ifndef DT_TEST
    // Set the width and height of the window to their default values
    bool setResResult{
        windowManager.SetResolution(windowWidth, windowHeight)
    };
    // Set the window title to its default value
    bool setTitleResult{
        windowManager.SetTitle(windowTitle)
    };
    // Set the fullscreen toggle to its default value
    windowManager.SetFullscreen(true);
    // If no errors have occurred, initialize the windowManager and confirm we're initialized and running
    if(setResResult && setTitleResult) {
        windowManager.Init();
        initialized = true;
        running = true;
    } // if window resolution & title were set successfully
#endif
}

void DuctTape::Engine::Shutdown() {
    windowManager.Shutdown();
    running = false;
    initialized = false;
}

TestResult DuctTape::Engine::RunNextTest() {
    if(!testQueue.empty()) {
        Test* nextTest = testQueue.front();
        testQueue.pop_front();
        if(nextTest) {
            return nextTest->Run();
        } // if nextTest != nullptr
    } // if there are any tests in the testQueue
    return TestResult{"", false};
}