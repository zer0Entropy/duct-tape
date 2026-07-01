//
// Created by dgmuller on 6/10/26.
//

#ifndef DUCT_TAPE_ENGINE_HPP
#define DUCT_TAPE_ENGINE_HPP

#include <array>
#include <deque>
#include <vector>
#include "event.hpp"
#include "../common/init.hpp"
#include "../common/shutdown.hpp"
#include "../common/test.hpp"
#include "../utilities/window.hpp"

namespace DuctTape::TestFramework {
    struct EngineTests;
};

namespace DuctTape {
    struct Engine final: NeedsToBeInitialized, NeedsToBeShutdown, TestFramework::TestTarget {
        // TODO: Read configuration data from file on disk instead of hard-coding
        static constexpr unsigned int windowWidth{1920};
        static constexpr unsigned int windowHeight{1080};
        static constexpr std::string_view windowTitle{"DuctTape Engine"};
        static constexpr std::string_view name{"DTEngine"};

        WindowManager windowManager;
        std::unique_ptr<TestFramework::EngineTests> tests;
        std::deque<Event> eventQueue;
        std::array<std::vector<EventListener*>, static_cast<int>(Event::Type::NumEventTypes)> eventListeners;

        bool running;

        explicit Engine();
        ~Engine() override;

        void Init() override;
        void Shutdown() override;

        TestFramework::TestSequence* GetTestSequence() override;

        void SubscribeListener(EventListener* listener, Event::Type type);
        void UnsubscribeListener(EventListener* listener, Event::Type type);
        bool UpdateEventQueue();

    }; // Engine
}

#endif //DUCT_TAPE_ENGINE_HPP