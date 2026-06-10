//
// Created by dgmuller on 6/10/26.
//

#ifndef DUCT_TAPE_ENGINE_HPP
#define DUCT_TAPE_ENGINE_HPP

#include "../utilities/window.hpp"

namespace DuctTape {
    struct Engine {
        WindowManager windowManager;
        bool initialized;
        bool running;

        Engine():
            initialized{false},
            running{false} {

        }

        ~Engine() = default;
    };
}

#endif //DUCT_TAPE_ENGINE_HPP