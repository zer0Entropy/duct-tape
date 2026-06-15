//
// Created by dgmuller on 6/10/26.
//

#ifndef DUCT_TAPE_ENGINE_HPP
#define DUCT_TAPE_ENGINE_HPP

#include <deque>
#include "../common/init.hpp"
#include "../common/shutdown.hpp"
#include "../utilities/window.hpp"
#include "../../test/include/result.hpp"

struct Test;

namespace DuctTape {
    struct Engine final: NeedsToBeInitialized, NeedsToBeShutdown {
        // TODO: Read configuration data from file on disk instead of hard-coding
        static constexpr unsigned int windowWidth{1920};
        static constexpr unsigned int windowHeight{1080};
        static constexpr std::string_view windowTitle{"DuctTape Engine"};

        /** These are used for running tests **/
        std::deque<Test*> testQueue;
        TestResult RunNextTest();
        /** These are used for running tests **/

        WindowManager windowManager;

        bool initialized;
        bool running;

        Engine();
        ~Engine() override = default;

        void Init() override;
        void Shutdown() override;

    };
}

#endif //DUCT_TAPE_ENGINE_HPP