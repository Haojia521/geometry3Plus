#ifndef G3_MATH_VECTOR_TRAITS
#define G3_MATH_VECTOR_TRAITS

#include <math/vector2d.h>
#include <math/vector3d.h>
#include <math/vector4d.h>

namespace g3
{
    template<typename T>
    struct Vector2Traits{};

    template<>
    struct Vector2Traits<double>
    {
        using vector_type = Vector2d;
    };

    template<>
    struct Vector2Traits<float>
    {
        using vector_type = Vector2f;
    };

    template<>
    struct Vector2Traits<int>
    {
        using vector_type = Vector2i;
    };

    template<typename T>
    struct Vector3Traits{};

    template<>
    struct Vector3Traits<double>
    {
        using vector_type = Vector3d;
    };

    template<>
    struct Vector3Traits<float>
    {
        using vector_type = Vector3f;
    };

    template<>
    struct Vector3Traits<int>
    {
        using vector_type = Vector3i;
    };

    template<typename T>
    struct Vector4Traits{};

    template<>
    struct Vector4Traits<double>
    {
        using vector_type = Vector4d;
    };

    template<>
    struct Vector4Traits<float>
    {
        using vector_type = Vector4f;
    };
}

#endif
