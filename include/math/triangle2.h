#ifndef G3_MATH_TRIANGLE_2
#define G3_MATH_TRIANGLE_2

#include <math/vectorTraits.h>

namespace g3
{
    template<typename T>
    class Triangle2
    {
    public:
        using vector_type  = typename Vector2Traits<T>::vector_type;
        using vector3_type = typename Vector3Traits<T>::vector_type;
        using value_type   = typename vector_type::value_type;

        // constructors
        Triangle2(const vector_type &v0, const vector_type &v1, const vector_type &v2)
        { _v0 = v0; _v1 = v1; _v2 = v2; }

        // type conversion
        template<typename U>
        operator Triangle2<U> () const
        {
            return Triangle2<U>(static_cast<typename Triangle2<U>::vector_type>(_v0), 
                                static_cast<typename Triangle2<U>::vector_type>(_v1),
                                static_cast<typename Triangle2<U>::vector_type>(_v2));
        }

        // functions
        vector_type& v0() { return _v0; }
        vector_type& v1() { return _v1; }
        vector_type& v2() { return _v2; }
        vector_type  v0() const { return _v0; }
        vector_type  v1() const { return _v1; }
        vector_type  v2() const { return _v2; }

        vector_type pointAt(value_type bary0, value_type bary1, value_type bary2)
        { return _v0 * bary0 + _v1 * bary1 + _v2 * bary2; }

        vector_type pointAt(const vector3_type &bary)
        { return _v0 * bary.x() + _v1 * bary.y() + _v2 * bary.z(); }

        vector3_type barycentricCoords(const vector_type &point)
        { return mathUtil::barycentricCoords<vector_type, vector3_type>(point, _v0, _v1, _v2); }

        // operators
        vector_type  operator [] (int i) const
        { return (i == 0) ? _v0 : (i == 1) ? _v1 : _v2; }
        vector_type& operator [] (int i)
        { return (i == 0) ? _v0 : (i == 1) ? _v1 : _v2; }

    private:
        vector_type _v0, _v1, _v2;
    };

    using Triangle2d = Triangle2<double>;
    using Triangle2f = Triangle2<float>;
}

#endif
