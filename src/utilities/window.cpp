#include "../../include/utilities/window.hpp"
#include "../../include/utilities/window-test.hpp"

DuctTape::Window::Window(std::string_view name):
    NeedsToBeInitialized(),
    NeedsToBeShutdown(),
    TestFramework::TestTarget(name),
    windowPtr{nullptr},
    properties{0, 0, "", false},
    tests{nullptr} {
}

DuctTape::Window::Window(Window& copy):
    TestTarget(copy.name),
    NeedsToBeInitialized(),
    NeedsToBeShutdown(),
    windowPtr{std::move(copy.windowPtr)},
    properties{copy.properties} {
    copy.windowPtr = nullptr;
}

DuctTape::Window::~Window() {
    sf::RenderWindow* window{windowPtr.release()};
    if(window) {
        windowPtr.reset(nullptr);
        window = nullptr;
    } // if window
    if(tests) {
        tests.reset(nullptr);
    } // if tests;
}

bool DuctTape::Window::IsOpen() const  {
    if(windowPtr) {
        return windowPtr->isOpen();
    } // if windowPtr
    return false;
}

bool DuctTape::Window::IsFullscreen() const {
    if(!windowPtr || !windowPtr->isOpen()) {
        return false;
    }
    bool fullscreen{false};
    const sf::Vector2u windowSize{windowPtr->getSize()};
    const sf::VideoMode desktopMode{sf::VideoMode::getDesktopMode()};
    if(windowSize.x == desktopMode.size.x
    && windowSize.y == desktopMode.size.y) {
        fullscreen = true;
    } // if(windowSize == desktopMode)
    return fullscreen;
}

void DuctTape::Window::ResetProperties()  {
    properties.width = properties.height = 0;
    properties.title = "";
    properties.fullscreen = false;
}

void DuctTape::Window::Init()  {
    if(!windowPtr) {
        if(properties.fullscreen) {
            windowPtr = std::make_unique<sf::RenderWindow>(
                sf::VideoMode({properties.width, properties.height}),
                properties.title,
                sf::Style::None
            );
        } // if fullscreen
        else {
            windowPtr = std::make_unique<sf::RenderWindow>(
                sf::VideoMode({properties.width, properties.height}),
                properties.title,
                sf::Style::Default
            );
        } // else !fullscreen
    } // if !windowPtr
    windowPtr->clear();
    initialized = true;
    shutdown = false;
}

void DuctTape::Window::Shutdown()  {
    if(windowPtr) {
        if(windowPtr->isOpen()) {
            windowPtr->close();
        } // if window is open
        windowPtr.reset(nullptr);
        ResetProperties();
        initialized = false;
        shutdown = true;
    } // if windowPtr
}

DuctTape::TestFramework::TestSequence* DuctTape::Window::GetTestSequence() {
    if(!tests) {
        tests = std::make_unique<TestFramework::WindowTests>(this);
    } // if tests haven't been initialized, create them
    return tests.get();
}

DuctTape::WindowManager::WindowManager(std::string_view name):
    NeedsToBeInitialized(),
    NeedsToBeShutdown(),
    TestFramework::TestTarget(name),
    InputHandler(),
    mainWindow{Window::defaultName},
    tests{nullptr} {

}

DuctTape::WindowManager::~WindowManager() {
    if(tests) {
        tests.reset(nullptr);
    } // if tests
}

const DuctTape::Window& DuctTape::WindowManager::GetMainWindow() const {
    return mainWindow;
}

DuctTape::Window& DuctTape::WindowManager::GetMainWindow() {
    return static_cast<Window&>(mainWindow);
}

bool DuctTape::WindowManager::SetResolution(unsigned int width, unsigned int height) {
    WindowProperties properties{width, height, "", false};
    bool valid{ValidateProperties(properties)};
    if(valid) {
        mainWindow.properties.width = width;
        mainWindow.properties.height = height;
    } // if valid
    return valid;
}

bool DuctTape::WindowManager::SetTitle(std::string_view title) {
    WindowProperties properties{MaxWindowWidth, MaxWindowHeight, std::string{title}, false};
    bool valid{ValidateProperties(properties)};
    if(valid) {
        mainWindow.properties.title = std::string{title};
    } // if valid
    return valid;
}

void DuctTape::WindowManager::SetFullscreen(bool fullscreen) {
    if(fullscreen) {
        const auto oldTitle = mainWindow.properties.title;
        const sf::VideoMode desktopMode{sf::VideoMode::getDesktopMode()};
        mainWindow.properties.width = desktopMode.size.x;
        mainWindow.properties.height = desktopMode.size.y;
        bool success{SetResolution(desktopMode.size.x, desktopMode.size.y)};
        if(success && mainWindow.initialized) {
            mainWindow.Shutdown();
            mainWindow.properties.width = desktopMode.size.x;
            mainWindow.properties.height = desktopMode.size.y;
            mainWindow.properties.title = oldTitle;
            mainWindow.properties.fullscreen = true;
            mainWindow.Init();
        } // reinitialize if necessary
    } // if fullscreen
    else {
        if(mainWindow.initialized) {
            const auto oldTitle = mainWindow.properties.title;
            const sf::VideoMode desktopMode{sf::VideoMode::getDesktopMode()};
            mainWindow.Shutdown();
            mainWindow.properties.width = desktopMode.size.x;
            mainWindow.properties.height = desktopMode.size.y;
            mainWindow.properties.title = oldTitle;
            mainWindow.properties.fullscreen = false;
            mainWindow.Init();
        } // reinitialize if necessary
    } // else !fullscreen
    mainWindow.properties.fullscreen = fullscreen;
}

void DuctTape::WindowManager::Init() {
    bool propertiesValid{ValidateProperties(mainWindow.properties)};
    if(!mainWindow.windowPtr && propertiesValid) {
        mainWindow.Init();
        initialized = true;
        shutdown = false;
    } // if(!mainWindow.windowPtr)
}

void DuctTape::WindowManager::Shutdown() {
    if(mainWindow.windowPtr) {
        mainWindow.Shutdown();
        initialized = false;
        shutdown = true;
    } // if mainWindow.windowPtr
}

DuctTape::TestFramework::TestSequence* DuctTape::WindowManager::GetTestSequence() {
    if(!tests) {
        tests = std::make_unique<TestFramework::WindowManagerTests>(this);
    } // if tests have not been initialized, create them
    return tests.get();
}

void DuctTape::WindowManager::HandleInput(const std::optional<sf::Event> input) {
    if(input->is<sf::Event::Closed>()) {
        Shutdown();
    } // if windowClose event
}
