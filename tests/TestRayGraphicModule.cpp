#include <gtest/gtest.h>
#include <dlfcn.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>

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
    ASSERT_NE(window, nullptr);
    window->beginAudio();

    graphic::IEvent* event = gm->createEvent();
    ASSERT_NE(event, nullptr);
    graphic::IMouse* mouse = gm->createMouse(event);
    ASSERT_NE(mouse, nullptr);
    graphic::IKeyboard* keyboard = gm->createKeyboard(event);
    ASSERT_NE(keyboard, nullptr);

    graphic::ISprite* sprite = gm->createSprite("../assets/image.png");
    Vector2f size = sprite->getSize();
    sprite->setSize({size.x / 2, size.y / 2});
    ASSERT_NE(sprite, nullptr);
    graphic::IPolygon* polygon = gm->createPolygon(std::vector<Vector2f>{{0, 100}, {100, 0}, {200, 100}, {100, 200}});
    ASSERT_NE(polygon, nullptr);
    polygon->setPosition({220, 140});
    polygon->setColor({255, 255, 255, 255});
    graphic::IText* text = gm->createText("Welcome", "../assets/font.ttf");
    text->setPosition({220, 140});
    ASSERT_NE(text, nullptr);

    //Sound
    graphic::ISound* sound = gm->createSound("../assets/step.wav");
    ASSERT_NE(sound, nullptr);
    sound->setVolume(10);
    graphic::IMusic* music = gm->createMusic("../assets/ambience.wav");
    ASSERT_NE(music, nullptr);
    music->setVolume(2);
    music->setTime(100);
    graphic::ICamera* camera = gm->createCamera();
    ASSERT_NE(camera, nullptr);
    graphic::IModel* model = gm->createModel();
    ASSERT_NE(model, nullptr);

//    std::cout << std::filesystem::current_path() << std::endl;
//    graphic::ISprite* sprite = gm->createSprite("../assets/image.png");
//    graphic::IText* text = gm->createText("bonjour", "./assets/font.");
    auto endTime = std::chrono::steady_clock::now() + std::chrono::seconds(1);

    music->play();

    window->linkEvent(event);
    while (window->isOpen()) {
        while (window->pollEvent()) {
            window->eventClose();
            if (mouse->isButtonPressed(graphic::IMouse::BUTTON_LEFT)) {
                std::cout << "clicked" << std::endl; 
            }
            if (keyboard->isKeyPressed(graphic::IKeyboard::KEY_Z)) {
                std::cout << "forward" << std::endl;
                sound->play();
            }
        }
        if (std::chrono::steady_clock::now() > endTime) {
            window->close();
        }

        window->beginDraw();
        window->drawPoly(polygon);
        window->drawText(text);
        window->drawSprite(sprite);
        // ... your drawing code ...
        window->endDraw();
        music->update();
    }
        window->endAudio();

    gm->deleteWindow(window);


    deleteFn(mod);
}