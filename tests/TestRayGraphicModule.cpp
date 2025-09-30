#include <gtest/gtest.h>
#include <dlfcn.h>
#include <iostream>
#include <chrono>
#include <thread>

#include "IGraphicModule.hpp"

// Function pointer types
using CreateModuleFn = IModule* (*)();
using DeleteModuleFn = void (*)(IModule*);

class RaylibFixture : public ::testing::Test {
protected:
    static void* handle;
    static CreateModuleFn createFn;
    static DeleteModuleFn deleteFn;

    static void SetUpTestSuite() {

#if defined(__APPLE__)
        const char* libPath = "libraygraphic.dylib";
#elif defined(__linux__)
        const char* libPath = "./libraygraphic.so";
#else
        GTEST_FAIL() << "Unsupported platform";
#endif

        handle = dlopen(libPath, RTLD_LAZY);
        ASSERT_NE(handle, nullptr) << "dlopen failed: " << dlerror();

        createFn = reinterpret_cast<CreateModuleFn>(dlsym(handle, "createModule"));
        ASSERT_NE(createFn, nullptr) << "dlsym(createModule) failed: " << dlerror();

        deleteFn = reinterpret_cast<DeleteModuleFn>(dlsym(handle, "deleteModule"));
        ASSERT_NE(deleteFn, nullptr) << "dlsym(deleteModule) failed: " << dlerror();
    }

    static void TearDownTestSuite() {
        if (handle) dlclose(handle);
        handle = nullptr;
    }
};

// Static members
void* RaylibFixture::handle = nullptr;
CreateModuleFn RaylibFixture::createFn = nullptr;
DeleteModuleFn RaylibFixture::deleteFn = nullptr;

// ------------------- TESTS -------------------

// Test1: Check library loaded
TEST_F(RaylibFixture, LoadLibrary) {
    ASSERT_NE(handle, nullptr);
    ASSERT_NE(createFn, nullptr);
    ASSERT_NE(deleteFn, nullptr);
}

// Test2: Retrieve module
TEST_F(RaylibFixture, RetrieveModule) {
    IModule* mod = createFn();
    ASSERT_NE(mod, nullptr);
    deleteFn(mod);
}

// Test3: Cast to IGraphicModule and check basic functions
TEST_F(RaylibFixture, GraphicModuleBasic) {
    IModule* mod = createFn();
    ASSERT_NE(mod, nullptr);

    IGraphicModule* gm = dynamic_cast<IGraphicModule*>(mod);
    ASSERT_NE(gm, nullptr);

    std::string name = gm->getName();
    std::string type = gm->getType();

    EXPECT_FALSE(name.empty());
    EXPECT_FALSE(type.empty());

    deleteFn(mod);
}

// Test4: Create and delete window
TEST_F(RaylibFixture, WindowCreation) {
    IModule* mod = createFn();
    IGraphicModule* gm = dynamic_cast<IGraphicModule*>(mod);
    ASSERT_NE(gm, nullptr);

    graphic::IWindow* window = gm->createWindow(640, 480, "Test Window");
    ASSERT_NE(window, nullptr);

    gm->deleteWindow(window);
    deleteFn(mod);
}

// Test5: Integration placeholder (your own logic)
TEST_F(RaylibFixture, IntegrationRun) {
    IModule* mod = createFn();
    IGraphicModule* gm = dynamic_cast<IGraphicModule*>(mod);
    ASSERT_NE(gm, nullptr);

    // ... your more complex sequence here ...
    graphic::IWindow* window = gm->createWindow(640, 480, "Test Window");
    graphic::IEvent* event = gm->createEvent();
    ASSERT_NE(window, nullptr);
    auto endTime = std::chrono::steady_clock::now() + std::chrono::seconds(1);

    window->linkEvent(event);
    while (window->isOpen()) {
        while (window->pollEvent()) {
            window->eventClose();
        }
        if (std::chrono::steady_clock::now() > endTime) {
            window->close();
        }

        window->beginDraw();
        // ... your drawing code ...
        window->endDraw();
    }

    gm->deleteWindow(window);


    deleteFn(mod);
}