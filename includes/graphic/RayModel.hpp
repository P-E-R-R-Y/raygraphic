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
        RayModel() {
            _position = {0, 0, 0};
            _size = {1, 1, 1};
        }

        ~RayModel() = default;

        Vector3f getPosition() const override {
            return {_position.x, _position.y, _position.z};
        }

        void setPosition(Vector3f position) override {
            _position = {float(position.x), float(position.y), float(position.z)};
        }

        friend class RayWindow;

    private:
        RaylibVector3 _position;
        RaylibVector3 _size;
};

#endif /* !RAYMODEL_HPP_ */