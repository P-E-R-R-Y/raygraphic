/**
 * @file RayKeyboard.hpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-29
 * 
 * @addtogroup Raylib
 * @{
 */

#ifndef RAYKEYBOARD_HPP_
#define RAYKEYBOARD_HPP_

//Raylib (without conflict)
#include "RaylibAliases.hpp"

//Interface
#include "IKeyboard.hpp"

//More
#include <vector>
#include <unordered_map>

class RayKeyboard : public graphic::IKeyboard {

    public:
        RayKeyboard(graphic::IEvent *event) {
        }

        ~RayKeyboard() override = default;

        std::vector<Keys> whichKey() const override {
            std::vector<Keys> keys;
            
            for (const auto& [key, rayKey] : _keys) {
                if (raylib::IsKeyPressed(rayKey)) {
                    keys.push_back(key);
                }
            }
            return keys;
        }

        bool isKeyPressed(Keys key) const override {
            return raylib::IsKeyPressed(_keys.at(key));
        }

        bool isKeyDown(Keys key) const override {
            return raylib::IsKeyDown(_keys.at(key));
        }

        bool isKeyReleased(Keys key) const override {
            return raylib::IsKeyReleased(_keys.at(key));
        }

        bool isKeyUp(Keys key) const override {
            return raylib::IsKeyUp(_keys.at(key));
        }

