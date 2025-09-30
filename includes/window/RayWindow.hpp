/**
 * @file RayWindow.hpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-29
 * 
 * @addtogroup Raylib
 * @{
 */

#ifndef RAYWINDOW_HPP_
#define RAYWINDOW_HPP_

//Raylib (without conflict)
#include "RaylibAliases.hpp"

//Interface
#include "IWindow.hpp"

//encapsulation
#include "RayPolygon.hpp"
#include "RaySprite.hpp"
#include "RayModel.hpp"
#include "RayText.hpp"
#include "RayCamera.hpp"

#include <iostream>

/**
 * @brief Raylib Window class
 */
class RayWindow : public graphic::IWindow {

    public:
        RayWindow(int32_t screenWidth, int32_t screenHeight, std::string title): quitRequested(false) {
            InitWindow(screenWidth, screenHeight, title.c_str());
//            SetWindowState(FLAG_WINDOW_RESIZABLE);
//            SetWindowMinSize(800, 600);
//            SetWindowMaxSize(1920, 1080);
        };

        ~RayWindow() {
            CloseWindow();
        };

        //GLOBAL

        //IsWindowReady for init fails
        //WindowShouldClose for escape & alt+f4
        //quitRequested when user ask to close the app under is own condition
        bool isOpen() override {
            return IsWindowReady() && !WindowShouldClose() && !quitRequested;
        };

        void close() override {
            quitRequested = true;
        };

        //EVENT
        void linkEvent(graphic::IEvent *event) override {
        };
        
        bool pollEvent() override {
            static bool firstCall = true;
            firstCall = !firstCall;
            return !firstCall;
        }

        //not define cause eventClose is internally define using Key::Escape
        void eventClose() override {
        };
        
        //TIME
        void setFrameLimit(int32_t limit) override {
            SetTargetFPS(limit);
        };

        int32_t getDelta() override {
            return static_cast<int32_t>(GetFrameTime() * 1000);
        };

        //2D
        void beginDraw() override {
            BeginDrawing();
            ClearBackground({ 0, 0, 0, 255 });
        };

        void endDraw() override {
            EndDrawing();
        };

        void drawPoly(graphic::IPolygon *polygon) override;
        void drawSprite(graphic::ISprite *sprite) override;
        
        void drawText(graphic::IText *text) override {
            RayText *raytext = static_cast<RayText *>(text);

//            DrawTextPro(raytext->_font, "Press SPACE to PLAY the WAV sound!", 200, 180, 20, LIGHTGRAY);
//            DrawTextPro(raytext->_font, raytext->_data.c_str(), raytext->_position, {0, 0},raytext->_rotation, raytext->_size, 1, raytext->_color);
            DrawTextPro(raytext->_font, raytext->_data.c_str(), raytext->_position, {0, 0},raytext->_rotation, raytext->_size, 1, raytext->_color);
        };

        //3D
        //Draw3 (Carve)
        void beginMode3(graphic::ICamera *camera) override;
        
        void drawModel(graphic::IModel *model) override;

        void endMode3() override;

        bool beginAudio() override {
            InitAudioDevice();
            return true;
        };

        void endAudio() override {
            CloseAudioDevice();
        };

    private:
        bool quitRequested;
};

//2D
void RayWindow::drawPoly(graphic::IPolygon *polygon) {
    RayPolygon *rayPolygon = static_cast<RayPolygon *>(polygon);
    std::vector<graphic::Triangle> triangles = rayPolygon->_triangles;

    std::cout << "StartDraw" << std::endl;
    for (int i = 0; i < triangles.size(); i++) {
        //raylib ask for counter clockwise it's why I reverse the order
        DrawTriangle({static_cast<float>(triangles[i].C.x), static_cast<float>(triangles[i].C.y)},
                    {static_cast<float>(triangles[i].B.x), static_cast<float>(triangles[i].B.y)},
                    {static_cast<float>(triangles[i].A.x), static_cast<float>(triangles[i].A.y)},
                    rayPolygon->_color);
    }
    std::cout << "EndDraw" << std::endl;
};

void RayWindow::drawSprite(graphic::ISprite *sprite) {
    RaySprite *raysprite = static_cast<RaySprite *>(sprite);
    Rectangle posSize = {float(raysprite->getPosition().x), float(raysprite->getPosition().y),
                        float(raysprite->getSize().x), float(raysprite->getSize().y) };

    DrawTexturePro(raysprite->_texture, raysprite->_crop, posSize, {0,0}, raysprite->_rotation, { 255, 255, 255, 255 });
};

//3D

void RayWindow::beginMode3(graphic::ICamera *camera) {
    RayCamera *raycamera = static_cast<RayCamera *>(camera);

    BeginMode3D(raycamera->_camera);
};

void RayWindow::drawModel(graphic::IModel *model) {
    RayModel *raymodel = static_cast<RayModel *>(model);

    DrawCubeV(raymodel->_position, raymodel->_size, { 255, 0, 0, 255 });
    DrawCubeWiresV(raymodel->_position, raymodel->_size, { 0, 0, 0, 255 });
};

void RayWindow::endMode3() {
    EndMode3D();
};

#endif /* !RAYWINDOW_HPP_ */