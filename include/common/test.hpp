//
// Created by dgmuller on 6/21/26.
//

#ifndef DUCT_TAPE_TEST_HPP
#define DUCT_TAPE_TEST_HPP

#include <string>
#include <vector>

namespace DuctTape::TestFramework {
    struct TestResult {
        bool passed;
        std::string details;

        TestResult(): passed{true}, details {""} {}

        explicit TestResult(std::string_view details): passed{false}, details{details} {}

        bool operator==(const TestResult& other) const {
            bool isEqual{false};
            if(this->passed == other.passed
            && this->details.compare(other.details) == 0) {
                isEqual = true;
            } // if both 'passed' flag and details are identical
            return isEqual;
        }
    };

    struct Test {
        std::string name;

        Test() = delete;
        explicit Test(std::string_view name): name{name} {}
        Test(const Test& copy): name{copy.name} {}
        virtual ~Test() = 0;

        std::string_view GetName() const {return name;}

        virtual TestResult Run() = 0;
    };

    struct TestSequence {
        std::vector<Test*> tests;

        TestSequence() = default;
        explicit TestSequence(const std::vector<Test*>& tests): tests{tests} {}
        virtual ~TestSequence() = 0;

        std::vector<TestResult> Run() const {
            std::vector<TestResult> results;
            for(const auto& test: tests) {
                TestResult result{test->Run()};
                results.push_back(result);
            } // for each test in tests
            return results;
        }
    };

    struct TestTarget {
        std::string name;

        TestTarget() = delete;
        explicit TestTarget(std::string_view name): name{name} {}
        virtual ~TestTarget() = default;

        std::string_view GetName() const {return name;}

        virtual TestSequence* GetTestSequence() = 0;
    };
/*
    struct CanRunTests {
        std::string name;

        CanRunTests() = delete;
        CanRunTests(std::string_view name, const std::vector<Test*>& tests):
            name{name},
            testList{tests} {}
        virtual ~CanRunTests();

        std::string_view GetName() const {return name;}

        std::vector<TestResult> RunAllTests() const {
            std::vector<TestResult> results;
            for(const auto& test: testList.tests) {
                TestResult result{test->Run()};
                results.push_back(result);
            }
            return results;
        }
    protected:
        TestSequence testList;
    };
    */

}

#endif //DUCT_TAPE_TEST_HPP
