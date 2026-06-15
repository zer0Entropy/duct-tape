#ifndef DUCT_TAPE_WINDOW_HPP
#define DUCT_TAPE_WINDOW_HPP

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../common/init.hpp"
#include "../common/shutdown.hpp"

namespace DuctTape {
    struct WindowProperties {
        unsigned int width;
        unsigned int height;
        std::string title;
        bool fullscreen;
    };

    struct Window: NeedsToBeInitialized, NeedsToBeShutdown {
        std::unique_ptr<sf::RenderWindow> windowPtr;
        WindowProperties properties;

        Window():
            windowPtr{nullptr},
            properties{0, 0, "", false} {
        }

        Window(Window& copy):
            windowPtr{std::move(copy.windowPtr)},
            properties{copy.properties} {
            copy.windowPtr = nullptr;
        }

        ~Window() override {
            sf::RenderWindow* window{windowPtr.release()};
            if(window) {
                windowPtr.reset(nullptr);
                window = nullptr;
            } // if window
        }

        bool IsOpen() const {
            if(windowPtr) {
                return windowPtr->isOpen();
            } // if windowPtr
            return false;
        }

        void ResetProperties() {
            properties.width = properties.height = 0;
            properties.title = "";
            properties.fullscreen = false;
        }

        void Init() override {
            if(!windowPtr) {
                windowPtr = std::make_unique<sf::RenderWindow>(
                    sf::VideoMode({properties.width, properties.height}),
                    properties.title,
                    sf::Style::Default
                );
            } // if !windowPtr
            windowPtr->clear();
        }

        void Shutdown() override {
            if(windowPtr) {
                if(windowPtr->isOpen()) {
                    windowPtr->close();
                } // if window is open
                windowPtr.reset(nullptr);
                ResetProperties();
            } // if windowPtr
        }
    };

    class WindowManager final: NeedsToBeInitialized, NeedsToBeShutdown {
    public:
        static constexpr unsigned int MaxWindowWidth = 1920;
        static constexpr unsigned int MaxWindowHeight = 1080;
        static constexpr unsigned int MaxTitleLength = 256;

        [[nodiscard]] static bool ValidateProperties(const WindowProperties& properties) {
            bool valid = true;
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

        WindowManager() = default;
        ~WindowManager() override = default;

        [[nodiscard]] bool SetResolution(unsigned int width, unsigned int height);
        [[nodiscard]] bool SetTitle(std::string_view title);
        void SetFullscreen(bool fullscreen);

        [[nodiscard]] const Window& GetMainWindow() const;
        [[nodiscard]] Window& GetMainWindow();

        void Init() override;
        void Shutdown() override;
    private:
        Window mainWindow;
    };
}

#endif //DUCT_TAPE_WINDOW_HPP