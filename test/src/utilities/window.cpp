//
// Created by dgmuller on 6/13/26.
//
#include <vector>
#include "../../include/utilities/window.hpp"

// WindowInitTest Implementation
WindowInitTest::WindowInitTest(DuctTape::WindowManager& windowManager):
    Test(),
    windowManager{windowManager} {

}

WindowInitTest::~WindowInitTest() {

}

Test::TestID WindowInitTest::GetID() const {
    return TestID::WindowInitTest;
}

TestName WindowInitTest::GetName() const {
    return testName;
}

TestResult WindowInitTest::Run() {
    TestResult result;
    DuctTape::Window& window{windowManager.GetMainWindow()};
    windowManager.Init();
    if(window.IsOpen()) {
        result.passed = true;
    } // if window is open
    else {
        const std::vector<std::string> paramNames{
            "width",
            "height",
            "title",
            "fullscreen"
        };
        std::string details{"Window failed to open (parameters: "};
        int index{0};
        for(const auto& param : paramNames) {
            details += param;
            details += "=";
            if(param.compare("width") == 0) {
                details += std::to_string(window.properties.width);
            } // width
            else if(param.compare("height") == 0) {
                details += std::to_string(window.properties.height);
            } // height
            else if(param.compare("title") == 0) {
                details += '"';
                details += window.properties.title;
                details += '"';
            } // title
            else if(param.compare("fullscreen") == 0) {
                details += std::to_string(window.properties.fullscreen);
            } // fullscreen
            if(index < paramNames.size()) {
                details += ", ";
            } // if this isn't the last parameter
            ++index;
        } // for each paramName
        details += ")";
        result.details = details;
    } // else if window is not open
    return result;
}

// WindowCloseText Implementation

WindowCloseTest::WindowCloseTest(DuctTape::WindowManager& windowManager):
    Test(),
    windowManager{windowManager} {

}

WindowCloseTest::~WindowCloseTest() {

}

Test::TestID WindowCloseTest::GetID() const {
    return TestID::WindowCloseTest;
}

TestName WindowCloseTest::GetName() const {
    return testName;
}

TestResult WindowCloseTest::Run() {
    TestResult result;
    DuctTape::Window& window{windowManager.GetMainWindow()};
    windowManager.Shutdown();
    if(!window.IsOpen()) {
        result.passed = true;
    } // if window is not open
    else {
        result.passed = false;
        const std::vector<std::string> paramNames{
            "width",
            "height",
            "title",
            "fullscreen"
        };
        std::string details{"Window failed to close (parameters: "};
        int index{0};
        for(const auto& param : paramNames) {
            details += param;
            details += "=";
            if(param.compare("width") == 0) {
                details += std::to_string(window.properties.width);
            } // width
            else if(param.compare("height") == 0) {
                details += std::to_string(window.properties.height);
            } // height
            else if(param.compare("title") == 0) {
                details += '"';
                details += window.properties.title;
                details += '"';
            } // title
            else if(param.compare("fullscreen") == 0) {
                details += std::to_string(window.properties.fullscreen);
            } // fullscreen
            if(index < paramNames.size()) {
                details += ", ";
            } // if this isn't the last parameter
            ++index;
        } // for each paramName
        details += ")";
        result.details = details;
    } // else window is open
    return result;
}
