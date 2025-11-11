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
#include "Shape.hpp"

class RayPolygon : public graphic::IPolygon {

public:
    RayPolygon(std::vector<Vector2f> points) {
        _color = raylib::Color{255, 0, 0, 255};
        _position = {0, 0};

        // Store both user points (Vector2f) and Raylib points
        for (auto point : points) {
            _points.push_back(raylib::Vector2{float(point.x), float(point.y)});
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
        _position = raylib::Vector2{float(position.x), float(position.y)};
    }

    Color getColor() const override {
        return Color{_color.r, _color.g, _color.b, _color.a};
    }

    void setColor(Color color) override {
        _color = raylib::Color{color.r, color.g, color.b, color.a};
    }

    std::vector<Vector2f> getPoints() const override {
        return _systemPoints;
    }

    friend class RayWindow;

private:
    // Triangulation using your system Vector2f (safe, avoids Raylib pollution)

    float polygon_area(const std::vector<Vector2f>& pts) {
        float area = 0;
        for (size_t i = 0; i < pts.size(); ++i) {
            const Vector2f& a = pts[i];
            const Vector2f& b = pts[(i + 1) % pts.size()];
            area += (a.x * b.y - b.x * a.y);
        }
        return area * 0.5f;
    }

    void triangulate() {
        std::vector<Vector2f> tmp = _systemPoints;

        // ✅ Optional: ensure CCW winding for correct convexity
        if (polygon_area(tmp) < 0)
            std::reverse(tmp.begin(), tmp.end());

        while (tmp.size() >= 3) {
            bool earFound = false; // ✅ added: to prevent infinite loops

            for (size_t i = 0; i < tmp.size(); i++) {
                Vector2f A = tmp[i];
                Vector2f B = tmp[(i + 1) % tmp.size()];
                Vector2f C = tmp[(i + 2) % tmp.size()];
                Triangle<double> t = Triangle<double>{A, B, C};

                if (is_convex(A, B, C)) {
                    bool isEar = true;
                    for (size_t j = 0; j < tmp.size(); j++) {
                        if (j == i || j == (i + 1) % tmp.size() || j == (i + 2) % tmp.size()) continue;
                        if (t.isInside(tmp[j])) {
                            isEar = false;
                            break;
                        }
                    }

                    if (isEar) {
                        _triangles.push_back(Triangle<double>{A, B, C});

                        // ✅ fixed: compute erase index explicitly (avoid modulo precedence issue)
                        size_t earIndex = (i + 1) % tmp.size();
                        tmp.erase(tmp.begin() + earIndex);

                        earFound = true; // ✅ mark that we clipped one ear
                        break;           // restart after ear clip
                    }
                }
            }

            if (!earFound)
                break;
        }
    }

    raylib::Color _color;
    raylib::Vector2 _position;

    std::vector<raylib::Vector2> _points;     // for rendering with Raylib
    std::vector<Vector2f> _systemPoints;    // for logic/geometry
    std::vector<Triangle<double>> _triangles;
};

#endif /* !RAYPOLYGON_HPP_ */