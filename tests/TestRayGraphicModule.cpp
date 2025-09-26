/**
 * @file TestRayGraphicModule.cpp
 * @brief GoogleTest for RayGraphicModule DLL functions
 */

#include <gtest/gtest.h>
#include "raylib.cpp" // includes all create/delete functions and RayGraphicModule

// -----------------------------------------------------
// Module creation / deletion
// -----------------------------------------------------
TEST(RayGraphicModuleTest, CreateDeleteModule) {
    IModule* module = createModule();
    ASSERT_NE(module, nullptr);
    deleteModule(module); // should not crash
}

// -----------------------------------------------------
// Window
// -----------------------------------------------------
TEST(RayGraphicModuleTest, CreateDeleteWindow) {
    graphic::IWindow* window = createWindow(800, 600, "Test Window");
    ASSERT_NE(window, nullptr);
    deleteWindow(window);
}

// -----------------------------------------------------
// Camera
// -----------------------------------------------------
TEST(RayGraphicModuleTest, CreateDeleteCamera) {
    graphic::ICamera* camera = createCamera({0, 0, 0});
    ASSERT_NE(camera, nullptr);
    deleteCamera(camera);
}

// -----------------------------------------------------
// Event, Keyboard, Mouse
// -----------------------------------------------------
TEST(RayGraphicModuleTest, CreateDeleteEventKeyboardMouse) {
    graphic::IEvent* event = createEvent();
    ASSERT_NE(event, nullptr);

    graphic::IKeyboard* keyboard = createKeyboard(event);
    ASSERT_NE(keyboard, nullptr);

    graphic::IMouse* mouse = createMouse(event);
    ASSERT_NE(mouse, nullptr);

    deleteMouse(mouse);
    deleteKeyboard(keyboard);
    deleteEvent(event);
}

// -----------------------------------------------------
// Polygon, Sprite, Text, Model
// -----------------------------------------------------
TEST(RayGraphicModuleTest, CreateDeleteGraphics) {
    std::vector<Vector2f> points = {{0,0},{1,0},{0,1}};
    graphic::IPolygon* poly = createPolygon(points);
    ASSERT_NE(poly, nullptr);
    deletePolygon(poly);

    graphic::ISprite* sprite = createSprite("dummy_sprite.png");
    ASSERT_NE(sprite, nullptr);
    deleteSprite(sprite);

    graphic::IText* text = createText("Hello", "Arial");
    ASSERT_NE(text, nullptr);
    deleteText(text);

    graphic::IModel* model = createModel();
    ASSERT_NE(model, nullptr);
    deleteModel(model);
}

// -----------------------------------------------------
// Audio
// -----------------------------------------------------
TEST(RayGraphicModuleTest, CreateDeleteAudio) {
    graphic::ISound* sound = createSound("dummy.wav");
    ASSERT_NE(sound, nullptr);
    deleteSound(sound);

    graphic::IMusic* music = createMusic("dummy.ogg");
    ASSERT_NE(music, nullptr);
    deleteMusic(music);
}

// -----------------------------------------------------
// DLL Info
// -----------------------------------------------------
TEST(RayGraphicModuleTest, GetNameAndType) {
    const char* name = getName();
    const char* type = getType();

    ASSERT_STREQ(name, "raylib");
    ASSERT_STREQ(type, "graphic");
}

// -----------------------------------------------------
// Main entry
// -----------------------------------------------------
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}