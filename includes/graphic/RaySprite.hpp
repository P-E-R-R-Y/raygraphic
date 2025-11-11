/**
 * @file RaySprite.hpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-29
 * 
 * @addtogroup Raylib
 * @{
 */


#ifndef RAYSPRITE_HPP_
#define RAYSPRITE_HPP_

//Raylib (without conflict)
#include "RaylibAliases.hpp"

//Interface
#include "ISprite.hpp"

/**
 * @brief Raylib Sprite class
 */
class RaySprite : public graphic::ISprite {

    public:
        RaySprite(std::string path) {
            _texture = raylib::LoadTexture(path.c_str());
            _position = {0, 0};
            _scale = {1, 1};
            _crop = {0, 0, float(_texture.width), float(_texture.height)};
        }

        ~RaySprite() {
            raylib::UnloadTexture(_texture);
        }

        bool isReady() const override {
            return raylib::IsTextureValid(_texture);
        }

        Rect<float> getBounds() const override {
            return {_position.x, _position.y, float(_texture.width), float(_texture.height)};
        }

        void setCrop(Rect<float> rect) override {
            _crop = {float(rect.x), float(rect.y), float(rect.w), float(rect.h)};
        }

        Vector2f getPosition() const override {
            return {_position.x, _position.y};
        }
        void setPosition(Vector2f position) override {
            _position = {float(position.x), float(position.y)};
        }

        float getRotation() const override {
            return _rotation;
        }

        void setRotation(float angle, bool isRad = false) override {
            if (isRad) {
                _rotation = angle * DEG2RAD;
            } else {
                _rotation = angle;
            }
        }

        Vector2f getSize() const override {
            return {
                static_cast<float>(_texture.width) * _scale.x,
                static_cast<float>(_texture.height) * _scale.y
            };
        }

        // 🔹 Set absolute size in pixels (based on texture dimensions)
        void setSize(Vector2f size) override {
            if (_texture.width == 0 || _texture.height == 0) return;

            _scale.x = size.x / static_cast<float>(_texture.width);
            _scale.y = size.y / static_cast<float>(_texture.height);
        }
            

        friend class RayWindow;

    private:
        raylib::Texture2D _texture;
        raylib::Vector2 _position;
        raylib::Vector2 _scale;
        raylib::Rectangle _crop;
        float _rotation;

        //your variables here
};

#endif /* !RAYSPRITE_HPP_ */