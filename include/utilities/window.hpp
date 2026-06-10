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
        ~Window() {
            sf::RenderWindow* window{windowPtr.release()};
            if(window) {
                windowPtr.reset(nullptr);
                window = nullptr;
            } // if window
        }

        void Init() {

            if(!windowPtr) {
                windowPtr = std::make_unique<sf::RenderWindow>(
                    sf::VideoMode({properties.width, properties.height}),
                    properties.title,
                    sf::Style::Default
                );

                if(!windowPtr->isOpen()) {
                    windowPtr->create(
                        sf::VideoMode({properties.width, properties.height}),
                        properties.title,
                        sf::Style::Default
                    );
                } // if not open
            } // if !windowPtr
            windowPtr->clear();
        } // void Init()
    };

    class WindowManager {
    public:
        WindowManager() = default;
        WindowManager(const WindowManager&) = delete;
        ~WindowManager() = default;

        [[nodiscard]] const Window& GetMainWindow() const;
        void Init();
    private:
        Window mainWindow;
    };
}

#endif //DUCT_TAPE_WINDOW_HPP