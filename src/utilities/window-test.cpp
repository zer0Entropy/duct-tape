//
// Created by dgmuller on 6/28/26.
//
#include "../../include/utilities/window-test.hpp"
#include "../../include/utilities/window-test.hpp"
#include "../../include/utilities/window-test.hpp"
#include "../../include/utilities/window.hpp"
#include "../../include/core/engine.hpp"

DuctTape::TestFramework::WindowTests::WindowTests(DuctTape::Window* window):
    TestSequence(),
    window{window},
    initTest{std::make_unique<InitTest>(WindowTests::TestNames.at(0), window)},
    shutdownTest{std::make_unique<ShutdownTest>(WindowTests::TestNames.at(1),window)},
    resetPropertiesTest{std::make_unique<ResetPropertiesTest>(WindowTests::TestNames.at(2),window)} {
    tests.push_back(initTest.get());
    tests.push_back(shutdownTest.get());
    tests.push_back(resetPropertiesTest.get());
}

DuctTape::TestFramework::WindowTests::InitTest::InitTest(std::string_view name, Window* window):
    Test(name),
    window{window} {

}

DuctTape::TestFramework::TestResult DuctTape::TestFramework::WindowTests::InitTest::Run() {
    TestResult result;

    // TEST: window == nullptr (must be FALSE)
    if(!window) {
        result = TestResult{"unexpected nullptr, ResetPropertiesTest was not properly initialized"};
        return result;
    } // TEST: window == nullptr

    window->properties.width = Engine::windowWidth;
    window->properties.height = Engine::windowHeight;
    window->properties.title = Engine::windowTitle;
    window->properties.fullscreen = false;
    window->Init();

    // TEST: window->windowPtr == nullptr (must be FALSE)
    if(!window->windowPtr) {
        result = TestResult{"unexpected nullptr, window was not properly initialized"};
    } // TEST: window->windowPtr == nullptr

    // TEST: window->IsOpen() == true (must be TRUE)
    else if(!window->IsOpen()) {
        result = TestResult{"window failed to open"};
    } // TEST: window->IsOpen()

    // TEST: window->IsInitialized() (must be TRUE)
    else if(!window->IsInitialized()) {
        result = TestFramework::TestResult{"window failed to set initialized flag to true"};
    } // TEST: window->IsInitialized()

    // TEST: window->IsShutdown() (must be FALSE)
    else if(window->IsShutdown()) {
        result = TestFramework::TestResult{"window failed to set shutdown flag to false"};
    } // TEST: window->IsShutdown()

    return result;
}

DuctTape::TestFramework::WindowTests::ShutdownTest::ShutdownTest(std::string_view name, Window* window):
    Test(name),
    window{window} {
}

DuctTape::TestFramework::TestResult DuctTape::TestFramework::WindowTests::ShutdownTest::Run() {
    TestResult result;
    window->Shutdown();

    // TEST: window->windowPtr == nullptr (must be TRUE)
    if(window->windowPtr) {
        // TEST: window->IsOpen() == true (must be false)
        if(window->IsOpen()) {
            result = TestResult{"window failed to close"};
        } // TEST: window->IsOpen()

        else { // window is closed
            result = TestResult{"window was not properly shutdown (windowPtr != nullptr)"};
        } // else (window is closed)
    } // TEST: window->windowPtr == nullptr

    // TEST: window->IsInitialized() (must be FALSE)
    else if(window->IsInitialized()) {
        result = TestResult{"window failed to reset initialized flag to false"};
    } // TEST: window->IsInitialized()

    // TEST: window->IsShutdown() (must be TRUE)
    else if(!window->IsShutdown()) {
        result = TestResult{"window failed to set shutdown flag to true"};
    } // TEST: window->IsShutdown()

    return result;
} // ShutdownTest::Run()

DuctTape::TestFramework::WindowTests::ResetPropertiesTest::ResetPropertiesTest(std::string_view name, Window* window):
    Test(name),
    window{window} {

}

