/**
 * @file RayModel.hpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-29
 * 
 * @addtogroup Raylib
 * @{
 */

#ifndef RAYMODEL_HPP_
#define RAYMODEL_HPP_

//Raylib (without conflict)
#include "RaylibAliases.hpp"
namespace raylib{
    #include "raymath.h"
}

//Interface
#include "IModel.hpp"

/**
 * @brief Raylib Model class
 */
class RayModel : public graphic::IModel {

    public:

        /**
         * @brief Construct a new Ray Model object
         */
        RayModel(std::string path): _position{}, _rotation{}, _scale{1, 1, 1}, _animsSize(0), _animId(0), _animFrame(0)  {
            _model = raylib::LoadModel(path.c_str());
            _boundingbox = raylib::GetModelBoundingBox(_model);
            _animations = nullptr;
        }

        ~RayModel() = default;

        void setTexture(std::string path) override {
            _texture = raylib::LoadTexture(path.c_str());
            for (int i = 0; i < _model.materialCount; i++) {
                raylib::SetMaterialTexture(&_model.materials[i], raylib::MATERIAL_MAP_DIFFUSE, _texture);
            }
        }

        //animation
        void setAnimations(std::string path) override{
            if (_animations)
                raylib::UnloadModelAnimations(_animations, _animsSize);
            _animations = raylib::LoadModelAnimations(path.c_str(), &_animsSize);
            _animFrame = 0;
            _animId = 0;
        }
        virtual int getAnimationsSize() const override{
            return _animsSize;
        }
        virtual void setAnimation(int pos) override{
            _animId = pos;
        }
        int getAnimation() const override {
            return _animId;
        }
        virtual void updateAnimation() override{
            if (_animsSize == 0 || _animId >= _animsSize || _animations[_animId].frameCount == 0) {
                return;
            }
            raylib::UpdateModelAnimation(_model, _animations[_animId], _animFrame++ % _animations[_animId].frameCount);
        }

        //position
        Vector3f getPosition() const override {
            return {_position.x, _position.y, _position.z};
        }

        void setPosition(Vector3f position) override {
            _position = {float(position.x), float(position.y), float(position.z)};
        }

        Vector3f getRotation() const override {
            return {_rotation.x, _rotation.y, _rotation.z};
        }

        void setRotation(Vector3f rotation) override {
            _rotation = {float(rotation.x), float(rotation.y), float(rotation.z)};
            _model.transform = raylib::MatrixRotateXYZ((raylib::Vector3){ DEG2RAD*_rotation.x, DEG2RAD*_rotation.y, DEG2RAD*_rotation.z });
        }

        Vector3f getSize() const override {
            raylib::Vector3 s = {
                _boundingbox.max.x - _boundingbox.min.x,
                _boundingbox.max.y - _boundingbox.min.y,
                _boundingbox.max.z - _boundingbox.min.z
            };

            return {
                s.x * _scale.x,
                s.y * _scale.y,
                s.z * _scale.z
            };
        }

        void setSize(Vector3f size) override {
            raylib::Vector3 s = {
                _boundingbox.max.x - _boundingbox.min.x,
                _boundingbox.max.y - _boundingbox.min.y,
                _boundingbox.max.z - _boundingbox.min.z
            };

            if (s.x == 0 || s.y == 0 || s.z == 0) return;

            _scale.x = size.x / s.x;
            _scale.y = size.y / s.y;
            _scale.z = size.z / s.z;
        }

        friend class RayWindow;

    private:
        raylib::Texture2D _texture;
        raylib::Model _model;
        raylib::Vector3 _rotation;
        raylib::Vector3 _position;
        raylib::Vector3 _scale;
        raylib::BoundingBox _boundingbox;
        raylib::ModelAnimation *_animations;
        int _animsSize;
        int _animId;
        int _animFrame;
};

#endif /* !RAYMODEL_HPP_ */