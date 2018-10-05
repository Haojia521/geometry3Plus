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
        typedef Vector2d vector_type;
    };

    template<>
    struct Vector2Traits<float>
    {
        typedef Vector2f vector_type;
    };

    template<>
    struct Vector2Traits<int>
    {
        typedef Vector2i vector_type;
    };

    template<typename T>
    struct Vector3Traits{};

    template<>
    struct Vector3Traits<double>
    {
        typedef Vector3d vector_type;
    };

    template<>
    struct Vector3Traits<float>
    {
        typedef Vector3f vector_type;
    };

    template<>
    struct Vector3Traits<int>
    {
        typedef Vector3i vector_type;
    };

    template<typename T>
    struct Vector4Traits{};

    template<>
    struct Vector4Traits<double>
    {
        typedef Vector4d vector_type;
    };

    template<>
    struct Vector4Traits<float>
    {
        typedef Vector4f vector_type;
    };
}

#endif
