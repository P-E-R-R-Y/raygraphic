/**
 * @file raylib.cpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief graphic shared library for raylib implementation
 * @version 0.1
 * @date 2025-01-27
 * 
 * @addtogroup graphic
 * @{
 * @addtogroup Raylib
 * @{
 */


#ifndef RAYLIB_CPP_
#define RAYLIB_CPP_

//Raylib
#include "window/RayWindow.hpp"

#include "graphic/RaySprite.hpp"
#include "graphic/RayPolygon.hpp"
#include "graphic/RayText.hpp"

#include "graphic/RayModel.hpp"
#include "window/RayCamera.hpp"

#include "event/RayKeyboard.hpp"
#include "event/RayMouse.hpp"
#include "event/RayEvent.hpp"

#include "audio/RaySound.hpp"
#include "audio/RayMusic.hpp"

/**
 * @brief create a window
 * 
 * @param screenWidth
 * @param screenHeight
 * @param title
 * @return graphic::IWindow*
 */
extern "C" graphic::IWindow *createWindow(__int32_t screenWidth, __int32_t screenHeight, std::string title) {
    return new RayWindow(screenWidth, screenHeight, std::string("Raylib " + title));
}

/**
 * @brief delete a window
 * 
 * @param window
 */
extern "C" void deleteWindow(graphic::IWindow *window) {
    delete window;
}

/**
 * @brief create a camera
 * 
 * @param position
 * @return graphic::ICamera*
 */
extern "C" graphic::ICamera *createCamera(__v3f_t position) {
    return new RayCamera();
}

/**
 * @brief delete a camera
 * 
 * @param camera
 */
extern "C" void deleteCamera(graphic::ICamera *camera) {
    delete camera;
}

///Event

/**
 * @brief create an event
 * 
 * @return graphic::IEvent*
 */
extern "C" graphic::IEvent *createEvent() {
    return new RayEvent();
}

/**
 * @brief delete an event
 * 
 * @param event
 */
extern "C" void deleteEvent(graphic::IEvent *event) {
    delete event;
}

/**
 * @brief create a keyboard
 * 
 * @param event
 * @return graphic::IKeyboard*
 */
extern "C" graphic::IKeyboard *createKeyboard(graphic::IEvent *event) {
    return new RayKeyboard(event);
}

/**
 * @brief delete a keyboard
 * 
 * @param keyboard
 */
extern "C" void deleteKeyboard(graphic::IKeyboard *keyboard) {
    delete keyboard;
}

/**
 * @brief create a mouse
 * 
 * @param event
 * @return graphic::IMouse*
 */
extern "C" graphic::IMouse *createMouse(graphic::IEvent *event) {
    return new RayMouse(event);
}

/**
 * @brief delete a mouse
 * 
 * @param mouse
 */
extern "C" void deleteMouse(graphic::IMouse *mouse) {
    delete mouse;
}

///Graphics

/**
 * @brief create a polygon
 * 
 * @param points
 * @return graphic::IPolygon*
 */
extern "C" graphic::IPolygon *createPolygon(std::vector<__v2f_t> points) {
    return new RayPolygon(points);
}

/**
 * @brief delete a polygon
 * 
 * @param polygon
 */
extern "C" void deletePolygon(graphic::IPolygon *polygon) {
    delete polygon;
}

/**
 * @brief create a sprite
 * 
 * @param sprite
 * @return graphic::ISprite*
 */
extern "C" graphic::ISprite *createSprite(std::string sprite) {
    return new RaySprite(sprite);
}

/**
 * @brief delete a sprite
 * 
 * @param sprite
 */
extern "C" void deleteSprite(graphic::ISprite *sprite) {
    delete sprite;
}

/**
 * @brief create a text
 * 
 * @param text
 * @return graphic::IText*
 */
extern "C" graphic::IText *createText(std::string text, std::string font) {
    return new RayText(text, font);
}

/**
 * @brief delete a text
 * 
 * @param text
 */
extern "C" void deleteText(graphic::IText *text) {
    delete text;
}

/**
 * @brief create a model
 * 
 * @return graphic::IModel*
 */
extern "C" graphic::IModel *createModel() {
    return new RayModel();
}

/**
 * @brief delete a model
 * 
 * @param model
 */
extern "C" void deleteModel(graphic::IModel *model) {
    delete model;
}

///Audio

/**
 * @brief create a sound
 * 
 * @param sound
 * @return graphic::ISound*
 */
extern "C" graphic::ISound *createSound(std::string sound) {
    return new RaySound(sound);
}

/**
 * @brief delete a sound
 * 
 * @param sound
 */
extern "C" void deleteSound(graphic::ISound *sound) {
    delete sound;
}

/**
 * @brief create a music
 * 
 * @param music
 * @return graphic::IMusic*
 */
extern "C" graphic::IMusic *createMusic(std::string music) {
    return new RayMusic(music);
}

/**
 * @brief delete a music
 * 
 * @param music
 */
extern "C" void deleteMusic(graphic::IMusic *music) {
    delete music;
}

/**
 * @brief get the name of the library
 * 
 * @return const char*
 */
extern "C" const char *getName() {
    return "raylib\0";
}

/**
 * @brief get the type of the library
 * 
 * @return const char*
 */
extern "C" const char *getType() {
    return "graphic\0";
}


#endif /* !RAYLIB_CPP_ */