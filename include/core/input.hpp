//
// Created by dgmuller on 6/15/26.
//

#ifndef DUCT_TAPE_INPUT_HPP
#define DUCT_TAPE_INPUT_HPP

#include <optional>
#include <SFML/Window/Event.hpp>

namespace DuctTape {
    struct InputHandler {
        virtual ~InputHandler() = 0;
        virtual void HandleInput(const std::optional<sf::Event> input) = 0;
    };
}

#endif //DUCT_TAPE_INPUT_HPP
