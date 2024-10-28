#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#ifdef _WIN32
    #include <windows.h>
#endif

enum TEST_DISPLAY
{
    ALL,
    FAILURE,
    SUCCESS,
    NONE
};

class Test
{
protected:
    unsigned totalCountTests = 0;
    unsigned failedCountTests = 0;
    const std::string SUCCESS_MESSAGE = "YES";
    const std::string FAILURE_MESSAGE = "NO";
    TEST_DISPLAY display = TEST_DISPLAY::ALL;

    void error(std::string message) 
    {
        #ifdef _WIN32
            HANDLE error_handle = GetStdHandle(STD_ERROR_HANDLE);
            CONSOLE_SCREEN_BUFFER_INFO error_buffer_info;
            GetConsoleScreenBufferInfo(error_handle, &error_buffer_info);

            SetConsoleTextAttribute(error_handle, FOREGROUND_RED);
        #else
            std::cerr << "\033[0;31m";
        #endif

        std::cerr << message;

        #ifdef _WIN32
            SetConsoleTextAttribute(error_handle, error_buffer_info.wAttributes);
        #else
            std::cerr << "\033[0m";
        #endif
    }

    void success(std::string message)
    {
         #ifdef _WIN32
            HANDLE error_handle = GetStdHandle(STD_ERROR_HANDLE);
            CONSOLE_SCREEN_BUFFER_INFO error_buffer_info;
            GetConsoleScreenBufferInfo(error_handle, &error_buffer_info);

            SetConsoleTextAttribute(error_handle, FOREGROUND_GREEN);
        #else
            std::cerr << "\033[0;31m";
        #endif

        std::cerr << message;

        #ifdef _WIN32
            SetConsoleTextAttribute(error_handle, error_buffer_info.wAttributes);
        #else
            std::cerr << "\033[0m";
        #endif
    }

    bool isDisplaySuccess()
    {
        return display == TEST_DISPLAY::ALL || display == TEST_DISPLAY::SUCCESS;
    }

    bool isDisplayFailure()
    {
        return display == TEST_DISPLAY::ALL || display == TEST_DISPLAY::FAILURE;
    }

public:

    #define PRINT_TEST_SOURCE() \
        std::cerr << __FILE__ << ":" << __FUNCTION__ << "::" << __LINE__ << std::endl; \

    #define ASSERT_TRUE(value) \
        {\
            ++totalCountTests; \
            bool isSuccess = typeid(value).hash_code() == typeid(bool).hash_code() && value;\
            bool needDisplay = isDisplaySuccess() && isSuccess || isDisplayFailure() && !isSuccess;\
            \
            if (!isSuccess)\
                ++failedCountTests;\
            \
            if (needDisplay) \
            { \
                PRINT_TEST_SOURCE(); \
                std::cerr << #value << " is true  --- ";\
                if (isSuccess)\
                    success(SUCCESS_MESSAGE);\
                else\
                    error(FAILURE_MESSAGE); \
                std::cerr << std::endl;\
            }\
        }

    #define ASSERT_FALSE(value) \
       {\
            ++totalCountTests; \
            bool isSuccess = typeid(value).hash_code() == typeid(bool).hash_code() && !value;\
            bool needDisplay = isDisplaySuccess() && isSuccess || isDisplayFailure() && !isSuccess;\
            \
            if (!isSuccess)\
                ++failedCountTests;\
            \
            if (needDisplay)\
            {\
                PRINT_TEST_SOURCE(); \
                std::cerr << #value << " is false  --- ";\
                if (isSuccess)\
                    success(SUCCESS_MESSAGE);\
                else\
                    error(FAILURE_MESSAGE); \
                std::cerr << std::endl;\
            }\
       }

    #define ASSERT_THROWS_EXCEPTION(expression, exception) \
        {\
            ++totalCountTests; \
            bool isSuccess = true;\
            \
            try \
            { \
                expression;\
                isSuccess = false;\
                ++failedCountTests; \
            } \
            catch (exception _) \
            {\
                isSuccess = true;\
            }\
            catch (...)\
            {\
                isSuccess = false;\
                ++failedCountTests; \
            }\
            \
            bool needDisplay = isDisplaySuccess() && isSuccess || isDisplayFailure() && !isSuccess;\
            \
            if (needDisplay)\
            {\
                PRINT_TEST_SOURCE(); \
                std::cerr << #expression << " throws " << #exception << " --- "; \
                if (isSuccess)\
                    success(SUCCESS_MESSAGE);\
                else\
                    error(FAILURE_MESSAGE); \
                std::cerr << std::endl;\
            }\
        }

