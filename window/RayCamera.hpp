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

//Interface
#include "ICamera.hpp"

//Raylib
#include <raylib.h>

/**
 * @brief Raylib Camera class
 */
class RayCamera : public graphic::ICamera {

    public:

        /**
         * @brief Construct a new Ray Camera object
         */
        RayCamera() {
            _camera = { 0 };
            _camera.position = (Vector3){ 4.0f, 4.0f, 4.0f };    // Camera position
            _camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
            _camera.up = (Vector3){ 0.f, 1.f, 0.0f };          // Camera up vector (rotation towards target)
            _camera.fovy = 60.0f;                                // Camera field-of-view Y
            _camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
            _mode = CAMERA_FREE;
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
            return ICamera::Mode(_mode);
        }

        /**
         * @brief Set the Mode object
         * 
         * @param mode 
         */
        void setMode(ICamera::Mode mode) override {
            _mode = CameraMode(mode);
        }
        
        /**
         * @brief Get the Position object
         * 
         * @return __v3f_t 
         */
        __v3f_t getPosition() const override {
            return {_camera.position.x, _camera.position.y, _camera.position.z};
        }

        /**
         * @brief Set the Position object
         * 
         * @param position 
         */
        void setPosition(__v3f_t position) override {
            _camera = {float(position.x), float(position.y), float(position.z)};
        }
        
        /**
         * @brief Get the Projection object
         * 
         * @return ICamera::Projection 
         */
        ICamera::Projection getProjection() const override {
            switch(_camera.projection) {
                case PERSPECTIVE:
                    return ICamera::PERSPECTIVE;
                case CAMERA_ORTHOGRAPHIC:
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
                    _camera.projection = CAMERA_PERSPECTIVE;
                case ICamera::ORTHOGRAPHIC:
                    _camera.projection = CAMERA_ORTHOGRAPHIC;
            }
            _camera.projection = projection;
        }

        /**
         * @brief Get the Target object
         * 
         * @return __v3f_t 
         */
        __v3f_t getTarget() const override {
            return {_camera.target.x, _camera.target.y, _camera.target.z};
        }
        
        /**
         * @brief Set the Target object
         * 
         * @param target 
         */
        void setTarget(__v3f_t target) override {
            _camera = {float(target.x), float(target.y), float(target.z)};
        }

        /**
         * @brief Get the Up object
         * 
         * @return __v3f_t 
         */
        __v3f_t getUp() const override {
            return {_camera.up.x, _camera.up.y, _camera.up.z};
        }

        /**
         * @brief Set the Up object
         * 
         * @param up 
         */
        void setUp(__v3f_t up) override {
            _camera.up = {float(up.x), float(up.y), float(up.z)};
        }

        friend class RayWindow;

    private:
        Camera _camera;
        CameraMode _mode;
};

#endif /* !RAYMODEL2_HPP_ */