/**
 * @file RayMusic.hpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2025-02-03
 * 
 * @addtogroup Raylib
 */

#ifndef RAYMUSIC_HPP_
    #define RAYMUSIC_HPP_

    //Raylib (without conflict)
    #include "RaylibAliases.hpp"

    //Interface
    #include "IMusic.hpp"



class RayMusic: public graphic::IMusic {

    public:

        /**
         * @brief Construct a new Ray Music
         * 
         * @param path 
         */
        RayMusic(std::string path) {
            _music = raylib::LoadMusicStream(path.c_str());
            _pause = false;
            _volume = 1.0f;
        }
        
        /**
         * @brief Destroy the Ray Music
         * 
         */
        ~RayMusic() override {
            raylib::UnloadMusicStream(_music);
        }

        bool isReady() const override {
            return raylib::IsMusicValid(_music);
        }

        /**
         * @brief play the music
         */
        void play() override {
            if (_pause) {
                raylib::ResumeMusicStream(_music);
            } else {
                raylib::PlayMusicStream(_music);
            }
        }

        /**
         * @brief pause the music
         * 
         */
        void pause() override {
            if (!_pause) {
                _pause = true;
                raylib::PauseMusicStream(_music);
            }
        }

        /**
         * @brief stop the music and reset it to the beginning
         * 
         */
        void stop() override {
            raylib::StopMusicStream(_music);
        }

        void update() override {
            raylib::UpdateMusicStream(_music);

            if (!_loop && raylib::IsMusicStreamPlaying(_music) && 
                raylib::GetMusicTimePlayed(_music) >= raylib::GetMusicTimeLength(_music)) {
                this->stop();
            }
        }

        /**
         * @brief set the volume of the music
         * 
         * @param volume 
         */
        void setVolume(float volume) override {
            _volume = volume;
            raylib::SetMusicVolume(_music, volume);
        }

        /**
         * @brief get the volume of the music or if not set the master volume
         * 
         * @return float 
         */
        float getVolume() const override {
            return _volume;
        }

        /**
         * @brief set the music to loop or not
         * 
         * @param loop 
         */
        void setLoop(bool loop) override {
            _loop = loop;
        }

        /**
         * @brief get if the music is looping or not
         * 
         * @return true 
         * @return false 
         */
        bool getLoop() const override {
            return _loop; 
        }

        /**
         * @brief Set the time of the music in seconds
         * 
         * @param position 
         */
        void setTime(float position) override {
            raylib::SeekMusicStream(_music, position);
        }

        /**
         * @brief Get the current time of the music in seconds
         * 
         * @return float 
         */
        float getTime() const override {
            return raylib::GetMusicTimePlayed(_music);
        }

        /**
         * @brief Get the Length of the music
         * 
         * @return float 
         */
        float getLength() const override {
            return raylib::GetMusicTimeLength(_music);
        }

    private:

        raylib::Music _music;
        bool _loop;
        bool _pause;
        float _volume;
};

#endif /* !RAYMUSIC_HPP_ */