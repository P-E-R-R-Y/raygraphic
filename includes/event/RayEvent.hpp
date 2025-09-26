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

//Raylib (without conflict)
#include "RaylibAliases.hpp"

//Interface
#include "IEvent.hpp"

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
