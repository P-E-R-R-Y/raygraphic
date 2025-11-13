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

    //event
    graphic::IEvent* event = gm->createEvent();
    ASSERT_NE(event, nullptr);
    window->linkEvent(event);

    graphic::IMouse* mouse = gm->createMouse(event);
    ASSERT_NE(mouse, nullptr);
    graphic::IKeyboard* keyboard = gm->createKeyboard(event);
    ASSERT_NE(keyboard, nullptr);

    //graphic
    graphic::ISprite* sprite = gm->createSprite("../assets/image.png");
    ASSERT_NE(sprite, nullptr);
    Vector2f size = sprite->getSize();
    sprite->setSize({size.x / 2, size.y / 2});

    graphic::IPolygon* polygon = gm->createPolygon(std::vector<Vector2f>{{0, 100}, {100, 0}, {200, 100}, {100, 200}});
    ASSERT_NE(polygon, nullptr);
    polygon->setPosition({220, 140});
    polygon->setColor({255, 255, 255, 255});
    
    graphic::IText* text = gm->createText("Press Z to play sound\nRight click to rotate model\n", "../assets/font.ttf");
    ASSERT_NE(text, nullptr);
    text->setPosition({10, 430});
    
    //Sound
    graphic::ISound* sound = gm->createSound("../assets/step.wav");
    ASSERT_NE(sound, nullptr);
    sound->setVolume(10);
    
    graphic::IMusic* music = gm->createMusic("../assets/ambience.wav");
    ASSERT_NE(music, nullptr);
    music->setVolume(2);
    music->setTime(100);
    music->play();


    graphic::ICamera* camera = gm->createCamera({50.f, 50.f, 50.f}, {0.f, 0.f, 0.f}, 45);
    ASSERT_NE(camera, nullptr);

    graphic::IModel* model = gm->createModel("../assets/fox.glb");
    ASSERT_NE(model, nullptr);
    model->setSize(model->getSize() / 4);
    model->setTexture("../assets/fox2.png");   
    model->setAnimations("../assets/fox.glb");
    model->setPosition({-25, +10, -10});
    model->setAnimation(1);

    auto endTime = std::chrono::steady_clock::now() + std::chrono::seconds(10);
    auto lastUpdate = std::chrono::steady_clock::now();   
    const int targetFPS = 30;
    const std::chrono::milliseconds frameInterval(1000 / targetFPS); 

    while (window->isOpen()) {
        //event condition
        while (window->pollEvent()) {
            window->eventClose();
            if (mouse->isButtonDown(graphic::IMouse::BUTTON_RIGHT)) {
                std::cout << "right drag" << std::endl; 
                model->setRotation({0, model->getRotation().y + 0.01, 0});
            }
            if (mouse->isButtonPressed(graphic::IMouse::BUTTON_LEFT)) {
                std::cout << "left click" << std::endl;
                sprite->setRotation({sprite->getRotation() - 15});
            }
            if (keyboard->isKeyPressed(graphic::IKeyboard::KEY_Z)) {
                std::cout << "forward" << std::endl;
                sound->play();
            }
        }
        //time condition        
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        if (now > endTime) {
            window->close();
        }

        if (now - lastUpdate > frameInterval) {
            lastUpdate = now;

            // 👇 Do your update here
            model->updateAnimation();
        }

        //2D+
        window->beginDraw();
        window->drawPoly(polygon);
        window->drawText(text);
        window->drawSprite(sprite);

        //3D
        window->beginMode3(camera);
        window->drawModel(model);
        window->endMode3();


        window->endDraw();

        //music
        music->update();
    }
    window->endAudio();

    gm->deleteWindow(window);


    deleteFn(mod);
}