    private:
        const std::unordered_map<IKeyboard::Keys, int> _keys = {
            //line 0
            {IKeyboard::Keys::KEY_ESCAPE, raylib::KeyboardKey::KEY_ESCAPE},
            {IKeyboard::Keys::KEY_F1, raylib::KeyboardKey::KEY_F1},
            {IKeyboard::Keys::KEY_F2, raylib::KeyboardKey::KEY_F2},
            {IKeyboard::Keys::KEY_F3, raylib::KeyboardKey::KEY_F3},
            {IKeyboard::Keys::KEY_F4, raylib::KeyboardKey::KEY_F4},
            {IKeyboard::Keys::KEY_F5, raylib::KeyboardKey::KEY_F5},
            {IKeyboard::Keys::KEY_F6, raylib::KeyboardKey::KEY_F6},
            {IKeyboard::Keys::KEY_F7, raylib::KeyboardKey::KEY_F7},
            {IKeyboard::Keys::KEY_F8, raylib::KeyboardKey::KEY_F8},
            {IKeyboard::Keys::KEY_F9, raylib::KeyboardKey::KEY_F9},
            {IKeyboard::Keys::KEY_F10, raylib::KeyboardKey::KEY_F10},
            {IKeyboard::Keys::KEY_F11, raylib::KeyboardKey::KEY_F11},
            {IKeyboard::Keys::KEY_F12, raylib::KeyboardKey::KEY_F12},

            //line 1
            {IKeyboard::Keys::KEY_1, raylib::KeyboardKey::KEY_ONE},
            {IKeyboard::Keys::KEY_2, raylib::KeyboardKey::KEY_TWO},
            {IKeyboard::Keys::KEY_3, raylib::KeyboardKey::KEY_THREE},
            {IKeyboard::Keys::KEY_4, raylib::KeyboardKey::KEY_FOUR},
            {IKeyboard::Keys::KEY_5, raylib::KeyboardKey::KEY_FIVE},
            {IKeyboard::Keys::KEY_6, raylib::KeyboardKey::KEY_SIX},
            {IKeyboard::Keys::KEY_7, raylib::KeyboardKey::KEY_SEVEN},
            {IKeyboard::Keys::KEY_8, raylib::KeyboardKey::KEY_EIGHT},
            {IKeyboard::Keys::KEY_9, raylib::KeyboardKey::KEY_NINE},
            {IKeyboard::Keys::KEY_0, raylib::KeyboardKey::KEY_ZERO},
            {IKeyboard::Keys::KEY_MINUS, raylib::KeyboardKey::KEY_MINUS},
            {IKeyboard::Keys::KEY_EQUAL, raylib::KeyboardKey::KEY_EQUAL},
            {IKeyboard::Keys::KEY_BACKSPACE, raylib::KeyboardKey::KEY_BACKSPACE},

            //line 2
            {IKeyboard::Keys::KEY_TAB, raylib::KeyboardKey::KEY_TAB},
            {IKeyboard::Keys::KEY_Q, raylib::KeyboardKey::KEY_Q},
            {IKeyboard::Keys::KEY_W, raylib::KeyboardKey::KEY_W},
            {IKeyboard::Keys::KEY_E, raylib::KeyboardKey::KEY_E},
            {IKeyboard::Keys::KEY_R, raylib::KeyboardKey::KEY_R},
            {IKeyboard::Keys::KEY_T, raylib::KeyboardKey::KEY_T},
            {IKeyboard::Keys::KEY_Y, raylib::KeyboardKey::KEY_Y},
            {IKeyboard::Keys::KEY_U, raylib::KeyboardKey::KEY_U},
            {IKeyboard::Keys::KEY_I, raylib::KeyboardKey::KEY_I},
            {IKeyboard::Keys::KEY_O, raylib::KeyboardKey::KEY_O},
            {IKeyboard::Keys::KEY_P, raylib::KeyboardKey::KEY_P},
            {IKeyboard::Keys::KEY_LEFT_BRACKET, raylib::KeyboardKey::KEY_LEFT_BRACKET},
            {IKeyboard::Keys::KEY_RIGHT_BRACKET, raylib::KeyboardKey::KEY_RIGHT_BRACKET},

            //line 3
            {IKeyboard::Keys::KEY_CAPS_LOCK, raylib::KeyboardKey::KEY_CAPS_LOCK},
            {IKeyboard::Keys::KEY_LEFT_CONTROL, raylib::KeyboardKey::KEY_LEFT_CONTROL},
            {IKeyboard::Keys::KEY_A, raylib::KeyboardKey::KEY_A},
            {IKeyboard::Keys::KEY_S, raylib::KeyboardKey::KEY_S},
            {IKeyboard::Keys::KEY_D, raylib::KeyboardKey::KEY_D},
            {IKeyboard::Keys::KEY_F, raylib::KeyboardKey::KEY_F},
            {IKeyboard::Keys::KEY_G, raylib::KeyboardKey::KEY_G},
            {IKeyboard::Keys::KEY_H, raylib::KeyboardKey::KEY_H},
            {IKeyboard::Keys::KEY_J, raylib::KeyboardKey::KEY_J},
            {IKeyboard::Keys::KEY_K, raylib::KeyboardKey::KEY_K},
            {IKeyboard::Keys::KEY_L, raylib::KeyboardKey::KEY_L},
            {IKeyboard::Keys::KEY_SEMICOLON, raylib::KeyboardKey::KEY_SEMICOLON},
            {IKeyboard::Keys::KEY_APOSTROPHE, raylib::KeyboardKey::KEY_APOSTROPHE},
            {IKeyboard::Keys::BACK_TICK, raylib::KeyboardKey::KEY_LEFT_SUPER},
            {IKeyboard::Keys::KEY_ENTER, raylib::KeyboardKey::KEY_ENTER},
            
            //line 4
            {IKeyboard::Keys::KEY_LEFT_SHIFT, raylib::KeyboardKey::KEY_LEFT_SHIFT},
            {IKeyboard::Keys::KEY_BACKSLASH, raylib::KeyboardKey::KEY_BACKSLASH},
            {IKeyboard::Keys::KEY_Z, raylib::KeyboardKey::KEY_Z},
            {IKeyboard::Keys::KEY_X, raylib::KeyboardKey::KEY_X},
            {IKeyboard::Keys::KEY_C, raylib::KeyboardKey::KEY_C},
            {IKeyboard::Keys::KEY_V, raylib::KeyboardKey::KEY_V},
            {IKeyboard::Keys::KEY_B, raylib::KeyboardKey::KEY_B},
            {IKeyboard::Keys::KEY_N, raylib::KeyboardKey::KEY_N},
            {IKeyboard::Keys::KEY_M, raylib::KeyboardKey::KEY_M},
            {IKeyboard::Keys::KEY_COMMA, raylib::KeyboardKey::KEY_COMMA},
            {IKeyboard::Keys::KEY_DOT, -1},
            {IKeyboard::Keys::KEY_RIGHT_SHIFT, raylib::KeyboardKey::KEY_RIGHT_SHIFT},

            /// Line 5
            {IKeyboard::Keys::KEY_LEFT_ALT, raylib::KeyboardKey::KEY_LEFT_ALT},
            {IKeyboard::Keys::KEY_SPACE, raylib::KeyboardKey::KEY_SPACE},
            {IKeyboard::Keys::KEY_RIGHT_ALT, raylib::KeyboardKey::KEY_RIGHT_ALT},
            {IKeyboard::Keys::KEY_RIGHT_CONTROL, raylib::KeyboardKey::KEY_RIGHT_CONTROL},
    
            /// KEYPAD
            {IKeyboard::Keys::KEY_PAD_0, raylib::KeyboardKey::KEY_KP_0},
            {IKeyboard::Keys::KEY_PAD_1, raylib::KeyboardKey::KEY_KP_1},
            {IKeyboard::Keys::KEY_PAD_2, raylib::KeyboardKey::KEY_KP_2},
            {IKeyboard::Keys::KEY_PAD_3, raylib::KeyboardKey::KEY_KP_3},
            {IKeyboard::Keys::KEY_PAD_4, raylib::KeyboardKey::KEY_KP_4},
            {IKeyboard::Keys::KEY_PAD_5, raylib::KeyboardKey::KEY_KP_5},
            {IKeyboard::Keys::KEY_PAD_6, raylib::KeyboardKey::KEY_KP_6},
            {IKeyboard::Keys::KEY_PAD_7, raylib::KeyboardKey::KEY_KP_7},
            {IKeyboard::Keys::KEY_PAD_8, raylib::KeyboardKey::KEY_KP_8},
            {IKeyboard::Keys::KEY_PAD_9, raylib::KeyboardKey::KEY_KP_9},
            {IKeyboard::Keys::KEY_PAD_MINUS, raylib::KeyboardKey::KEY_KP_SUBTRACT},
            {IKeyboard::Keys::KEY_PAD_PLUS, raylib::KeyboardKey::KEY_KP_ADD},
            {IKeyboard::Keys::KEY_PAD_DOT, raylib::KeyboardKey::KEY_KP_DECIMAL},
            {IKeyboard::Keys::KEY_PAD_ENTER, raylib::KeyboardKey::KEY_KP_ENTER},

            //Arrow
            {IKeyboard::Keys::KEY_UP, raylib::KeyboardKey::KEY_UP},
            {IKeyboard::Keys::KEY_DOWN, raylib::KeyboardKey::KEY_DOWN},
            {IKeyboard::Keys::KEY_LEFT, raylib::KeyboardKey::KEY_LEFT},
            {IKeyboard::Keys::KEY_RIGHT, raylib::KeyboardKey::KEY_RIGHT},
        };
};

#endif /* !RAYKEYBOARD_HPP_ */