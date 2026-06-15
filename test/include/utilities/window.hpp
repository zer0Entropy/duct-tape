//
// Created by dgmuller on 6/13/26.
//

#ifndef DT_TEST_WINDOW_HPP
#define DT_TEST_WINDOW_HPP

#include "../../../include/utilities/window.hpp"
#include "../test.hpp"

struct WindowInitTest final: Test {
    WindowInitTest() = delete;
    explicit WindowInitTest(DuctTape::WindowManager& windowManager);
    ~WindowInitTest() override;
    TestID GetID() const override;
    TestName GetName() const override;
    TestResult Run() override;
private:
    DuctTape::WindowManager& windowManager;
    static constexpr std::string testName = "WindowInitTest";
};

struct WindowCloseTest final: Test {
    WindowCloseTest() = delete;
    explicit WindowCloseTest(DuctTape::WindowManager& windowManager);
    ~WindowCloseTest() override;
    TestID GetID() const override;
    TestName GetName() const override;
    TestResult Run() override;
private:
    DuctTape::WindowManager& windowManager;
    static constexpr std::string testName = "WindowCloseTest";
};

struct WindowManagerTests {
    WindowInitTest initTest;
    WindowCloseTest closeTest;
    std::vector<TestResult> RunAll();
};

#endif //DT_TEST_WINDOW_HPP
