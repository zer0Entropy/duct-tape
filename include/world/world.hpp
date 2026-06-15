//
// Created by dgmuller on 6/15/26.
//

#ifndef DUCT_TAPE_WORLD_HPP
#define DUCT_TAPE_WORLD_HPP

#include "level.hpp"

namespace DuctTape {
    struct World {
        std::vector<std::unique_ptr<Level>> levels;
    };
}

#endif //DUCT_TAPE_WORLD_HPP
