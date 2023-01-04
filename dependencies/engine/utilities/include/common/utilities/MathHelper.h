#pragma once
#include <math.h>
#include <memory>

namespace Utilities
{
    struct Matrix4
    {
        Matrix4(float m00, float m01, float m02, float m03,
                float m10, float m11, float m12, float m13,
                float m20, float m21, float m22, float m23,
                float m30, float m31, float m32, float m33)
        {
            m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
            m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
            m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
            m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
        }

        float m[4][4];
    };

    union Vector2 {
        struct {
            float x, y;
        };
        struct {
            float u, v;
        };
        float idx[2];
    };

    union Vector3 
    {
        struct {
            float x, y, z;
        };
        float idx[3];
    };

    union Vector4
    {
        struct {
            float x, y, z, w;
        };
        float idx[4];
    };

    struct Vertex {
        constexpr Vertex(const Vector3 &inPosition, const Vector2 &inUV) 
            : position(inPosition)
            , uv(inUV) {}

        Vector3 position;
        Vector2 uv;
    };

    typedef uint16_t Index;

    template <typename T>
	union Point {
        struct {
		    T x;
		    T y;
        };

        // Overloading "+" operator
        Point<T> operator+ (Point<T> const& point)
        {
            return Point<T>{x + point.x, y + point.y};
        }
        
        // Overloading "+" operator
        Point<T> operator+ (Vector2 const& vec)
        {
            return Point<T>{x + vec.x, y + vec.y};
        }
	};

    struct Rectangle
    {
        Rectangle(int x, int y, int w, int h)
            : position(Point<float>{static_cast<float>(x), static_cast<float>(y)})
            , width(w)
            , height(h)
        { }

        Point<float> position;
        int width;
        int height;
    };

    struct Circle 
    {
        Circle(float x, float y, float radius)
            : position(Point<float>{x, y})
            , radius(radius)
        { }

        Point<float> position;
        float radius;
    };

    inline static Matrix4 simpleModelMatrix(float radians)
    {
	    const auto cosine = cosf(radians);
	    const auto sine = sinf(radians);

        return Matrix4(cosine, 0.0f,  -sine, 0.0f,
                        0.0f, 1.0f,   0.0f, 0.0f,
                        sine, 0.0f, cosine, 0.0f,
                        0.0f, 0.0f,   0.0f, 1.0f);
    }

    inline static Matrix4 simpleViewMatrix()
    {
        // Camera is at 60 degrees to the ground, in the YZ plane.
        // Camera Look-At is hardcoded to (0, 0, 0).
        // Camera Up is hardcoded to (0, 1, 0).
        const auto sqrt3over2 = 0.86603f;
        const auto cameraDistance = 5.0f;

        return Matrix4(1.0f,       0.0f,            0.0f, 0.0f,
                    0.0f, sqrt3over2,            0.5f, 0.0f,
                    0.0f,      -0.5f,      sqrt3over2, 0.0f,
                    0.0f,       0.0f, -cameraDistance, 1.0f);
    }

    inline static Matrix4 simpleProjectionMatrix(float aspectRatio)
    {
        // Far plane is at 50.0f, near plane is at 1.0f.
        // FoV is hardcoded to pi/3.
        const auto cotangent = 1 / tanf(3.14159f / 6.0f);

        return Matrix4(cotangent / aspectRatio,      0.0f,                    0.0f,                             0.0f,
                                        0.0f, cotangent,                    0.0f,                             0.0f,
                                        0.0f,      0.0f, -50.0f / (50.0f - 1.0f), (-50.0f * 1.0f) / (50.0f - 1.0f),
                                        0.0f,      0.0f,                   -1.0f,                             0.0f);
    }

    inline static float lerp(float a, float b, float t) 
    {
        return a + t * (b - a);
    }

    static float *
    buildOrthographicMatrix(float *outMatrix, 
                            float halfHeight,
                            float aspect,
                            float near,
                            float far) {
        float halfWidth = halfHeight * aspect;

        // column 1
        outMatrix[0] = 1.f / halfWidth;
        outMatrix[1] = 0.f;
        outMatrix[2] = 0.f;
        outMatrix[3] = 0.f;

        // column 2
        outMatrix[4] = 0.f;
        outMatrix[5] = 1.f / halfHeight;
        outMatrix[6] = 0.f;
        outMatrix[7] = 0.f;

        // column 3
        outMatrix[8] = 0.f;
        outMatrix[9] = 0.f;
        outMatrix[10] = -2.f / (far - near);
        outMatrix[11] = -(far + near) / (far - near);

        // column 4
        outMatrix[12] = 0.f;
        outMatrix[13] = 0.f;
        outMatrix[14] = 0.f;
        outMatrix[15] = 1.f;

        return outMatrix;
    }
}
