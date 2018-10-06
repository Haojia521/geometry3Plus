#ifndef G3_MATH_VECTOR_TUPLE
#define G3_MATH_VECTOR_TUPLE

#include <tuple>

#include <math/vector3d.h>

namespace g3
{
    using Vector3dTuple2 = std::tuple<Vector3d, Vector3d>;
    using Vector3dTuple3 = std::tuple<Vector3d, Vector3d, Vector3d>;

    using Vector3fTuple2 = std::tuple<Vector3f, Vector3f>;
    using Vector3fTuple3 = std::tuple<Vector3f, Vector3f, Vector3f>;

    using Vector2dTuple2 = std::tuple<Vector2d, Vector2d>;
    using Vector2dTuple3 = std::tuple<Vector2d, Vector2d, Vector2d>;
    using Vector2dTuple4 = std::tuple<Vector2d, Vector2d, Vector2d, Vector2d>;

    using Vector2fTuple2 = std::tuple<Vector2f, Vector2f>;
    using Vector2fTuple3 = std::tuple<Vector2f, Vector2f, Vector2f>;
    using Vector2fTuple4 = std::tuple<Vector2f, Vector2f, Vector2f, Vector2f>;

    template<typename T, int N, class = std::enable_if<(N > 0)>>
    struct VectorTupleTrait{};

    template<>
    struct VectorTupleTrait<Vector3d, 2>
    {
        using tuple_type = Vector3dTuple2;
    };

    template<>
    struct VectorTupleTrait<Vector3d, 3>
    {
        using tuple_type = Vector3dTuple3;
    };
    
    template<>
    struct VectorTupleTrait<Vector3f, 2>
    {
        using tuple_type = Vector3fTuple2;
    };

    template<>
    struct VectorTupleTrait<Vector3f, 3>
    {
        using tuple_type = Vector3fTuple3;
    };

    template<>
    struct VectorTupleTrait<Vector2d, 2>
    {
        using tuple_type = Vector2dTuple2;
    };

    template<>
    struct VectorTupleTrait<Vector2d, 3>
    {
        using tuple_type = Vector2dTuple3;
    };

    template<>
    struct VectorTupleTrait<Vector2d, 4>
    {
        using tuple_type = Vector2dTuple4;
    };

    template<>
    struct VectorTupleTrait<Vector2f, 2>
    {
        using tuple_type = Vector2fTuple2;
    };

    template<>
    struct VectorTupleTrait<Vector2f, 3>
    {
        using tuple_type = Vector2fTuple3;
    };

    template<>
    struct VectorTupleTrait<Vector2f, 4>
    {
        using tuple_type = Vector2fTuple4;
    };
}

#endif
