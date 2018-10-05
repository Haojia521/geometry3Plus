#ifndef G3_MATH_VECTOR_TUPLE
#define G3_MATH_VECTOR_TUPLE

#include <tuple>

#include <math/vector3d.h>

namespace g3
{
    typedef std::tuple<Vector3d, Vector3d>                     Vector3dTuple2;
    typedef std::tuple<Vector3d, Vector3d, Vector3d>           Vector3dTuple3;

    typedef std::tuple<Vector3f, Vector3f>                     Vector3fTuple2;
    typedef std::tuple<Vector3f, Vector3f, Vector3f>           Vector3fTuple3;

    typedef std::tuple<Vector2d, Vector2d>                     Vector2dTuple2;
    typedef std::tuple<Vector2d, Vector2d, Vector2d>           Vector2dTuple3;
    typedef std::tuple<Vector2d, Vector2d, Vector2d, Vector2d> Vector2dTuple4;

    typedef std::tuple<Vector2f, Vector2f>                     Vector2fTuple2;
    typedef std::tuple<Vector2f, Vector2f, Vector2f>           Vector2fTuple3;
    typedef std::tuple<Vector2f, Vector2f, Vector2f, Vector2f> Vector2fTuple4;

    template<typename T, int N, class = std::enable_if<(N > 0)>>
    struct VectorTupleTrait{};

    template<>
    struct VectorTupleTrait<Vector3d, 2>
    {
        typedef Vector3dTuple2 tuple_type;
    };

    template<>
    struct VectorTupleTrait<Vector3d, 3>
    {
        typedef Vector3dTuple3 tuple_type;
    };
    
    template<>
    struct VectorTupleTrait<Vector3f, 2>
    {
        typedef Vector3fTuple2 tuple_type;
    };

    template<>
    struct VectorTupleTrait<Vector3f, 3>
    {
        typedef Vector3fTuple3 tuple_type;
    };

    template<>
    struct VectorTupleTrait<Vector2d, 2>
    {
        typedef Vector2dTuple2 tuple_type;
    };

    template<>
    struct VectorTupleTrait<Vector2d, 3>
    {
        typedef Vector2dTuple3 tuple_type;
    };

    template<>
    struct VectorTupleTrait<Vector2d, 4>
    {
        typedef Vector2dTuple4 tuple_type;
    };

    template<>
    struct VectorTupleTrait<Vector2f, 2>
    {
        typedef Vector2fTuple2 tuple_type;
    };

    template<>
    struct VectorTupleTrait<Vector2f, 3>
    {
        typedef Vector2fTuple3 tuple_type;
    };

    template<>
    struct VectorTupleTrait<Vector2f, 4>
    {
        typedef Vector2fTuple4 tuple_type;
    };
}

#endif
