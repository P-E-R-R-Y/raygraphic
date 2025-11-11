/**
 * @file RayText.hpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2025-02-03
 * 
 * @addtogroup Raylib
 */

#ifndef RAYTEXT_HPP_
#define RAYTEXT_HPP_

//standard
#include <string>

//Raylib (without conflict)
#include "RaylibAliases.hpp"


    //Interface
    #include "IText.hpp"


class RayText: public graphic::IText {

    public:
        RayText(std::string data, std::string font) {
            _data = data;
            _position = {0, 0};
            _color = raylib::Color{255, 255, 255, 255};
            _font = raylib::LoadFont(font.c_str());
            _size = 20;
            _spacing = 1;
            _rotation = 0;
            updateOrigin();
        }

        ~RayText() override {}

        bool isReady() const override {
            return raylib::IsFontValid(_font);
        }

        void setText(const std::string text) override {
            _data = text;
            updateOrigin();
        }

        std::string getText() const override {
            return _data;
        }

        void setFont(std::string font) override {
            _font = raylib::LoadFont(font.c_str());
            updateOrigin();
        }

        void setFontSize(unsigned int size)  override {
            _size = size;
            updateOrigin();
        }
        unsigned int getFontSize() const override {
            return _size;
        }
        

        void setTextColor(Color color) override {
            _color = raylib::Color{static_cast<unsigned char>(color.r), static_cast<unsigned char>(color.g), static_cast<unsigned char>(color.b),static_cast<unsigned char>(color.a)};
        } 

        Color getTextColor() const override {
            return Color{_color.r, _color.g, _color.b, _color.a};
        } 

        void setPosition(Vector2f position) override {
            _position = raylib::Vector2{static_cast<float>(position.x), static_cast<float>(position.y)};
        }
        Vector2f getPosition() const override {
            return Vector2f{_position.x, _position.y};
        }

        void setRotation(float angle) override {
            _rotation = angle;
        }

        float getRotation() const override {
            return _rotation;
        }

        friend class RayWindow;

    private:

        void updateOrigin() {
            const raylib::Vector2 textSize = raylib::MeasureTextEx(_font, _data.c_str(), _size, _spacing);
            _origin = { textSize.x / 2, textSize.y / 2 };
        }

        std::string _data;
        raylib::Vector2 _position;
        raylib::Color _color;
        raylib::Font _font;
        unsigned int _size;
        raylib::Vector2 _origin;
        float _rotation;
        float _spacing;

};

#endif /* !RAYTEXT_HPP_ */