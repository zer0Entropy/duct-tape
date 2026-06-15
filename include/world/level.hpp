//
// Created by dgmuller on 6/13/26.
//

#ifndef DUCT_TAPE_LEVEL_HPP
#define DUCT_TAPE_LEVEL_HPP

#include <memory>
#include <vector>
#include "tile.hpp"

namespace DuctTape {
    struct Level {
        static constexpr unsigned int MapWidth = 64;
        static constexpr unsigned int MapHeight = 64;
        Tile map[MapHeight][MapWidth];
        std::vector<std::unique_ptr<Creature>> creatures;
    };
}

#endif //DUCT_TAPE_LEVEL_HPP
