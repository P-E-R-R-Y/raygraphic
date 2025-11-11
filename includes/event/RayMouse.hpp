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

//Raylib (without conflict)
#include "RaylibAliases.hpp"

//Interface
#include "IMouse.hpp"

/**
 * @brief Raylib Mouse class
 */
class RayMouse : public graphic::IMouse {

    public:
        RayMouse(graphic::IEvent *event) {
        }

        ~RayMouse() override = default;

        bool isButtonPressed(Buttons key) const override {
            return raylib::IsMouseButtonPressed(key);
        }
        bool isButtonDown(Buttons key) const override {
            return raylib::IsMouseButtonDown(key);
        }
        bool isButtonReleased(Buttons key) const override {
            return raylib::IsMouseButtonReleased(key);
        }
        bool isButtonUp(Buttons key) const override {
            return raylib::IsMouseButtonUp(key);
        }
        
        Vector2f getPosition() const override {
            return {float(raylib::GetMouseX()), float(raylib::GetMouseY())};
        }
        void setPosition(Vector2f position) override {
            raylib::SetMousePosition(int(position.x), int(position.y));
        }

        float GetMouseWheelMove() const override {
            return raylib::GetMouseWheelMove();
        }

    private:
};

#endif /* !RAYMOUSE_HPP_ */