#include "duct-tape.hpp"

void Init() {
    DuctTape::Engine& engine{GetInstance()};
    engine.windowManager.Init();
    engine.initialized = true;
    engine.running = true;
}

DuctTape::Engine& GetInstance() {
    if(!instance) {
        instance = std::make_unique<DuctTape::Engine>();
    } // if not instantiated
    return *instance;
}
