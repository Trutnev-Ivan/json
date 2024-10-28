#pragma once
#include "Test.h"
#include <vector>

class TestManager
{
protected:
    std::vector<Test*> tests;
public:
    TestManager()
    {}

    ~TestManager()
    {
        for (Test* test: tests)
        {
            delete test;
        }
    }

    void add(Test* test)
    {
        tests.push_back(test);
    }

    void run(TEST_DISPLAY display = TEST_DISPLAY::ALL)
    {
        unsigned totalTests = 0;
        unsigned failedTests = 0;

        for (Test* test: tests)
        {
            test->setDisplay(display);
            test->run();
            totalTests += test->getTotalCountTests();
            failedTests += test->getFailedCountTests();
        }

        std::cerr << std::endl << "Total tests: " << totalTests;
        std::cerr << std::endl << "Failed tests: " << failedTests << std::endl;
    }
};