    #define ASSERT_NO_THROWS_EXCEPTION(expression)\
        {\
            ++totalCountTests;\
            bool isSuccess = true;\
            \
            try\
            {\
                expression;\
                isSuccess = true;\
            }\
            catch (...)\
            {\
                isSuccess = false;\
                ++failedCountTests;\
            }\
            \
            bool needDisplay = isDisplaySuccess() && isSuccess || isDisplayFailure() && !isSuccess;\
            \
            if (needDisplay)\
            {\
                PRINT_TEST_SOURCE();\
                std::cerr << #expression << " doesn`t throws exception" << " --- ";\
                if (isSuccess)\
                    success(SUCCESS_MESSAGE);\
                else\
                    error(FAILURE_MESSAGE);\
                std::cerr << std::endl;\
            }\
        }

    #define ASSERT_EQUALS(value1, value2) \
        {\
            ++totalCountTests; \
            bool isSuccess = value1 == value2;\
            bool needDisplay = isDisplaySuccess() && isSuccess || isDisplayFailure() && !isSuccess;\
            \
            if (!isSuccess)\
                ++failedCountTests;\
            \
            if (needDisplay) \
            {\
                PRINT_TEST_SOURCE(); \
                std::cerr << #value1 << " == " << #value2 << " --- "; \
                if (isSuccess)\
                    success(SUCCESS_MESSAGE);\
                else\
                    error(FAILURE_MESSAGE);\
                std::cerr << std::endl;\
            }\
        }

    #define ASSERT_NOT_EQUALS(value1, value2) \
        {\
            ++totalCountTests; \
            bool isSuccess = value1 != value2;\
            bool needDisplay = isDisplaySuccess() && isSuccess || isDisplayFailure() && !isSuccess;\
            \
            if (!isSuccess)\
                ++failedCountTests;\
            \
            if (needDisplay) \
            {\
                PRINT_TEST_SOURCE(); \
                std::cerr << #value1 << " != " << #value2 << " --- "; \
                if (isSuccess)\
                    success(SUCCESS_MESSAGE);\
                else\
                    error(FAILURE_MESSAGE);\
                std::cerr << std::endl;\
            }\
        }

    #define ASSERT_FLOATS_ARE_SAME(float1, float2)\
        {\
            ++totalCountTests;\
            bool isSuccess = std::fabs(float1 - float2) <= std::numeric_limits<float>::epsilon();\
            bool needDisplay = isDisplaySuccess() && isSuccess || isDisplayFailure() && !isSuccess;\
            \
            if (!isSuccess)\
                ++failedCountTests;\
            \
            if (needDisplay)\
            {\
                PRINT_TEST_SOURCE();\
                std::cerr << #float1 << " == " << #float2 << " --- ";\
                if (isSuccess)\
                    success(SUCCESS_MESSAGE);\
                else\
                    error(FAILURE_MESSAGE);\
                std::cerr << std::endl;\
            }\
        }

    #define ASSERT_INSTANCE_OF(instance, type)\
        {\
            ++totalCountTests;\
            bool isSuccess = typeid(instance).hash_code() == typeid(type).hash_code();\
            bool needDisplay = isDisplaySuccess() && isSuccess || isDisplayFailure() && !isSuccess;\
            \
            if (!isSuccess)\
                ++failedCountTests;\
            \
            if (needDisplay)\
            {\
                PRINT_TEST_SOURCE();\
                std::cerr << #instance << " is instance of " << #type << " --- ";\
                if (isSuccess)\
                    success(SUCCESS_MESSAGE);\
                else\
                    error(FAILURE_MESSAGE);\
                std::cerr << std::endl;\
            }\
        }

    unsigned getTotalCountTests()
    {
        return totalCountTests;
    }

    unsigned getFailedCountTests()
    {
        return failedCountTests;
    }

    Test(){}

    virtual void run() {};

    void setDisplay(TEST_DISPLAY display)
    {
        this->display = display;
    }
};