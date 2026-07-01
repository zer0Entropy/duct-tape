//
// Created by dgmuller on 6/28/26.
//

#ifndef DUCT_TAPE_WINDOW_TEST_HPP
#define DUCT_TAPE_WINDOW_TEST_HPP

#include <array>
#include <memory>

#include "../common/test.hpp"

namespace DuctTape {
    struct Window;
    struct WindowManager;
}

namespace DuctTape::TestFramework {
    struct WindowTests: public TestSequence {
        static constexpr unsigned int NumTests{3};

        static constexpr std::array<std::string_view, NumTests> TestNames{
            "InitTest",
            "ShutdownTest",
            "ResetPropertiesTest"
        };

        Window* window;

        explicit WindowTests() = delete;
        explicit WindowTests(DuctTape::Window* window);

        struct InitTest final: public Test {
            Window* window;

            InitTest() = delete;
            explicit InitTest(std::string_view name, Window* window);
            ~InitTest() override = default;

            TestResult Run() override;
        }; // struct InitTest

        struct ShutdownTest final: public Test {
            Window* window;

            ShutdownTest() = delete;
            explicit ShutdownTest(std::string_view name, Window* window);
            ~ShutdownTest() override = default;

            TestResult Run() override;
        }; // ShutdownTest

        struct ResetPropertiesTest final: public Test {
            Window* window;

            ResetPropertiesTest() = delete;
            explicit ResetPropertiesTest(std::string_view name, Window* window);
            ~ResetPropertiesTest() override = default;

            TestResult Run() override;

        }; // ResetPropertiesTest

    private:
        std::unique_ptr<InitTest> initTest;
        std::unique_ptr<ShutdownTest> shutdownTest;
        std::unique_ptr<ResetPropertiesTest> resetPropertiesTest;
    }; // struct WindowTests

    struct WindowManagerTests: public TestSequence {
        static constexpr unsigned int NumTests{5};

        static constexpr std::array<std::string_view, NumTests> TestNames{
            "InitTest",
            "ShutdownTest",
            "SetResolutionTest",
            "SetTitleTest",
            "SetFullscreenTest"
        };

        WindowManager* windowManager;

        explicit WindowManagerTests() = delete;
        explicit WindowManagerTests(WindowManager* windowManager);
        ~WindowManagerTests() override = default;

        struct InitTest: public Test {
            WindowManager* windowManager;

            InitTest() = delete;
            explicit InitTest(std::string_view name, WindowManager* windowManager);
            ~InitTest() override = default;

            TestResult Run() override;
        };

        struct ShutdownTest: public Test {
            WindowManager* windowManager;

            ShutdownTest() = delete;
            explicit ShutdownTest(std::string_view name, WindowManager* windowManager);
            ~ShutdownTest() override = default;

            TestResult Run() override;
        };

        struct SetResolutionTest: public Test {
            WindowManager* windowManager;

            SetResolutionTest() = delete;
            explicit SetResolutionTest(std::string_view name, WindowManager* windowManager);
            ~SetResolutionTest() override = default;

            TestResult Run() override;
        }; // SetResolutionTest

        struct SetTitleTest: public TestFramework::Test {
            WindowManager* windowManager;

            SetTitleTest() = delete;
            explicit SetTitleTest(std::string_view name, WindowManager* windowManager);
            ~SetTitleTest() override = default;

            TestResult Run() override;
        }; // SetTitleTest

        struct SetFullscreenTest: public Test {
            WindowManager* windowManager;

            SetFullscreenTest() = delete;
            explicit SetFullscreenTest(std::string_view name, WindowManager* windowManager);
            ~SetFullscreenTest() override = default;

            TestResult Run() override;
        }; // SetFullscreenTest
    private:
        std::unique_ptr<InitTest> initTest;
        std::unique_ptr<ShutdownTest> shutdownTest;
        std::unique_ptr<SetResolutionTest> setResolutionTest;
        std::unique_ptr<SetTitleTest> setTitleTest;
        std::unique_ptr<SetFullscreenTest> setFullscreenTest;
    }; // WindowManagerTests
}

#endif //DUCT_TAPE_WINDOW_TEST_HPP
