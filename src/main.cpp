//
// Created by dgmuller on 6/28/26.
//
#include <iostream>
#include <strings.h>

#include "../include/core/engine.hpp"

int main() {
    DuctTape::Engine engine;

    constexpr unsigned int numTestTargets{3};

    auto engineTests{engine.GetTestSequence()};
    auto windowMgrTests{engine.windowManager.GetTestSequence()};
    auto windowTests{engine.windowManager.GetMainWindow().GetTestSequence()};

    const std::array<DuctTape::TestFramework::TestTarget*, numTestTargets> targets{
        &engine,
        &engine.windowManager,
        &engine.windowManager.mainWindow,
    };

    const std::array<DuctTape::TestFramework::TestSequence*, numTestTargets> testSequences{
        engineTests,
        windowMgrTests,
        windowTests
    };

    std::cout << "*** STARTING DUCT TAPE ENGINE TESTS ***" << std::endl << std::endl;

    bool fail{false};
    unsigned int index{0};
    for(const auto target: targets) {
        std::cout << "Running tests for target \"";
        std::cout << target->GetName();
        std::cout << + "\":" << std::endl;
        DuctTape::TestFramework::TestSequence* sequence{testSequences.at(index++)};
        const auto results{sequence->Run()};
        for(int resultIndex = 0; resultIndex < results.size(); ++resultIndex) {
            std::cout << "Test #";
            std::cout << std::to_string(resultIndex);
            std::cout << " (";
            std::cout << sequence->tests.at(resultIndex)->GetName();
            std::cout<<  "): ";
            const auto& result{results[resultIndex]};
            if(result.passed) {
                std::cout << "Passed." << std::endl;
            } // if passed
            else {
                std::cout << "Failed!" << std::endl;
                std::cout << "Details: " << result.details << std::endl;
                fail = true;
                break;
            } // else failed
        } // for each result
        if(fail) {
            break;
        } // stop when the first test fails
        if(target == &engine) {
            engine.Init();
        } // if we just finished testing the engine, initialize it
        std::cout << std::endl;
    } // for each target

    if(!fail) {
        std::cout << "*** DUCT TAPE ENGINE TESTS COMPLETED - ALL TESTS PASSED! ***" << std::endl << std::endl;
    }

    return 0;
}