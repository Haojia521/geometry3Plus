#ifndef G3_MATH_TRIANGLE_2
#define G3_MATH_TRIANGLE_2

#include <math/vector3d.h>

namespace g3
{
    template<typename Vec2T, typename AssoVec3T>
    class Triangle2
    {
    public:
        typedef Vec2T     vec_type;
        typedef AssoVec3T asso_vec_type;
        typedef typename vec_type::value_type value_type;

        // constructors
        Triangle2(const vec_type &v0, const vec_type &v1, const vec_type &v2)
        { _v0 = v0; _v1 = v1; _v2 = v2; }

        // type conversion
        template<typename V2T, typename AV3T>
        inline operator Triangle2<V2T, AV3T> () const
        {
            return Triangle2<V2T, AV3T>(static_cast<V2T>(_v0), 
                                        static_cast<V2T>(_v1), 
                                        static_cast<V2T>(_v2));
        }

        // functions
        inline vec_type& v0() { return _v0; }
        inline vec_type& v1() { return _v1; }
        inline vec_type& v2() { return _v2; }
        inline vec_type  v0() const { return _v0; }
        inline vec_type  v1() const { return _v1; }
        inline vec_type  v2() const { return _v2; }

        inline vec_type pointAt(value_type bary0, value_type bary1, value_type bary2)
        { return _v0 * bary0 + _v1 * bary1 + _v2 * bary2; }

        inline vec_type pointAt(const asso_vec_type &bary)
        { return _v0 * bary.x() + _v1 * bary.y() + _v2 * bary.z(); }

        inline asso_vec_type barycentricCoords(const vec_type &point)
        { return mathUtil::barycentricCoords<vec_type, asso_vec_type>(point, _v0, _v1, _v2); }

        // operators
        inline vec_type  operator [] (int i) const
        { return (i == 0) ? _v0 : (i == 1) ? _v1 : _v2; }
        inline vec_type& operator [] (int i)
        { return (i == 0) ? _v0 : (i == 1) ? _v1 : _v2; }

    private:
        vec_type _v0, _v1, _v2;
    };

    typedef Triangle2<Vector2d, Vector3d> Triangle2d;
    typedef Triangle2<Vector2f, Vector3f> Triangle2f;
}

#endif
