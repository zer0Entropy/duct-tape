//
// Created by dgmuller on 6/21/26.
//

#ifndef DUCT_TAPE_ENGINE_TEST_HPP
#define DUCT_TAPE_ENGINE_TEST_HPP

#include <array>
#include <memory>

#include "../common/test.hpp"

namespace DuctTape {
    struct Engine;
}

namespace DuctTape::TestFramework {
        struct EngineTests: public TestSequence {

            static constexpr unsigned int NumTests{2};

            static constexpr std::array<std::string_view, NumTests> TestNames{
                "InitTest",
                "ShutdownTest"
            };

            Engine* engine;

            EngineTests() = delete;
            explicit EngineTests(DuctTape::Engine* engine);
            ~EngineTests() final = default;

            struct InitTest final: public Test {
                DuctTape::Engine* engine;

                InitTest() = delete;
                explicit InitTest(std::string_view name, DuctTape::Engine* engine);
                ~InitTest() override = default;

                TestResult Run() override;
            }; // InitTest

            struct ShutdownTest final: public Test {
                DuctTape::Engine* engine;

                ShutdownTest() = delete;
                explicit ShutdownTest(std::string_view name, DuctTape::Engine* engine);
                ~ShutdownTest() override = default;

                TestResult Run() override;
            }; // ShutdownTest

        private:
            std::unique_ptr<InitTest> initTest;
            std::unique_ptr<ShutdownTest> shutdownTest;
        }; // EngineTests
}

#endif //DUCT_TAPE_ENGINE_TEST_HPP
