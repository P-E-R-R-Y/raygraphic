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

    //Interface
    #include "IText.hpp"

    //Raylib
    #include <raylib.h>

class RayText: public graphic::IText {

    public:
        RayText(std::string data, std::string font) {
            _data = data;
            _position = {0, 0};
            _color = Color{255, 255, 255, 255};
            _font = LoadFont(font.c_str());
            _size = 20;
            _spacing = 1;
            _rotation = 0;
            updateOrigin();
        }

        ~RayText() override {}

        bool isReady() const override {
            return IsFontReady(_font);
        }

        void setText(const std::string text) override {
            _data = text;
            updateOrigin();
        }

        std::string getText() const override {
            return _data;
        }

        void setFont(std::string font) override {
            _font = LoadFont(font.c_str());
            updateOrigin();
        }

        void setFontSize(unsigned int size)  override {
            _size = size;
            updateOrigin();
        }
        unsigned int getFontSize() const override {
            return _size;
        }
        

        void setTextColor(__color_t color) override {
            _color = Color{static_cast<unsigned char>(color.r), static_cast<unsigned char>(color.g), static_cast<unsigned char>(color.b),static_cast<unsigned char>(color.a)};
        } 

        __color_t getTextColor() const override {
            return __color_t{_color.r, _color.g, _color.b, _color.a};
        } 

        void setPosition(__v2f_t position) override {
            _position = Vector2{position.x, position.y};
        }
        __v2f_t getPosition() const override {
            return __v2f_t{_position.x, _position.y};
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
            const Vector2 textSize = MeasureTextEx(_font, _data.c_str(), _size, _spacing);
            _origin = { textSize.x / 2, textSize.y / 2 };
        }

        std::string _data;
        Vector2 _position;
        Color _color;
        Font _font;
        unsigned int _size;
        Vector2 _origin;
        float _rotation;
        float _spacing;

};

#endif /* !RAYTEXT_HPP_ */