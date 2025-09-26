/**
 * @file RayPolygon.hpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @date 2025-09-26
 * 
 * @addtogroup Raylib
 * @{
 */

#ifndef RAYPOLYGON_HPP_
#define RAYPOLYGON_HPP_

#include <iostream>
#include <vector>

//Raylib (without conflict)
#include "RaylibAliases.hpp"

// Interface
#include "IPolygon.hpp"

// maths
#include "geometry.hpp"

class RayPolygon : public graphic::IPolygon {

public:
    RayPolygon(std::vector<Vector2f> points) {
        _color = RaylibColor{255, 0, 0, 255};
        _position = {0, 0};

        // Store both user points (Vector2f) and Raylib points
        for (auto point : points) {
            _points.push_back(RaylibVector2{float(point.x), float(point.y)});
            _systemPoints.push_back(point);
        }

        triangulate();
    }

    ~RayPolygon() = default;

    bool isReady() const override {
        return true;
    }

    Vector2f getPosition() const override {
        return {_position.x, _position.y};
    }

    void setPosition(Vector2f position) override {
        _position = RaylibVector2{float(position.x), float(position.y)};
    }

    Color getColor() const override {
        return Color{_color.r, _color.g, _color.b, _color.a};
    }

    void setColor(Color color) override {
        _color = RaylibColor{color.r, color.g, color.b, color.a};
    }

    std::vector<Vector2f> getPoints() const override {
        return _systemPoints;
    }

    friend class RayWindow;

private:
    // Triangulation using your system Vector2f (safe, avoids Raylib pollution)
    void triangulate() {
        std::vector<Vector2f> tmp = _systemPoints;
        while (tmp.size() >= 3) {
            for (size_t i = 0; i < tmp.size(); i++) {
                Vector2f A = tmp[i];
                Vector2f B = tmp[(i+1) % tmp.size()];
                Vector2f C = tmp[(i+2) % tmp.size()];

                if (is_convex(A, B, C)) {
                    bool isEar = true;
                    for (size_t j = 0; j < tmp.size(); j++) {
                        if (j == i || j == (i+1)%tmp.size() || j == (i+2)%tmp.size()) continue;
                        if (is_inside_triangle(tmp[j], A, B, C)) {
                            isEar = false;
                            break;
                        }
                    }
                    if (isEar) {
                        _triangles.push_back(graphic::triangle_t{A, B, C});
                        tmp.erase(tmp.begin() + (i+1) % tmp.size());
                        break; // restart after ear clip
                    }
                }
            }
        }
    }

    RaylibColor _color;
    RaylibVector2 _position;

    std::vector<RaylibVector2> _points;     // for rendering with Raylib
    std::vector<Vector2f> _systemPoints;    // for logic/geometry
    std::vector<graphic::triangle_t> _triangles;
};

#endif /* !RAYPOLYGON_HPP_ */