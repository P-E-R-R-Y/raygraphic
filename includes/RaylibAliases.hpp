#pragma once

// Rename Raylib types to avoid conflicts
#define Vector2 RaylibVector2
#define Vector3 RaylibVector3
#define Vector4 RaylibVector4
#define Color RaylibColor
#define Quaternion RaylibQuaternion

#include <raylib.h>

#undef Vector2
#undef Vector3
#undef Vector4
#undef Color
#undef Quaternion