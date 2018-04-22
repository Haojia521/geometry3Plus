#ifndef G3_MATH_VECTOR_3_D
#define G3_MATH_VECTOR_3_D

#include <math/vector2d.h>
#include <math/vector3f.h>

namespace g3
{
    class Vector3d
    {
    public:
        typedef double   value_type;
        typedef Vector3d self_type;
        typedef Vector2d assoc_2d_type;

        // static values
        static const self_type zero;
        static const self_type one;
        static const self_type oneNormalized;
        static const self_type axisX;
        static const self_type axisY;
        static const self_type axisZ;
        static const self_type maxValue;
        static const self_type minValue;
        static const self_type invalid;

        // static functions
        static inline value_type dot(const self_type &v1, const self_type &v2)
        { return v1.dot(v2); }
        static inline self_type cross(const self_type &v1, const self_type &v2)
        { return v1.cross(v2); }

        static inline value_type angleD(const self_type &v1, const self_type &v2)
        { return v1.angleD(v2); }
        static inline value_type angleR(const self_type &v1, const self_type &v2)
        { return v1.angleR(v2); }

        static inline self_type lerp(const self_type &a, const self_type &b, value_type t)
        {
            auto s = 1.f - t;
            return self_type(s * a.x() + t * b.x(), 
                             s * a.y() + t * b.y(), 
                             s * a.z() + t * b.z());
        }

        // constructors
        Vector3d() { _x = _y = _z = 0; }
        Vector3d(value_type d) { _x = _y = _z = d;}
        Vector3d(value_type x, value_type y, value_type z) { _x = x; _y = y; _z = z; }
        Vector3d(value_type vals[]) { _x = vals[0]; _y = vals[1]; _z = vals[2]; }

        // copy-constructors
        Vector3d(const self_type &copy) { _x = copy._x; _y = copy._y; _z = copy._z; }

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
        inline value_type length() const { return std::sqrt(_x * _x + _y * _y + _z * _z); }
        inline value_type lengthL1() const { return std::abs(_x) + std::abs(_y) + std::abs(_z); }

        inline value_type max() const { return std::fmax(_x, std::fmax(_y, _z)); }
        inline value_type min() const { return std::fmin(_x, std::fmin(_y, _z)); }

        inline value_type maxAbs() const 
        { return std::fmax(std::abs(_x), std::fmax(std::abs(_y), std::abs(_z))); }
        inline value_type minAbs() const 
        { return std::fmin(std::abs(_x), std::fmin(std::abs(_y), std::abs(_z))); }

        inline self_type abs() const
        { return self_type(std::abs(_x), std::abs(_y), std::abs(_z)); }

        value_type normalize(value_type epsilon = mathUtil::epsilon);
        self_type normalized() const;

        inline bool isNormalized() const
        { return std::abs((_x * _x + _y * _y + _z * _z) - 1.0) < mathUtil::zeroTolerance; }

        // TODO: realize function 'vector3d::round()'
        inline void round(int decimals)
        { }

        inline value_type dot(const self_type &v) const
        { return _x * v._x + _y * v._y + _z * v._z; }

        inline self_type cross(const self_type &v) const
        { return self_type(_y * v._z - _z * v._y, _z * v._x - _x * v._z, _x * v._y - _y * v._x); }

        inline self_type unitCross(const self_type &v) const
        { return cross(v).normalize(); }

        inline value_type angleD(const self_type &v) const
        {
            auto fDot = mathUtil::clamp(dot(v), -1.0, 1.0);
            return std::acos(fDot) * mathUtil::rad2deg;
        }

        inline value_type angleR(const self_type &v) const
        {
            auto fDot = mathUtil::clamp(dot(v), -1.0, 1.0);
            return std::acos(fDot);
        }

        inline value_type distanceSquared(const self_type &v) const
        {
            auto dx = _x - v._x, dy = _y - v._y, dz = _z - v._z;
            return dx * dx + dy * dy + dz * dz;
        }

        inline value_type distance(const self_type &v) const
        { return std::sqrt(distanceSquared(v)); }

        inline void set(const self_type &v) { _x = v._x; _y = v._y; _z = v._z; }
        inline void set(value_type x, value_type y, value_type z) { _x = x; _y = y; _z = z; }

        inline void add(const self_type &v) { _x += v._x; _y += v._y; _z += v._z; }
        inline void subtract(const self_type &v) { _x -= v._x; _y -= v._y; _z -= v._z; }

        inline bool equals(const self_type &v) const
        { return (*this) == v; }
        inline bool epsilonEqual(const self_type &v, value_type eps) const
        { return std::abs(_x - v._x) <= eps && std::abs(_y - v._y) <= eps && std::abs(_z - v._z) <= eps; }

        // operator functions
        inline value_type& operator [] (int i) 
        { if (i == 0) return _x; else if (i == 1) return _y; else return _z; }
        inline value_type  operator [] (int i) const 
        { if (i == 0) return _x; else if (i == 1) return _y; else return _z; }

        inline operator Vector3f() const
        {
            return Vector3f(static_cast<Vector3f::value_type>(_x),
                            static_cast<Vector3f::value_type>(_y),
                            static_cast<Vector3f::value_type>(_z));
        }

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

    inline Vector3d operator + (Vector3d::value_type d, const Vector3d &v)
    { return v + d; }

    inline Vector3d operator * (Vector3d::value_type d, const Vector3d &v)
    { return v * d; }

    inline Vector3d operator / (Vector3d::value_type d, const Vector3d &v)
    { return Vector3d(d / v.x(), d / v.y(), d / v.z()); }
}

#endif
