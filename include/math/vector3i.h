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
        value_type& x() { return _x; }
        value_type& y() { return _y; }
        value_type& z() { return _z; }
        value_type  x() const { return _x; }
        value_type  y() const { return _y; }
        value_type  z() const { return _z; }

        assoc_2d_type xy() const { return assoc_2d_type(_x, _y); }
        void xy(const assoc_2d_type &v) { _x = v.x(); _y = v.y(); }

        assoc_2d_type xz() const { return assoc_2d_type(_x, _z); }
        void xz(const assoc_2d_type &v) { _x = v.x(); _z = v.y(); }

        assoc_2d_type yz() const { return assoc_2d_type(_y, _z); }
        void yz(const assoc_2d_type &v) { _y = v.x(), _z = v.y(); }

        value_type lengthSquared() const { return _x * _x + _y * _y + _z * _z; }

        void set(const self_type &v) { _x = v._x; _y = v._y; _z = v._z; }
        void set(value_type x, value_type y, value_type z) { _x = x; _y = y; _z = z; }

        void add(const self_type &v) { _x += v._x; _y += v._y; _z += v._z; }
        void subtract(const self_type &v) { _x -= v._x; _y -= v._y; _z -= v._z; }

        bool equals(const self_type &v) const
        { return (*this) == v; }

        // operator functions
        value_type& operator [] (int i) 
        { if (i == 0) return _x; else if (i == 1) return _y; else return _z; }
        value_type  operator [] (int i) const 
        { if (i == 0) return _x; else if (i == 1) return _y; else return _z; }

        self_type operator - () const { return self_type(-_x, -_y, -_z); }

        self_type operator - (const self_type &v) const
        { return self_type(_x - v._x, _y - v._y, _z - v._z); }
        self_type operator - (value_type d) const
        { return self_type(_x - d, _y - d, _z - d); }

        self_type operator + (const self_type &v) const
        { return self_type(_x + v._x, _y + v._y, _z + v._z); }
        self_type operator + (value_type d) const
        { return self_type(_x + d, _y + d, _z + d); }
        friend self_type operator + (value_type d, const self_type &v);

        self_type operator * (const self_type &v) const
        { return self_type(_x * v._x, _y * v._y, _z * v._z); }

        self_type operator * (value_type d) const
        { return self_type(_x * d, _y * d, _z * d); }
        friend self_type operator * (value_type d, const self_type &v);

        self_type operator / (const self_type &v) const
        { return self_type(_x / v._x, _y / v._y, _z / v._z); }

        self_type operator / (value_type d) const
        { return self_type(_x / d, _y / d, _z / d); }
        friend self_type operator / (value_type d, const self_type &v);

        bool operator == (const self_type &v) const
        { return _x == v._x && _y == v._y && _z == v._z; }
        bool operator != (const self_type &v) const
        { return !((*this) == v); }

    private:
        value_type _x, _y, _z;
    };

    const Vector3i Vector3i::zero = Vector3i();
    const Vector3i Vector3i::one = Vector3i(1, 1, 1);
    const Vector3i Vector3i::axisX = Vector3i(1, 0, 0);
    const Vector3i Vector3i::axisY = Vector3i(0, 1, 0);
    const Vector3i Vector3i::axisZ = Vector3i(0, 0, 1);

    Vector3i operator + (Vector3i::value_type d, const Vector3i &v)
    { return v + d; }

    Vector3i operator * (Vector3i::value_type d, const Vector3i &v)
    { return v * d; }

    Vector3i operator / (Vector3i::value_type d, const Vector3i &v)
    { return Vector3i(d / v.x(), d / v.y(), d / v.z()); }
}

#endif
