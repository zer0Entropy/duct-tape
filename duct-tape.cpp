#include "duct-tape.hpp"

DuctTape::Engine& GetInstance() {
    if(!instance) {
        instance = std::make_unique<DuctTape::Engine>();
    } // if not instantiated
    return *instance;
}

void Init() {
    DuctTape::Engine& engine{GetInstance()};
    engine.windowManager.Init();
    engine.initialized = true;
    engine.running = true;
}

void Shutdown() {
    DuctTape::Engine& engine{GetInstance()};
    engine.windowManager.Shutdown();
    engine.initialized = false;
    engine.running = false;
}

