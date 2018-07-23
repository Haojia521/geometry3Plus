#ifndef G3_MATH_TRIANGLE_2
#define G3_MATH_TRIANGLE_2

#include <math/vector3d.h>

namespace g3
{
    template<typename T>
    class Triangle2
    {
    public:
        typedef typename Vector2Traits<T>::vector_type vector_type;
        typedef typename Vector3Traits<T>::vector_type vector3_type;
        typedef typename vector_type::value_type value_type;

        // constructors
        Triangle2(const vector_type &v0, const vector_type &v1, const vector_type &v2)
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
        inline vector_type& v0() { return _v0; }
        inline vector_type& v1() { return _v1; }
        inline vector_type& v2() { return _v2; }
        inline vector_type  v0() const { return _v0; }
        inline vector_type  v1() const { return _v1; }
        inline vector_type  v2() const { return _v2; }

        inline vector_type pointAt(value_type bary0, value_type bary1, value_type bary2)
        { return _v0 * bary0 + _v1 * bary1 + _v2 * bary2; }

        inline vector_type pointAt(const vector3_type &bary)
        { return _v0 * bary.x() + _v1 * bary.y() + _v2 * bary.z(); }

        inline vector3_type barycentricCoords(const vector_type &point)
        { return mathUtil::barycentricCoords<vector_type, vector3_type>(point, _v0, _v1, _v2); }

        // operators
        inline vector_type  operator [] (int i) const
        { return (i == 0) ? _v0 : (i == 1) ? _v1 : _v2; }
        inline vector_type& operator [] (int i)
        { return (i == 0) ? _v0 : (i == 1) ? _v1 : _v2; }

    private:
        vector_type _v0, _v1, _v2;
    };

    typedef Triangle2<double> Triangle2d;
    typedef Triangle2<float>  Triangle2f;
}

#endif
