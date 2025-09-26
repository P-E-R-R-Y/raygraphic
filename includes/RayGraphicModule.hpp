#include "IGraphicModule.hpp"

/**
 * @file IGraphicModule.hpp
 * @author Perry Chouteau (perry.chouteau@outlook.com)
 * @brief
 * @version 0.1
 * @date 11-06-2025
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef RAYGRAPHIC_MODULE_HPP
#define RAYGRAPHIC_MODULE_HPP

#include "window/RayWindow.hpp"
#include "window/RayCamera.hpp"

#include "graphic/RayModel.hpp"
#include "graphic/RayPolygon.hpp"
#include "graphic/RaySprite.hpp"
#include "graphic/RayText.hpp"

#include "event/RayEvent.hpp"
#include "event/RayKeyboard.hpp"
#include "event/RayMouse.hpp"

#include "audio/RayMusic.hpp"
#include "audio/RaySound.hpp"

#include "IGraphicModule.hpp"

class RayGraphicModule : public IGraphicModule {

public:
    RayGraphicModule() = default;
    ~RayGraphicModule() = default;

    /* Window */

    graphic::IWindow *createWindow(int32_t screenWidth, int32_t screenHeight, std::string title) override {
        return new RayWindow(screenWidth, screenHeight, title);
    }
    void deleteWindow(graphic::IWindow *window) override {
        delete window;
    }

    /* 3D */

    graphic::ICamera *createCamera() override {
        return new RayCamera();
    }
    void deleteCamera(graphic::ICamera *camera) override {
        delete camera;
    }
    
    graphic::IModel *createModel() override {
        return new RayModel();
    }
    void deleteModel(graphic::IModel *model) override {
        delete model;
    }

    /* 2D */

    graphic::IPolygon *createPolygon(std::vector<Vector2f> points) override {
        return new RayPolygon(points);
    }
    void deletePolygon(graphic::IPolygon *polygon) override {
        delete polygon;
    }

    graphic::ISprite *createSprite(std::string path) override {
        return new RaySprite(path);
    }
    void deleteSprite(graphic::ISprite *sprite) override {
        delete sprite;
    }

    graphic::IText *createText(std::string text, std::string font) override {
        return new RayText(text, font);
    }
    void deleteText(graphic::IText *text) override {
        delete text;
    }

    /* Event */

    graphic::IEvent *createEvent() override {
        return new RayEvent();
    }
    void deleteEvent(graphic::IEvent *event) override {
        delete event;
    }

    graphic::IKeyboard *createKeyboard(graphic::IEvent *event) override {
        return new RayKeyboard(event);
    }
    void deleteKeyboard(graphic::IKeyboard *keyboard) override {
        delete keyboard;
    }

    graphic::IMouse *createMouse(graphic::IEvent *event) override {
        return new RayMouse(event);
    }
    void deleteMouse(graphic::IMouse *mouse) override {
        delete mouse;
    }

    /* Audio */ 

    graphic::IMusic *createMusic(std::string path) override {
        return new RayMusic(path);
    }
    void deleteMusic(graphic::IMusic *music) override {
        delete music;
    }

    graphic::ISound *createSound(std::string path) override {
        return new RaySound(path);
    }
    void deleteSound(graphic::ISound *sound) override {
        delete sound;
    }

    const std::string getType() const override {
        return "graphic";
    }
    const std::string getName() const override {
        return "raylib";
    }

    void update() override {}
};

#endif /* !IGRAPHIC_MODULE_HPP */