//
// Created by dgmuller on 6/15/26.
//

#include "../../include/core/engine.hpp"
#include "../../include/core/engine-test.hpp"

DuctTape::Engine::Engine():
    NeedsToBeInitialized(),
    NeedsToBeShutdown(),
    TestFramework::TestTarget(Engine::name),
    windowManager{WindowManager::name},
    tests{nullptr},
    running{false} {

}

DuctTape::Engine::~Engine() {
    if(tests) {
        tests.reset(nullptr);
    } // if tests
}

void DuctTape::Engine::Init() {
    // Set the width and height of the window to their default values
    const bool setResResult{
        windowManager.SetResolution(windowWidth, windowHeight)
    };
    // Set the window title to its default value
    const bool setTitleResult{
        windowManager.SetTitle(windowTitle)
    };
    // Set the fullscreen toggle to its default value
    windowManager.SetFullscreen(false);
    // If no errors have occurred, initialize the windowManager and confirm we're initialized and running
    if(setResResult && setTitleResult) {
        windowManager.Init();
        initialized = true;
        running = true;
        shutdown = false;
    } // if window resolution & title were set successfully
}

void DuctTape::Engine::Shutdown() {
    windowManager.Shutdown();
    running = false;
    initialized = false;
    shutdown = true;
}

DuctTape::TestFramework::TestSequence* DuctTape::Engine::GetTestSequence() {
    if(!tests) {
        tests = std::make_unique<TestFramework::EngineTests>(this);
    } // if tests has not been initialized, create it
    return tests.get();
}

void DuctTape::Engine::SubscribeListener(EventListener* listener, Event::Type type) {
    const int index{static_cast<int>(type)};
    auto& listenerList{eventListeners[index]};
    listenerList.push_back(listener);
}

void DuctTape::Engine::UnsubscribeListener(EventListener* listener, Event::Type type) {
    const int index{static_cast<int>(type)};
    auto& listenerList{eventListeners[index]};
    for(auto listenItr = listenerList.begin(); listenItr != listenerList.end(); ++listenItr) {
        if(*listenItr == listener) {
            listenerList.erase(listenItr);
            break;
        } // if listener found
    } // for each listener in listenerList
}

bool DuctTape::Engine::UpdateEventQueue() {
    if(!eventQueue.empty()) {
        Event event{eventQueue.front()};
        eventQueue.pop_front();
        const int index{static_cast<int>(event.type)};
        auto& listenerList{eventListeners[index]};
        for(const auto listener: listenerList) {
            listener->NotifyEvent(event);
        } // for each listener in listenerList
    } // if eventQueue is not empty
    else {
        return false;
    } // return false if there are no events in queue
    return true;
}
