/**
 * @file RayMouse.hpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-29
 * 
 * @addtogroup Raylib
 * @{
 */

#ifndef RAYMOUSE_HPP_
#define RAYMOUSE_HPP_

//Interface
#include "IMouse.hpp"
#include "RayEvent.hpp"

//Raylib
#include <raylib.h>

/**
 * @brief Raylib Mouse class
 */
class RayMouse : public graphic::IMouse {

    public:
        RayMouse(graphic::IEvent *event) {
        }

        ~RayMouse() {
        }

        bool isButtonPressed(Buttons key) const override {
            return IsMouseButtonPressed(key);
        }
        bool isButtonDown(Buttons key) const override {
            return IsMouseButtonDown(key);
        }
        bool isButtonReleased(Buttons key) const override {
            return IsMouseButtonReleased(key);
        }
        bool isButtonUp(Buttons key) const override {
            return IsMouseButtonUp(key);
        }
        
        __v2f_t getPosition() const override {
            return {float(GetMouseX()), float(GetMouseY())};
        }
        void setPosition(__v2f_t position) override {
            SetMousePosition(int(position.x), int(position.y));
        }

        float GetMouseWheelMove() const override {
            return GetMouseWheelMove();
        }

        void update() override {};

    private:
};

#endif /* !RAYMOUSE_HPP_ */