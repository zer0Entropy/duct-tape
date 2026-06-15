//
// Created by dgmuller on 6/15/26.
//

#ifndef DUCT_TAPE_GAME_HPP
#define DUCT_TAPE_GAME_HPP

#include "player.hpp"
#include "../world/world.hpp"

namespace DuctTape {
    struct Game {
        World world;
        Player player;
        bool initialized;
    };
}

#endif //DUCT_TAPE_GAME_HPP