DuctTape::TestFramework::TestResult DuctTape::TestFramework::WindowTests::ResetPropertiesTest::Run() {
    TestResult result;

    // TEST: window == nullptr (must be FALSE)
    if(!window) {
        result = TestResult{"unexpected nullptr, ResetPropertiesTest was not properly initialized"};
        return result;
    } // TEST: window == nullptr

    window->ResetProperties();

    // TEST: width == 0 (must be TRUE)
    if(window->properties.width != 0) {
        result = TestResult{"window width was not properly initialized"};
        result.details += " ";
        result.details += "(value = ";
        result.details += std::to_string(window->properties.width);
        result.details += ", expected value = 0)";
    } // TEST: width == 0

    // TEST: height == 0 (must be TRUE)
    else if(window->properties.height != 0) {
        result = TestResult{"window height was not properly initialized"};
        result.details += " ";
        result.details += "(value = ";
        result.details += std::to_string(window->properties.height);
        result.details += ", expected value = 0)";
    } // TEST: height == 0

    // TEST: title == "" (must be TRUE)
    else if(window->properties.title.length() != 0) {
        result = TestResult{"window title was not properly initialized"};
        result.details += " ";
        result.details += "(value = ";
        result.details += window->properties.title;
        result.details += ", expected value = \"\")";
    } // TEST: title == ""

    // TEST: fullscreen == false (must be TRUE)
    else if(window->properties.fullscreen != false) {
        result = TestResult{"fullscreen was not properly initialized"};
        result.details += " ";
        result.details += "(value = true, expected value = false)";
    } // TEST: fullscreen == false

    return result;
} // ResetPropertiesTest::Run()

DuctTape::TestFramework::WindowManagerTests::WindowManagerTests(WindowManager* windowManager):
    TestSequence(),
    windowManager{windowManager},
    initTest{std::make_unique<InitTest>(TestNames.at(0), windowManager)},
    shutdownTest{std::make_unique<ShutdownTest>(TestNames.at(1), windowManager)},
    setResolutionTest{std::make_unique<SetResolutionTest>(TestNames.at(2), windowManager)},
    setTitleTest(std::make_unique<SetTitleTest>(TestNames.at(3), windowManager)),
    setFullscreenTest(std::make_unique<SetFullscreenTest>(TestNames.at(4), windowManager)) {
    tests.push_back(initTest.get());
    tests.push_back(shutdownTest.get());
    tests.push_back(setResolutionTest.get());
    tests.push_back(setTitleTest.get());
    tests.push_back(setFullscreenTest.get());
}

DuctTape::TestFramework::WindowManagerTests::InitTest::InitTest(std::string_view name, WindowManager* windowManager):
    TestFramework::Test(name),
    windowManager{windowManager} {

}

DuctTape::TestFramework::TestResult DuctTape::TestFramework::WindowManagerTests::InitTest::Run() {
    TestResult result;

    // TEST: windowManager == nullptr (must be FALSE)
    if(!windowManager) {
        result = TestResult{"unexpected nullptr - InitTest was not properly initialized"};
        return result;
    }
    // TEST: windowManager == nullptr

    windowManager->Init();

    // TEST: windowManager->IsInitialized() (must be TRUE)
    if(!windowManager->IsInitialized()) {
        result = TestResult{"windowManager was not properly initialized"};
    } // TEST: windowManager->IsInitialized()

    // TEST: windowManager->IsShutdown() (must be FALSE)
    else if(windowManager->IsShutdown()) {
        result = TestResult{"windowManager unexpectedly shut down during initialization"};
    } // TEST: windowManager->IsShutdown()

    // TEST: window.IsOpen() (must be TRUE)
    else if(!windowManager->GetMainWindow().IsOpen()) {
        result = TestResult{"window failed to open"};
    } // TEST: window.IsOpen()

    return result;
}

DuctTape::TestFramework::WindowManagerTests::ShutdownTest::ShutdownTest(std::string_view name, WindowManager* windowManager):
    Test(name),
    windowManager{windowManager} {

}

DuctTape::TestFramework::TestResult DuctTape::TestFramework::WindowManagerTests::ShutdownTest::Run()  {
    TestResult result;

    // TEST: windowManager == nullptr (must be FALSE)
    if(!windowManager) {
        result = TestResult{"unexpected nullptr - ShutdownTest was not properly initialized"};
        return result;
    }
    // TEST: windowManager == nullptr

    windowManager->Shutdown();

    // TEST: windowManager->IsInitialized() (must be FALSE)
    if(windowManager->IsInitialized()) {
        result = TestResult{"windowManager unexpectedly remained initialized during shutdown"};
    } // TEST: windowManager->IsInitialized()

    // TEST: windowManager->IsShutdown() (must be TRUE)
    else if(!windowManager->IsShutdown()) {
        result = TestResult{"windowManager did not properly shut down"};
    } // TEST: windowManager->IsShutdown()

    // TEST: window.IsOpen() (must be TRUE)
    else if(windowManager->GetMainWindow().IsOpen()) {
        result = TestResult{"window failed to close"};
    } // TEST: window.IsOpen()

    return result;
}

DuctTape::TestFramework::WindowManagerTests::SetResolutionTest::SetResolutionTest(std::string_view name, WindowManager* windowManager):
    Test(name),
    windowManager{windowManager} {

}

