//
// Created by dgmuller on 6/17/26.
//

#ifndef DUCT_TAPE_EVENT_HPP
#define DUCT_TAPE_EVENT_HPP

#include <optional>
#include <SFML/Window/Event.hpp>

namespace DuctTape {
    struct Event {
        enum class Type {
            InputReceived = 0,
            NumEventTypes
        };

        Type type;
        std::optional<sf::Event> input;
    };
    struct EventListener {
        virtual ~EventListener() = 0;
        virtual void NotifyEvent(const Event &event) = 0;
    };
}

#endif //DUCT_TAPE_EVENT_HPP
