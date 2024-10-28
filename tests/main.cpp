#include "TestManager.h"
#include "json/JsonItemTest.h"
#include "json/JsonTest.h"
#include <iostream>

int main(int argc, char** argv)
{
	TestManager* testManager = new TestManager();

	testManager->add(new JsonItemTest);
	testManager->add(new JsonTest);

	testManager->run();

	delete testManager;
    return EXIT_SUCCESS;
}