DuctTape::TestFramework::TestResult DuctTape::TestFramework::WindowManagerTests::SetResolutionTest::Run() {
    TestResult result;

    // TEST: windowManager == nullptr (must be FALSE)
    if(!windowManager) {
        result = TestResult{"unexpected nullptr - SetResolutionTest was not properly initialized"};
        return result;
    } // TEST: windowManager == nullptr

    // TEST: SetResolution(0,0) (must be FALSE)
    {
        constexpr unsigned int width{0};
        constexpr unsigned int height{0};
        const bool success{windowManager->SetResolution(width, height)};
        if(success) {
            result = TestResult{"illegal resolution - validation was not properly performed"};
            return result;
        } // if(success)
    } // TEST: SetResolution(0,0)

    // TEST: SetResolution(800,600) (must be TRUE)
    {
        constexpr unsigned int width{800};
        constexpr unsigned int height{600};
        const bool success{windowManager->SetResolution(width, height)};
        if(!success) {
            result = TestResult{"failed to properly set resolution to 800x600"};
            return result;
        } // if(!success)
    } // TEST: SetResolution(800,600)

    // TEST: SetResolution(1280,1024) (must be TRUE)
    {
        constexpr unsigned int width{1280};
        constexpr unsigned int height{1024};
        const bool success{windowManager->SetResolution(width, height)};
        if(!success) {
            result = TestResult{"failed to properly set resolution to 1280x1024"};
            return result;
        } // if(!success)
    } // TEST: SetResolution(1280,1024)

    return result;
} // SetResolutionTest::Run()

DuctTape::TestFramework::WindowManagerTests::SetTitleTest::SetTitleTest(std::string_view name, WindowManager* windowManager):
    Test(name),
    windowManager{windowManager} {

}

DuctTape::TestFramework::TestResult DuctTape::TestFramework::WindowManagerTests::SetTitleTest::Run() {
    TestResult result;

    // TEST: windowManager == nullptr (must be FALSE)
    if(!windowManager) {
        result = TestResult{"unexpected nullptr - SetTitleTest was not properly initialized"};
        return result;
    } // TEST: windowManager == nullptr

    // TEST: SetTitle("") (must be TRUE)
    {
        const std::string blankTitle{""};
        const bool success{windowManager->SetTitle(blankTitle)};
        if(!success) {
            result = TestResult{"attempt to set title to \"\" was unsuccessful"};
        } // if(!success)
    } // TEST: SetTitle("") (must be TRUE)

    // TEST: SetTitle("DuctTape Engine") (must be TRUE)
    {
        const std::string goodTitle{"DuctTape Engine"};
        const bool success{windowManager->SetTitle(goodTitle)};
        if(!success) {
            result = TestResult{"attempt to set title to \"DuctTape Engine\" was unsuccessful"};
        } // if(!success)
    } // TEST: SetTitle("DuctTape Engine") (must be TRUE)

    // TEST: SetTitle('*' times MaxTitleLength) (must be FALSE)
    {
        std::string badTitle{""};
        for(unsigned int index = 0; index < WindowManager::MaxTitleLength + 1; ++index) {
            badTitle.append("*");
        } // for each positive integer less than MaxTitleLength
        const bool success{windowManager->SetTitle(badTitle)};
        if(success) {
            result = TestResult{"illegal title - validation was not properly performed"};
        } // if(success)
    } // TEST: SetTitle('*' times MaxTitleLength)

    return result;
}

DuctTape::TestFramework::WindowManagerTests::SetFullscreenTest::SetFullscreenTest(std::string_view name, WindowManager* windowManager):
    TestFramework::Test(name),
    windowManager{windowManager} {

}

DuctTape::TestFramework::TestResult DuctTape::TestFramework::WindowManagerTests::SetFullscreenTest::Run() {
    TestResult result;

    // TEST: windowManager == nullptr (must be FALSE)
    if(!windowManager) {
        result = TestResult{"unexpected nullptr - SetFullscreenTest was not properly initialized"};
        return result;
    } // TEST: windowManager == nullptr

    if(windowManager->initialized) {
        windowManager->Shutdown();
    } // if initialized, shutdown
    windowManager->Init();

    // TEST: windowManager->SetFullscreen(true) (must be TRUE)
    {
        windowManager->SetFullscreen(true);
        if(!windowManager->mainWindow.IsFullscreen()) {
            result = TestResult{"failed to set fullscreen to true"};
        } // if(IsFullscreen(mainWindow))
    }
    // TEST: windowManager->SetFullscreen(true)

    // TEST: windowManager->SetFullscreen(false)
    {
        windowManager->SetFullscreen(false);
        if(windowManager->mainWindow.IsFullscreen()) {
            result = TestResult{"failed to set fullscreen to false"};
        } // if(IsFullscreen(mainWindow))
    }
    // TEST: windowManager->SetFullscreen(false)

    windowManager->Shutdown();

    return result;
}
