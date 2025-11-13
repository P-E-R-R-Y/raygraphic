/**
 * @file RayCamera.hpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-29
 * 
 * @addtogroup Raylib
 * @{
 */


#ifndef RAYCAMERA_HPP_
#define RAYCAMERA_HPP_

//Raylib (without conflict)
#include "RaylibAliases.hpp"

//Interface
#include "ICamera.hpp"

/**
 * @brief Raylib Camera class
 */
class RayCamera : public graphic::ICamera {

    public:

        /**
         * @brief Construct a new Ray Camera object
         */
        RayCamera(Vector3f pos = {100.0f, 100.0f, 100.0f}, Vector3f target = {0.f, 0.f, 0.f}, float fov = 45.f) {
            _camera = { 0 };
            _camera.position = (raylib::Vector3){ (float)pos.x, (float)pos.y, (float)pos.z };    // Camera position
            _camera.target = (raylib::Vector3){ (float)target.x, (float)target.y, (float)target.z };      // Camera looking at point
            _camera.up = (raylib::Vector3){ 0.f, 1.f, 0.0f };          // Camera up vector (rotation towards target)
            _camera.fovy = fov;                                // Camera field-of-view Y
            _camera.projection = raylib::CAMERA_PERSPECTIVE;             // Camera projection type
            _mode = raylib::CAMERA_CUSTOM;
        }

        /**
         * @brief Destroy the Ray Camera object
         */
        ~RayCamera() {}

        /**
         * @brief Get the Fov object
         * 
         * @return float 
         */
        float getFov() const override {
            return _camera.fovy;
        }

        /**
         * @brief Set the Fov object
         * 
         * @param fov 
         */
        void setFov(float fov) override {
            _camera.fovy = fov;
        }
        
        /**
         * @brief Get the Mode object
         * 
         * @return ICamera::Mode 
         */
        ICamera::Mode getMode() const override {
            switch(_mode) {
                case raylib::CameraMode::CAMERA_CUSTOM:
                    return ICamera::Mode::CUSTOM;
                case raylib::CameraMode::CAMERA_FREE:
                    return ICamera::Mode::FREE;
                case raylib::CameraMode::CAMERA_ORBITAL:
                    return ICamera::Mode::ORBITAL;
                case raylib::CameraMode::CAMERA_FIRST_PERSON:
                    return ICamera::Mode::FIRST_PERSON;
                case raylib::CameraMode::CAMERA_THIRD_PERSON:
                    return ICamera::Mode::THIRD_PERSON;
            }
        }

        /**
         * @brief Set the Mode object
         * 
         * @param mode 
         */
        void setMode(ICamera::Mode mode) override {
            switch(mode) {
                case ICamera::Mode::CUSTOM:
                    _mode = raylib::CameraMode::CAMERA_CUSTOM;
                case ICamera::Mode::FREE:
                    _mode = raylib::CameraMode::CAMERA_FREE;
                case ICamera::Mode::ORBITAL:
                    _mode = raylib::CameraMode::CAMERA_ORBITAL;
                case ICamera::Mode::FIRST_PERSON:
                    _mode = raylib::CameraMode::CAMERA_FIRST_PERSON;
                case ICamera::Mode::THIRD_PERSON:
                    _mode = raylib::CameraMode::CAMERA_THIRD_PERSON;
            }
        }

        /**
         * @brief Get the Position object
         * 
         * @return Vector3f 
         */
        Vector3f getPosition() const override {
            return {_camera.position.x, _camera.position.y, _camera.position.z};
        }

        /**
         * @brief Set the Position object
         * 
         * @param position 
         */
        void setPosition(Vector3f position) override {
            _camera = {float(position.x), float(position.y), float(position.z)};
        }
        
        /**
         * @brief Get the Projection object
         * 
         * @return ICamera::Projection 
         */
        ICamera::Projection getProjection() const override {
            switch(_camera.projection) {
                case raylib::CAMERA_PERSPECTIVE:
                    return ICamera::PERSPECTIVE;
                case raylib::CAMERA_ORTHOGRAPHIC:
                    return ICamera::ORTHOGRAPHIC;
            }
            return ICamera::PERSPECTIVE;
        }

        /**
         * @brief Set the Projection object
         * 
         * @param projection 
         */
        void setProjection(ICamera::Projection projection) override {
            switch(projection) {
                case ICamera::PERSPECTIVE:
                    _camera.projection = raylib::CAMERA_PERSPECTIVE;
                case ICamera::ORTHOGRAPHIC:
                    _camera.projection = raylib::CAMERA_ORTHOGRAPHIC;
            }
            _camera.projection = projection;
        }

        /**
         * @brief Get the Target object
         * 
         * @return Vector3f 
         */
        Vector3f getTarget() const override {
            return {_camera.target.x, _camera.target.y, _camera.target.z};
        }
        
        /**
         * @brief Set the Target object
         * 
         * @param target 
         */
        void setTarget(Vector3f target) override {
            _camera = {float(target.x), float(target.y), float(target.z)};
        }

        /**
         * @brief Get the Up object
         * 
         * @return Vector3f 
         */
        Vector3f getUp() const override {
            return {_camera.up.x, _camera.up.y, _camera.up.z};
        }

        /**
         * @brief Set the Up object
         * 
         * @param up 
         */
        void setUp(Vector3f up) override {
            _camera.up = {float(up.x), float(up.y), float(up.z)};
        }

        friend class RayWindow;

    private:
        raylib::Camera _camera;
        raylib::CameraMode _mode;
};

#endif /* !RAYMODEL2_HPP_ */