//
// Created by dgmuller on 6/13/26.
//

#ifndef DUCT_TAPE_TILE_HPP
#define DUCT_TAPE_TILE_HPP

#include <string>
#include <SFML/Graphics/Texture.hpp>
#include "creature.hpp"

namespace DuctTape {
    using TerrainID = unsigned int;

    struct Terrain {

        enum class BaseType {
            Floor,
            Wall
        };

        TerrainID id;
        BaseType baseType;
        std::string name;
        sf::Texture* texture;
    };

    struct Tile {
        TerrainID terrainID;
        Creature* creature;
    };
}

#endif //DUCT_TAPE_TILE_HPP
