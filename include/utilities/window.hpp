#ifndef DUCT_TAPE_WINDOW_HPP
#define DUCT_TAPE_WINDOW_HPP

#include <array>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../common/init.hpp"
#include "../common/shutdown.hpp"
#include "../common/test.hpp"
#include "../core/input.hpp"

namespace DuctTape::TestFramework {
    struct WindowTests;
    struct WindowManagerTests;
}

namespace DuctTape {
    struct WindowProperties {
        unsigned int width;
        unsigned int height;
        std::string title;
        bool fullscreen;
    };

    struct Window: NeedsToBeInitialized, NeedsToBeShutdown, TestFramework::TestTarget {
        std::unique_ptr<sf::RenderWindow> windowPtr;
        std::unique_ptr<TestFramework::WindowTests> tests;
        WindowProperties properties;

        static constexpr unsigned int MaxTitleLength{256};
        static constexpr std::string_view defaultName{"mainWindow"};

        explicit Window() = delete;
        explicit Window(std::string_view name);
        Window(Window& copy);
        ~Window() override;

        bool IsOpen() const;
        bool IsFullscreen() const;
        void ResetProperties();

        void Init() override;
        void Shutdown() override;

        TestFramework::TestSequence* GetTestSequence() override;
    }; // Window

    struct WindowManager final: NeedsToBeInitialized, NeedsToBeShutdown, TestFramework::TestTarget, InputHandler {
        static constexpr unsigned int MaxWindowWidth = 1920;
        static constexpr unsigned int MaxWindowHeight = 1080;
        static constexpr unsigned int MaxTitleLength = 256;

        static constexpr std::string_view name{"windowManager"};

        std::unique_ptr<TestFramework::WindowManagerTests> tests;
        Window mainWindow;

        [[nodiscard]] static bool ValidateProperties(const WindowProperties& properties) {
            bool valid{true};
            if(properties.width <= 0 || properties.width > MaxWindowWidth) {
                valid = false;
            } // bounds-checking width
            else if(properties.height <= 0 || properties.height > MaxWindowHeight) {
                valid = false;
            } // bounds-checking height
            else if(properties.title.length() > MaxTitleLength) {
                valid = false;
            } // bounds-checking title length
            return valid;
        }

        explicit WindowManager() = delete;
        explicit WindowManager(std::string_view name);
        WindowManager(const WindowManager&) = delete;
        ~WindowManager() override;

        [[nodiscard]] bool SetResolution(unsigned int width, unsigned int height);
        [[nodiscard]] bool SetTitle(std::string_view title);
        void SetFullscreen(bool fullscreen);

        [[nodiscard]] const Window& GetMainWindow() const;
        [[nodiscard]] Window& GetMainWindow();

        void Init() override;
        void Shutdown() override;

        TestFramework::TestSequence* GetTestSequence() override;

        void HandleInput(const std::optional<sf::Event> input) override;
    }; // WindowManager
}

#endif //DUCT_TAPE_WINDOW_HPP