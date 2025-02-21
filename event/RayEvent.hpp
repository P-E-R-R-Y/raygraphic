/**
 * @file RayEvent.hpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-29
 * 
 * @addtogroup Raylib
 * @{
 */

#ifndef RAYEVENT_HPP
#define RAYEVENT_HPP

//Interface
#include "IEvent.hpp"

//Raylib
#include <raylib.h>

/**
 * @brief Raylib Event class
 * @section graphic hello
 */
class RayEvent : public graphic::IEvent {
  public:
    friend class RayKeyboard;
    friend class RayMouse;
    friend class RayWindow;

    RayEvent() = default;

    ~RayEvent() = default;

  protected:    //your variables here
};

#endif // RAYEVENT_HPP
