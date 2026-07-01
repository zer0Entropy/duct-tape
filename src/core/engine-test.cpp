//
// Created by dgmuller on 6/21/26.
//

#include "../../include/core/engine-test.hpp"
#include "../../include/core/engine.hpp"

DuctTape::TestFramework::EngineTests::EngineTests(DuctTape::Engine* engine):
    DuctTape::TestFramework::TestSequence(),
    engine{engine},
    initTest{std::make_unique<InitTest>(TestNames[0], engine)},
    shutdownTest{std::make_unique<ShutdownTest>(TestNames[1], engine)} {
        tests.push_back(initTest.get());
        tests.push_back(shutdownTest.get());
}

DuctTape::TestFramework::EngineTests::InitTest::InitTest(std::string_view name, DuctTape::Engine* engine):
    DuctTape::TestFramework::Test(name),
    engine{engine} {}

DuctTape::TestFramework::TestResult DuctTape::TestFramework::EngineTests::InitTest::Run() {
    TestResult result;

    // TEST: engine == nullptr (must equal FALSE)
    if(!engine) {
        result = TestResult{"unexpected nullptr, InitTest was not properly initialized"};
        return result;
    } // TEST: engine == nullptr

    engine->Init();

    // TEST: engine->IsInitialized() (must be TRUE)
    if(!engine->IsInitialized()) {
        result = TestResult{"engine was not properly initialized"};
    } // TEST: engine->IsInitialized()

    // TEST: engine->running (must be TRUE)
    else if(!engine->running) {
        result = TestResult{"engine failed to start"};
    } // TEST: engine->running

    return result;
}

DuctTape::TestFramework::EngineTests::ShutdownTest::ShutdownTest(std::string_view name, DuctTape::Engine* engine):
    DuctTape::TestFramework::Test(name),
    engine{engine} {}

DuctTape::TestFramework::TestResult DuctTape::TestFramework::EngineTests::ShutdownTest::Run() {
    TestResult result;

    // TEST: engine == nullptr (must equal FALSE)
    if(!engine) {
        result = TestResult{"unexpected nullptr, ShutdownTest was not properly initialized"};
        return result;
    } // TEST: engine == nullptr

    engine->Shutdown();

    // TEST: windowManager.IsInitialized() (must be FALSE)
    if(engine->windowManager.IsInitialized()) {
        result = TestResult{"windowManager was not properly shut down"};
    } // TEST: windowManager.IsInitialized()

    // TEST: engine->IsInitialized() (must be FALSE)
    else if(engine->IsInitialized()) {
        result = TestResult{"engine was not properly shut down"};
    } // TEST: engine->IsInitialized()

    // TEST: engine->running (must be FALSE)
    else if(engine->running) {
        result = TestResult{"engine failed to stop running"};
    } // TEST: engine->running

    return result;
}