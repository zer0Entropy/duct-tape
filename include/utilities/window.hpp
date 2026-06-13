#ifndef DUCT_TAPE_WINDOW_HPP
#define DUCT_TAPE_WINDOW_HPP

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

namespace DuctTape {
    struct WindowProperties {
        unsigned int width;
        unsigned int height;
        std::string title;
        bool fullscreen;
    };

    struct Window {
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

        ~Window() {
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

        void Init() {
            if(!windowPtr) {
                windowPtr = std::make_unique<sf::RenderWindow>(
                    sf::VideoMode({properties.width, properties.height}),
                    properties.title,
                    sf::Style::Default
                );
            } // if !windowPtr
            windowPtr->clear();
        } // void Init()

        void Close() {
            if(windowPtr) {
                if(windowPtr->isOpen()) {
                    windowPtr->close();
                } // if window is open
                windowPtr.reset(nullptr);
            } // if windowPtr
        }
    };

    class WindowManager {
    public:
        [[nodiscard]] const Window& GetMainWindow() const;
        [[nodiscard]] Window& GetMainWindow();
        void Init();
        void Shutdown();
    private:
        Window mainWindow;
    };
}

#endif //DUCT_TAPE_WINDOW_HPP