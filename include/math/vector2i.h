#ifndef G3_MATH_VECTOR_2_I
#define G3_MATH_VECTOR_2_I

namespace g3
{
    class Vector2i
    {
    public:
        using value_type = int;
        using self_type  = Vector2i;

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
        value_type& x() { return _x; }
        value_type& y() { return _y; }
        value_type  x() const { return _x; }
        value_type  y() const { return _y; }

        value_type lengthSquared() const { return _x * _x + _y * _y; }

        value_type distanceSquared(const self_type &v) const
        {
            value_type dx = _x - v._x, dy = _y - v._y;
            return dx * dx + dy * dy;
        }

        void set(const self_type &v) { _x = v._x; _y = v._y; }
        void set(value_type x, value_type y) { _x = x; _y = y; }

        void add(const self_type &v) { _x += v._x; _y += v._y; }
        void subtract(const self_type &v) { _x -= v._x; _y -= v._y; }

        bool equals(const self_type &v) const
        { return (*this) == v; }

        // operator functions
        value_type& operator [] (int i) { if (i == 0) return _x; else return _y; }
        value_type  operator [] (int i) const { if (i == 0) return _x; else return _y; }

        self_type operator - () const { return self_type(-_x, -_y); }

        self_type operator - (const self_type &v) const
        { return self_type(_x - v._x, _y - v._y); }
        self_type operator - (value_type d) const
        { return self_type(_x - d, _y - d); }

        self_type operator + (const self_type &v) const
        { return self_type(_x + v._x, _y + v._y); }
        self_type operator + (value_type d) const
        { return self_type(_x + d, _y + d); }
        friend self_type operator + (value_type d, const self_type &v);

        self_type operator * (const self_type &v) const
        { return self_type(_x * v._x, _y * v._y); }

        self_type operator * (value_type d) const
        { return self_type(_x * d, _y * d); }
        friend self_type operator * (value_type d, const self_type &v);

        self_type operator / (const self_type &v) const
        { return self_type(_x / v._x, _y / v._y); }

        self_type operator / (value_type d) const
        { return self_type(_x / d, _y / d); }
        friend self_type operator / (value_type d, const self_type &v);

        bool operator == (const self_type &v) const
        { return _x == v._x && _y == v._y; }
        bool operator != (const self_type &v) const
        { return !((*this) == v); }

    private:
        value_type _x, _y;
    };

    const Vector2i Vector2i::zero = Vector2i();
    const Vector2i Vector2i::one = Vector2i(1, 1);
    const Vector2i Vector2i::axisX = Vector2i(1, 0);
    const Vector2i Vector2i::axisY = Vector2i(0, 1);

    Vector2i operator + (Vector2i::value_type d, const Vector2i &v)
    { return v + d; }

    Vector2i operator * (Vector2i::value_type d, const Vector2i &v)
    { return v * d; }

    Vector2i operator / (Vector2i::value_type d, const Vector2i &v)
    { return Vector2i(d / v.x(), d / v.y()); }
}

#endif
