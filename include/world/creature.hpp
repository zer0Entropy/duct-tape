//
// Created by dgmuller on 6/13/26.
//

#ifndef DUCT_TAPE_CREATURE_HPP
#define DUCT_TAPE_CREATURE_HPP

#include <string>
#include <SFML/Graphics/Texture.hpp>

namespace DuctTape {
    struct Creature {
        enum class BaseType {
            Animal,
            Human,
            Dwarf,
            DarkElf,
            GrayElf,
            WoodElf,
            Halfling,
            Draconian,
            Monster
        };

        BaseType baseType;
        std::string typeName;
        std::string uniqueName;
        sf::Texture* texture;
    };
}

#endif //DUCT_TAPE_CREATURE_HPP
