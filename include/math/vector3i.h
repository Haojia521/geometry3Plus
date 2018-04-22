#ifndef G3_MATH_VECTOR_3_I
#define G3_MATH_VECTOR_3_I

#include <math/vector2i.h>

namespace g3
{
    class Vector3i
    {
    public:
        typedef int      value_type;
        typedef Vector3i self_type;
        typedef Vector2i assoc_2d_type;

        // static values
        static const self_type zero;
        static const self_type one;
        static const self_type axisX;
        static const self_type axisY;
        static const self_type axisZ;

        // constructors
        Vector3i() { _x = _y = _z = 0; }
        Vector3i(value_type d) { _x = _y = _z = d; }
        Vector3i(value_type x, value_type y, value_type z) { _x = x; _y = y; _z = z; }
        Vector3i(value_type vals[]) { _x = vals[0]; _y = vals[1]; _z = vals[2]; }

        // copy-constructors
        Vector3i(const self_type &copy) { _x = copy._x; _y = copy._y; _z = copy._z; }

        // functions
        inline value_type& x() { return _x; }
        inline value_type& y() { return _y; }
        inline value_type& z() { return _z; }
        inline value_type  x() const { return _x; }
        inline value_type  y() const { return _y; }
        inline value_type  z() const { return _z; }

        inline assoc_2d_type xy() const { return assoc_2d_type(_x, _y); }
        inline void xy(const assoc_2d_type &v) { _x = v.x(); _y = v.y(); }

        inline assoc_2d_type xz() const { return assoc_2d_type(_x, _z); }
        inline void xz(const assoc_2d_type &v) { _x = v.x(); _z = v.y(); }

        inline assoc_2d_type yz() const { return assoc_2d_type(_y, _z); }
        inline void yz(const assoc_2d_type &v) { _y = v.x(), _z = v.y(); }

        inline value_type lengthSquared() const { return _x * _x + _y * _y + _z * _z; }

        inline void set(const self_type &v) { _x = v._x; _y = v._y; _z = v._z; }
        inline void set(value_type x, value_type y, value_type z) { _x = x; _y = y; _z = z; }

        inline void add(const self_type &v) { _x += v._x; _y += v._y; _z += v._z; }
        inline void subtract(const self_type &v) { _x -= v._x; _y -= v._y; _z -= v._z; }

        inline bool equals(const self_type &v) const
        { return (*this) == v; }

        // operator functions
        inline value_type& operator [] (int i) 
        { if (i == 0) return _x; else if (i == 2) return _y; else return _z; }
        inline value_type  operator [] (int i) const 
        { if (i == 0) return _x; else if (i == 2) return _y; else return _z; }

        inline self_type operator - () const { return self_type(-_x, -_y, -_z); }

        inline self_type operator - (const self_type &v) const
        { return self_type(_x - v._x, _y - v._y, _z - v._z); }
        inline self_type operator - (value_type d) const
        { return self_type(_x - d, _y - d, _z - d); }

        inline self_type operator + (const self_type &v) const
        { return self_type(_x + v._x, _y + v._y, _z + v._z); }
        inline self_type operator + (value_type d) const
        { return self_type(_x + d, _y + d, _z + d); }
        friend self_type operator + (value_type d, const self_type &v);

        inline self_type operator * (const self_type &v) const
        { return self_type(_x * v._x, _y * v._y, _z * v._z); }

        inline self_type operator * (value_type d) const
        { return self_type(_x * d, _y * d, _z * d); }
        friend self_type operator * (value_type d, const self_type &v);

        inline self_type operator / (const self_type &v) const
        { return self_type(_x / v._x, _y / v._y, _z / v._z); }

        inline self_type operator / (value_type d) const
        { return self_type(_x / d, _y / d, _z / d); }
        friend self_type operator / (value_type d, const self_type &v);

        inline bool operator == (const self_type &v) const
        { return _x == v._x && _y == v._y && _z == v._z; }
        inline bool operator != (const self_type &v) const
        { return !((*this) == v); }

    private:
        value_type _x, _y, _z;
    };

    inline Vector3i operator + (Vector3i::value_type d, const Vector3i &v)
    { return v + d; }

    inline Vector3i operator * (Vector3i::value_type d, const Vector3i &v)
    { return v * d; }

    inline Vector3i operator / (Vector3i::value_type d, const Vector3i &v)
    { return Vector3i(d / v.x(), d / v.y(), d / v.z()); }
}

#endif
