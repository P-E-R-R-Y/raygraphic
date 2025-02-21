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

//Interface
#include "IKeyboard.hpp"

//Raylib
#include <raylib.h>

//More
#include <vector>
#include <unordered_map>

class RayKeyboard : public graphic::IKeyboard {

    public:
        RayKeyboard(graphic::IEvent *event) {
        }

        ~RayKeyboard() {
        }

        std::vector<Keys> whichKey() const override {
            std::vector<Keys> keys;
            
            return keys;
        }

        bool isKeyPressed(Keys key) const override {
            return IsKeyPressed(_keys.at(key));
        }

        bool isKeyDown(Keys key) const override {
            return IsKeyDown(_keys.at(key));
        }

        bool isKeyReleased(Keys key) const override {
            return IsKeyReleased(_keys.at(key));
        }

        bool isKeyUp(Keys key) const override {
            return IsKeyUp(_keys.at(key));
        }

        void update() override {};

    private:
        const std::unordered_map<IKeyboard::Keys, int> _keys = {
            //line 0
            {IKeyboard::Keys::KEY_ESCAPE, KeyboardKey::KEY_ESCAPE},
            {IKeyboard::Keys::KEY_F1, KeyboardKey::KEY_F1},
            {IKeyboard::Keys::KEY_F2, KeyboardKey::KEY_F2},
            {IKeyboard::Keys::KEY_F3, KeyboardKey::KEY_F3},
            {IKeyboard::Keys::KEY_F4, KeyboardKey::KEY_F4},
            {IKeyboard::Keys::KEY_F5, KeyboardKey::KEY_F5},
            {IKeyboard::Keys::KEY_F6, KeyboardKey::KEY_F6},
            {IKeyboard::Keys::KEY_F7, KeyboardKey::KEY_F7},
            {IKeyboard::Keys::KEY_F8, KeyboardKey::KEY_F8},
            {IKeyboard::Keys::KEY_F9, KeyboardKey::KEY_F9},
            {IKeyboard::Keys::KEY_F10, KeyboardKey::KEY_F10},
            {IKeyboard::Keys::KEY_F11, KeyboardKey::KEY_F11},
            {IKeyboard::Keys::KEY_F12, KeyboardKey::KEY_F12},

            //line 1
            {IKeyboard::Keys::KEY_1, KeyboardKey::KEY_ONE},
            {IKeyboard::Keys::KEY_2, KeyboardKey::KEY_TWO},
            {IKeyboard::Keys::KEY_3, KeyboardKey::KEY_THREE},
            {IKeyboard::Keys::KEY_4, KeyboardKey::KEY_FOUR},
            {IKeyboard::Keys::KEY_5, KeyboardKey::KEY_FIVE},
            {IKeyboard::Keys::KEY_6, KeyboardKey::KEY_SIX},
            {IKeyboard::Keys::KEY_7, KeyboardKey::KEY_SEVEN},
            {IKeyboard::Keys::KEY_8, KeyboardKey::KEY_EIGHT},
            {IKeyboard::Keys::KEY_9, KeyboardKey::KEY_NINE},
            {IKeyboard::Keys::KEY_0, KeyboardKey::KEY_ZERO},
            {IKeyboard::Keys::KEY_MINUS, KeyboardKey::KEY_MINUS},
            {IKeyboard::Keys::KEY_EQUAL, KeyboardKey::KEY_EQUAL},
            {IKeyboard::Keys::KEY_BACKSPACE, KeyboardKey::KEY_BACKSPACE},

            //line 2
            {IKeyboard::Keys::KEY_TAB, KeyboardKey::KEY_TAB},
            {IKeyboard::Keys::KEY_Q, KeyboardKey::KEY_Q},
            {IKeyboard::Keys::KEY_W, KeyboardKey::KEY_W},
            {IKeyboard::Keys::KEY_E, KeyboardKey::KEY_E},
            {IKeyboard::Keys::KEY_R, KeyboardKey::KEY_R},
            {IKeyboard::Keys::KEY_T, KeyboardKey::KEY_T},
            {IKeyboard::Keys::KEY_Y, KeyboardKey::KEY_Y},
            {IKeyboard::Keys::KEY_U, KeyboardKey::KEY_U},
            {IKeyboard::Keys::KEY_I, KeyboardKey::KEY_I},
            {IKeyboard::Keys::KEY_O, KeyboardKey::KEY_O},
            {IKeyboard::Keys::KEY_P, KeyboardKey::KEY_P},
            {IKeyboard::Keys::KEY_LEFT_BRACKET, KeyboardKey::KEY_LEFT_BRACKET},
            {IKeyboard::Keys::KEY_RIGHT_BRACKET, KeyboardKey::KEY_RIGHT_BRACKET},

            //line 3
            {IKeyboard::Keys::KEY_CAPS_LOCK, KeyboardKey::KEY_CAPS_LOCK},
            {IKeyboard::Keys::KEY_LEFT_CONTROL, KeyboardKey::KEY_LEFT_CONTROL},
            {IKeyboard::Keys::KEY_A, KeyboardKey::KEY_A},
            {IKeyboard::Keys::KEY_S, KeyboardKey::KEY_S},
            {IKeyboard::Keys::KEY_D, KeyboardKey::KEY_D},
            {IKeyboard::Keys::KEY_F, KeyboardKey::KEY_F},
            {IKeyboard::Keys::KEY_G, KeyboardKey::KEY_G},
            {IKeyboard::Keys::KEY_H, KeyboardKey::KEY_H},
            {IKeyboard::Keys::KEY_J, KeyboardKey::KEY_J},
            {IKeyboard::Keys::KEY_K, KeyboardKey::KEY_K},
            {IKeyboard::Keys::KEY_L, KeyboardKey::KEY_L},
            {IKeyboard::Keys::KEY_SEMICOLON, KeyboardKey::KEY_SEMICOLON},
            {IKeyboard::Keys::KEY_APOSTROPHE, KeyboardKey::KEY_APOSTROPHE},
            {IKeyboard::Keys::BACK_TICK, KeyboardKey::KEY_LEFT_SUPER},
            {IKeyboard::Keys::KEY_ENTER, KeyboardKey::KEY_ENTER},
            
            //line 4
            {IKeyboard::Keys::KEY_LEFT_SHIFT, KeyboardKey::KEY_LEFT_SHIFT},
            {IKeyboard::Keys::KEY_BACKSLASH, KeyboardKey::KEY_BACKSLASH},
            {IKeyboard::Keys::KEY_Z, KeyboardKey::KEY_Z},
            {IKeyboard::Keys::KEY_X, KeyboardKey::KEY_X},
            {IKeyboard::Keys::KEY_C, KeyboardKey::KEY_C},
            {IKeyboard::Keys::KEY_V, KeyboardKey::KEY_V},
            {IKeyboard::Keys::KEY_B, KeyboardKey::KEY_B},
            {IKeyboard::Keys::KEY_N, KeyboardKey::KEY_N},
            {IKeyboard::Keys::KEY_M, KeyboardKey::KEY_M},
            {IKeyboard::Keys::KEY_COMMA, KeyboardKey::KEY_COMMA},
            {IKeyboard::Keys::KEY_DOT, -1},
            {IKeyboard::Keys::KEY_RIGHT_SHIFT, KeyboardKey::KEY_RIGHT_SHIFT},

            /// Line 5
            {IKeyboard::Keys::KEY_LEFT_ALT, KeyboardKey::KEY_LEFT_ALT},
            {IKeyboard::Keys::KEY_SPACE, KeyboardKey::KEY_SPACE},
            {IKeyboard::Keys::KEY_RIGHT_ALT, KeyboardKey::KEY_RIGHT_ALT},
            {IKeyboard::Keys::KEY_RIGHT_CONTROL, KeyboardKey::KEY_RIGHT_CONTROL},
    
            /// KEYPAD
            {IKeyboard::Keys::KEY_PAD_0, KeyboardKey::KEY_KP_0},
            {IKeyboard::Keys::KEY_PAD_1, KeyboardKey::KEY_KP_1},
            {IKeyboard::Keys::KEY_PAD_2, KeyboardKey::KEY_KP_2},
            {IKeyboard::Keys::KEY_PAD_3, KeyboardKey::KEY_KP_3},
            {IKeyboard::Keys::KEY_PAD_4, KeyboardKey::KEY_KP_4},
            {IKeyboard::Keys::KEY_PAD_5, KeyboardKey::KEY_KP_5},
            {IKeyboard::Keys::KEY_PAD_6, KeyboardKey::KEY_KP_6},
            {IKeyboard::Keys::KEY_PAD_7, KeyboardKey::KEY_KP_7},
            {IKeyboard::Keys::KEY_PAD_8, KeyboardKey::KEY_KP_8},
            {IKeyboard::Keys::KEY_PAD_9, KeyboardKey::KEY_KP_9},
            {IKeyboard::Keys::KEY_PAD_MINUS, KeyboardKey::KEY_KP_SUBTRACT},
            {IKeyboard::Keys::KEY_PAD_PLUS, KeyboardKey::KEY_KP_ADD},
            {IKeyboard::Keys::KEY_PAD_DOT, KeyboardKey::KEY_KP_DECIMAL},
            {IKeyboard::Keys::KEY_PAD_ENTER, KeyboardKey::KEY_KP_ENTER},

            //Arrow
            {IKeyboard::Keys::KEY_UP, KeyboardKey::KEY_UP},
            {IKeyboard::Keys::KEY_DOWN, KeyboardKey::KEY_DOWN},
            {IKeyboard::Keys::KEY_LEFT, KeyboardKey::KEY_LEFT},
            {IKeyboard::Keys::KEY_RIGHT, KeyboardKey::KEY_RIGHT},
        };
};

#endif /* !RAYKEYBOARD_HPP_ */