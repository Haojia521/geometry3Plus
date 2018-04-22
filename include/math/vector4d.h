#ifndef G3_MATH_VECTOR_4_D
#define G3_MATH_VECTOR_4_D

#include <math/vector4f.h>

namespace g3
{
    class G3Export Vector4d
    {
    public:
        typedef double   value_type;
        typedef Vector4d self_type;

        // static values
        static const self_type zero;
        static const self_type one;

        // static functions
        static inline value_type dot(const self_type &v1, const self_type &v2)
        { return v1.dot(v2); }

        static inline value_type angleD(const self_type &v1, const self_type &v2)
        { return v1.angleD(v2); }
        static inline value_type angleR(const self_type &v1, const self_type &v2)
        { return v1.angleR(v2); }

        // constructors
        Vector4d() { _x = _y = _z = _w = 0; }
        Vector4d(value_type d) { _x = _y = _z = _w = d; }
        Vector4d(value_type x, value_type y, value_type z, value_type w) { _x = x; _y = y; _z = z; _w = w; }
        Vector4d(value_type vals[]) { _x = vals[0]; _y = vals[1]; _z = vals[2]; _w = vals[3]; }
        
        // copy-constructors
        Vector4d(const self_type &copy) { _x = copy._x; _y = copy._y; _z = copy._z; _w = copy._w; }

        // type conversion
        Vector4d(const Vector4f &v4f)
        {
            _x = static_cast<value_type>(v4f.x());
            _y = static_cast<value_type>(v4f.y());
            _z = static_cast<value_type>(v4f.z());
            _w = static_cast<value_type>(v4f.w());
        }

        inline operator Vector4f() const
        {
            return Vector4f(static_cast<Vector4f::value_type>(_x), 
                            static_cast<Vector4f::value_type>(_y), 
                            static_cast<Vector4f::value_type>(_z), 
                            static_cast<Vector4f::value_type>(_w));
        }

        // functions
        inline value_type& x() { return _x; }
        inline value_type& y() { return _y; }
        inline value_type& z() { return _z; }
        inline value_type& w() { return _w; }
        inline value_type  x() const { return _x; }
        inline value_type  y() const { return _y; }
        inline value_type  z() const { return _z; }
        inline value_type  w() const { return _w; }

        inline value_type lengthSquared() const { return _x * _x + _y * _y + _z * _z + _w * _w; }
        inline value_type length() const { return std::sqrt(_x * _x + _y * _y + _z * _z + _w * _w); }
        inline value_type lengthL1() const { return std::abs(_x) + std::abs(_y) + std::abs(_z) + std::abs(_w); }

        value_type normalize(value_type epsilon = mathUtil::epsilon);
        self_type normalized() const;

        inline bool isNormalized() const
        { return std::abs((_x * _x + _y * _y + _z * _z + _w * _w) - 1.0) < mathUtil::zeroTolerance; }

        // TODO: realize function 'vector4d::round()'
        inline void round(int decimals)
        { }

        inline value_type dot(const self_type &v) const
        { return _x * v._x + _y * v._y + _z * v._z + _w * v._w; }

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
            auto dx = _x - v._x, dy = _y - v._y, dz = _z - v._z, dw = _w - v._w;
            return dx * dx + dy * dy + dz * dz + dw * dw;
        }

        inline value_type distance(const self_type &v) const
        { return std::sqrt(distanceSquared(v)); }

        inline void set(const self_type &v) { _x = v._x; _y = v._y; _z = v._z; _w = v._w; }
        inline void set(value_type x, value_type y, value_type z, value_type w) { _x = x; _y = y; _z = z; _w = w; }

        inline void add(const self_type &v) { _x += v._x; _y += v._y; _z += v._z; _w += _w; }
        inline void subtract(const self_type &v) { _x -= v._x; _y -= v._y; _z -= v._z; _w -= v._w; }

        inline bool equals(const self_type &v) const
        { return (*this) == v; }
        inline bool epsilonEqual(const self_type &v, value_type eps) const
        { return std::abs(_x - v._x) <= eps && std::abs(_y - v._y) <= eps && std::abs(_z - v._z) <= eps && std::abs(_w - v._w) <= eps; }

        // operator functions
        inline value_type& operator [] (int i) 
        { if (i == 0) return _x; else if (i == 1) return _y; else if (i == 2) return _z; else return _w; }
        inline value_type  operator [] (int i) const 
        { if (i == 0) return _x; else if (i == 1) return _y; else if (i == 2) return _z; else return _w; }

        inline self_type operator - () const { return self_type(-_x, -_y, -_z, -_w); }

        inline self_type operator - (const self_type &v) const
        { return self_type(_x - v._x, _y - v._y, _z - v._z, _w - v._w); }
        inline self_type operator - (value_type d) const
        { return self_type(_x - d, _y - d, _z - d, _w - d); }

        inline self_type operator + (const self_type &v) const
        { return self_type(_x + v._x, _y + v._y, _z + v._z, _w + v._w); }
        inline self_type operator + (value_type d) const
        { return self_type(_x + d, _y + d, _z + d, _w + d); }
        friend self_type operator + (value_type d, const self_type &v);

        inline self_type operator * (const self_type &v) const
        { return self_type(_x * v._x, _y * v._y, _z * v._z, _w * v._w); }

        inline self_type operator * (value_type d) const
        { return self_type(_x * d, _y * d, _z * d, _w * d); }
        friend self_type operator * (value_type d, const self_type &v);

        inline self_type operator / (const self_type &v) const
        { return self_type(_x / v._x, _y / v._y, _z / v._z, _w / v._w); }

        inline self_type operator / (value_type d) const
        { return self_type(_x / d, _y / d, _z / d, _w / d); }
        friend self_type operator / (value_type d, const self_type &v);

        inline bool operator == (const self_type &v) const
        { return _x == v._x && _y == v._y && _z == v._z && _w == v._w; }
        inline bool operator != (const self_type &v) const
        { return !((*this) == v); }

    private:
        value_type _x, _y, _z, _w;
    };

    inline Vector4d operator + (Vector4d::value_type d, const Vector4d &v)
    { return v + d; }

    inline Vector4d operator * (Vector4d::value_type d, const Vector4d &v)
    { return v * d; }

    inline Vector4d operator / (Vector4d::value_type d, const Vector4d &v)
    { return Vector4d(d / v.x(), d / v.y(), d / v.z(), d / v.w()); }
}

#endif
