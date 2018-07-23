#ifndef G3_MATH_VECTOR_2_I
#define G3_MATH_VECTOR_2_I

#include <g3Export.h>
#include <math/vectorTraits.h>

namespace g3
{
    class G3Export Vector2i
    {
    public:
        typedef int      value_type;
        typedef Vector2i self_type;

        // static values
        static const self_type zero;
        static const self_type one;
        static const self_type axisX;
        static const self_type axisY;

        // constructors
        Vector2i() { _x = _y = 0; }
        Vector2i(value_type x, value_type y) { _x = x; _y = y; }
        Vector2i(value_type values[]) { _x = values[0]; _y = values[1]; }
        // copy-constructors
        Vector2i(const self_type &copy) { _x = copy._x; _y = copy._y; }

        // functions
        inline value_type& x() { return _x; }
        inline value_type& y() { return _y; }
        inline value_type  x() const { return _x; }
        inline value_type  y() const { return _y; }

        inline value_type lengthSquared() const { return _x * _x + _y * _y; }

        inline value_type distanceSquared(const self_type &v) const
        {
            value_type dx = _x - v._x, dy = _y - v._y;
            return dx * dx + dy * dy;
        }

        inline void set(const self_type &v) { _x = v._x; _y = v._y; }
        inline void set(value_type x, value_type y) { _x = x; _y = y; }

        inline void add(const self_type &v) { _x += v._x; _y += v._y; }
        inline void subtract(const self_type &v) { _x -= v._x; _y -= v._y; }

        inline bool equals(const self_type &v) const
        { return (*this) == v; }

        // operator functions
        inline value_type& operator [] (int i) { if (i == 0) return _x; else return _y; }
        inline value_type  operator [] (int i) const { if (i == 0) return _x; else return _y; }

        inline self_type operator - () const { return self_type(-_x, -_y); }

        inline self_type operator - (const self_type &v) const
        { return self_type(_x - v._x, _y - v._y); }
        inline self_type operator - (value_type d) const
        { return self_type(_x - d, _y - d); }

        inline self_type operator + (const self_type &v) const
        { return self_type(_x + v._x, _y + v._y); }
        inline self_type operator + (value_type d) const
        { return self_type(_x + d, _y + d); }
        friend self_type operator + (value_type d, const self_type &v);

        inline self_type operator * (const self_type &v) const
        { return self_type(_x * v._x, _y * v._y); }

        inline self_type operator * (value_type d) const
        { return self_type(_x * d, _y * d); }
        friend self_type operator * (value_type d, const self_type &v);

        inline self_type operator / (const self_type &v) const
        { return self_type(_x / v._x, _y / v._y); }

        inline self_type operator / (value_type d) const
        { return self_type(_x / d, _y / d); }
        friend self_type operator / (value_type d, const self_type &v);

        inline bool operator == (const self_type &v) const
        { return _x == v._x && _y == v._y; }
        inline bool operator != (const self_type &v) const
        { return !((*this) == v); }

    private:
        value_type _x, _y;
    };

    inline Vector2i operator + (Vector2i::value_type d, const Vector2i &v)
    { return v + d; }

    inline Vector2i operator * (Vector2i::value_type d, const Vector2i &v)
    { return v * d; }

    inline Vector2i operator / (Vector2i::value_type d, const Vector2i &v)
    { return Vector2i(d / v.x(), d / v.y()); }

    template<>
    struct Vector2Traits<int>
    {
        typedef Vector2i vector_type;
    };
}

#endif
