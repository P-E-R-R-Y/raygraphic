/**
 * @file IAudio.hpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2025-02-02
 * 
 * @addtogroup graphic
 * @{
 */

#ifndef RAYSOUND_HPP_
    #define RAYSOUND_HPP_

//Raylib (without conflict)
#include "RaylibAliases.hpp"

#include "ISound.hpp"

class RaySound: public graphic::ISound {

    public:

        RaySound(std::string path) {
            _sound = raylib::LoadSound(path.c_str());
            _volume = 1.0f;
        }

        ~RaySound() override {
            raylib::UnloadSound(_sound);
        }

        bool isReady() const override {
            return raylib::IsSoundValid(_sound);
        }

        /**
         * @brief play the sound
         */
        void play() override {
            raylib::PlaySound(_sound);
        }

        /**
         * @brief pause the sound
         * 
         */
        void pause() override {
            raylib::PauseSound(_sound);
        }

        /**
         * @brief stop the sound and reset it to the beginning
         * 
         */
        void stop() override {
            raylib::StopSound(_sound);
        }

        /**
         * @brief set the volume of the sound
         * 
         * @param volume 
         */
        void setVolume(float volume) override {
            _volume = volume;
            raylib::SetSoundVolume(_sound, volume);
        }

        /**
         * @brief get the volume of the sound
         * 
         * @return float 
         */
        float getVolume() const override {
            return _volume;
        }

    private:

        raylib::Sound _sound;
        float _volume;
};

#endif /* !RAYSOUND_HPP_ */