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
            raylib::InitWindow(screenWidth, screenHeight, title.c_str());
//            SetWindowState(FLAG_WINDOW_RESIZABLE);
//            SetWindowMinSize(800, 600);
//            SetWindowMaxSize(1920, 1080);
        };

        ~RayWindow() {
            raylib::CloseWindow();
        };

        //GLOBAL

        //IsWindowReady for init fails
        //WindowShouldClose for escape & alt+f4
        //quitRequested when user ask to close the app under is own condition
        bool isOpen() override {
            return raylib::IsWindowReady() && !raylib::WindowShouldClose() && !quitRequested;
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
            raylib::SetTargetFPS(limit);
        };

        int32_t getDelta() override {
            return static_cast<int32_t>(raylib::GetFrameTime() * 1000);
        };

        //2D
        void beginDraw() override {
            raylib::BeginDrawing();
            raylib::ClearBackground({ 0, 0, 0, 255 });
        };

        void endDraw() override {
            raylib::EndDrawing();
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
            raylib::InitAudioDevice();
            return true;
        };

        void endAudio() override {
            raylib::CloseAudioDevice();
        };

    private:
        bool quitRequested;
};

//2D
void RayWindow::drawPoly(graphic::IPolygon *polygon) {
    RayPolygon *rayPolygon = static_cast<RayPolygon *>(polygon);
    std::vector<Triangle<double>> triangles = rayPolygon->_triangles;

    for (int i = 0; i < triangles.size(); i++) {
        //raylib ask for counter clockwise it's why I reverse the order
        raylib::DrawTriangle({static_cast<float>(triangles[i].p3.x + rayPolygon->getPosition().x), static_cast<float>(triangles[i].p3.y + rayPolygon->getPosition().y)},
                    {static_cast<float>(triangles[i].p2.x + rayPolygon->getPosition().x), static_cast<float>(triangles[i].p2.y + rayPolygon->getPosition().y)},
                    {static_cast<float>(triangles[i].p1.x + rayPolygon->getPosition().x), static_cast<float>(triangles[i].p1.y + rayPolygon->getPosition().y)},
                    rayPolygon->_color);
    }
};

void RayWindow::drawSprite(graphic::ISprite *sprite) {
    RaySprite *raysprite = static_cast<RaySprite *>(sprite);
    raylib::Rectangle posSize = {float(raysprite->getPosition().x), float(raysprite->getPosition().y),
                        float(raysprite->getSize().x), float(raysprite->getSize().y) };

    raylib::DrawTexturePro(raysprite->_texture, raysprite->_crop, posSize, {0,0}, raysprite->_rotation, { 255, 255, 255, 255 });
};

//3D

void RayWindow::beginMode3(graphic::ICamera *camera) {
    RayCamera *raycamera = static_cast<RayCamera *>(camera);

    BeginMode3D(raycamera->_camera);
};

void RayWindow::drawModel(graphic::IModel *model) {
    RayModel *raymodel = static_cast<RayModel *>(model);

    raylib::DrawCubeV(raymodel->_position, raymodel->_size, { 255, 0, 0, 255 });
    raylib::DrawCubeWiresV(raymodel->_position, raymodel->_size, { 0, 0, 0, 255 });
};

void RayWindow::endMode3() {
    raylib::EndMode3D();
};

#endif /* !RAYWINDOW_HPP_ */