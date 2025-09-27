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
            _texture = LoadTexture(path.c_str());
            _position = {0, 0};
            _scale = {1, 1};
            _crop = {0, 0, float(_texture.width), float(_texture.height)};
        }

        ~RaySprite() {
            UnloadTexture(_texture);
        }

        bool isReady() const override {
            return IsTextureValid(_texture);
        }

        Vector4f getBounds() const override {
            return {_position.x, _position.y, float(_texture.width), float(_texture.height)};
        }

        void setCrop(Vector4f rect) override {
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
            return { float(_texture.width) * _scale.x, float(_texture.height) * _scale.y };
        }

        void setSize(Vector2f size) override {
            _scale = {float(this->getSize().x/float(_texture.width)), float(this->getSize().y/float(_texture.height))};
        }

        friend class RayWindow;

    private:
        Texture2D _texture;
        RaylibVector2 _position;
        RaylibVector2 _scale;
        Rectangle _crop;
        float _rotation;

        //your variables here
};

#endif /* !RAYSPRITE_HPP_ */