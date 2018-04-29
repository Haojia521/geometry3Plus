#ifndef G3_MATH_AXIS_ALIGNED_BOX_2
#define G3_MATH_AXIS_ALIGNED_BOX_2

#include <cstdlib>
#include <algorithm>
#include <vector>

#include <math/vector2d.h>

namespace g3
{
    template<typename VecT>
    class AxisAlignedBox2
    {
    public:
        typedef VecT                      vector_type;
        typedef typename VecT::value_type value_type;
        typedef AxisAlignedBox2<VecT>     self_type;

        enum ScaleMode
        {
            ScaleRight,
            ScaleLeft,
            ScaleUp,
            ScaleDown,
            ScaleCenter
        };

        // static values
        static const self_type empty        = self_type();
        static const self_type zero         = self_type(0);
        static const self_type unitPositive = self_type(1);
        static const self_type infinite     = self_type(vector_type::minValue, vector_type::maxValue);

        // constructors
        AxisAlignedBox2() : _min(vector_type::maxValue), _max(vector_type::minValue) {}
        AxisAlignedBox2(value_type xmin, value_type ymin, value_type xmax, value_type ymax) :
            _min(xmin, ymin), _max(_xmax, ymax) {}
        AxisAlignedBox2(value_type squareSize) :
            _min(0, 0), _max(squareSize, squareSize) {}
        AxisAlignedBox2(value_type width, height) :
            _min(0, 0), _max(width, height) {}
        AxisAlignedBox2(const vector_type &vmin, const vector_type &vmax) :
            _min(vmin), _max(vmax) {}
        AxisAlignedBox2(const vector_type &center, value_type halfWidth, value_type halfHeight) :
            _min(center.x() - halfWidth, center.y() - halfHeight), 
            _max(center.x() + halfWidth, center.y() + halfHeight) {}
        AxisAlignedBox2(const vector_type &center, value_type halfSize) :
            _min(center - halfSize), _max(center + halfSize) {}
        AxisAlignedBox2(const vector_type &center) :
            _min(center), _max(center) {}

        // copy constructor
        AxisAlignedBox2(const self_type &copy) :
            _min(copy._min), _max(copy._max) {}
        
        // functions
        inline bool valid() const { return (_max.x() >= _min.x() && _max.y() >= _min.y()); }

        inline value_type width() const { if (valid()) return _max.x() - _min.x(); else return 0; }
        inline value_type height() const { if (valid()) return _max.y() - _min.y(); else return 0; }

        inline value_type area() const { return width() * height(); }

        inline value_type diagonalLength() const
        { return std::sqrt(width() * width() + height() * height()); }

        inline value_type maxDim() const { return std::fmax(width(), height()); }
        inline value_type minDim() const { return std::fmin(width(), height()); }

        // returns absolute value of largest min/max x/y coordinate (ie max axis distance to origin)
        inline value_type maxUnsignedCoordinate() const
        {
            return std::fmax(std::fmax(std::abs(_min.x()), std::abs(_max.x())), 
                             std::fmax(std::abs(_min.y()), std::abs(_max.y())));
        }

        inline vector_type diagonal() const { if (valid()) return (_max - _min); else return vector_type(); }
        inline vector_type center() const { if (valid()) return (_max + _min) * 0.5f; else return vector_type(); }

        inline vector_type sampleT(value_type tx, value_type sy) const
        {
            return vector_type((1 - tx) * _min.x() + tx * _max.x(), 
                               (1 - sy) * _min.y() + sy * _max.y());
        }

        //! value is subtracted from min and added to max
        inline void expand(value_type radius)
        {
            _min.x() -= radius; _min.y() -= radius;
            _max.x() += radius; _max.y() += radius;
        }

        //! value is added to min and subtracted from max
        inline void contract(double radius) {
            _min.x() += radius; _min.y() += radius;
            _max.x() -= radius; _max.y() -= radius;
        }

        inline void add(value_type left, value_type right, value_type bottom, value_type top)
        {
            _min.x() += left; _min.y() += bottom;
            _max.x() += right; _max.y() += top;
        }

        void setWidth(value_type newWidth, ScaleMode mode)
        {
            switch (mode)
            {
            case ScaleMode::ScaleLeft:
                _min.x() = _max.x() - newWidth; break;
            case ScaleMode::ScaleRight:
                _max.x() = _min.x() + newWidth; break;
            case ScaleMode::ScaleCenter:
                auto c = center();
                _min.x() = c.x() - 0.5f * newWidth;
                _max.x() = c.x() + 0.5f * newWidth;
                break;
            default:
                break;
            }
        }

        void setHeight(value_type newHeight, ScaleMode mode)
        {
            switch (mode)
            {
            case ScaleMode::ScaleDown:
                _min.y() = _max.y() - newHeight; break;
            case ScaleMode::ScaleUp:
                _max.y() = _min.y() + newHeight; break;
            case ScaleMode::ScaleCenter:
                auto c = center();
                _min.y() = c.y() - 0.5f * newHeight;
                _max.y() = c.y() + 0.5f * newHeight;
                break;
            default:
                break;
            }
        }

        void contain(const vector_type &v)
        {
            if (valid())
            {
                if (v.x() < _min.x()) _min.x() = v.x();
                else if (v.x() > _max.x()) _max.x() = v.x();
                if (v.y() < _min.y()) _min.y() = v.y();
                else if (v.y() > _max.y()) _max.y() = v.y();
            }
            else _min = _max = v;
        }

        void contain(const self_type &box)
        {
            if (!box.valid()) return;
            if (valid())
            {
                if (box._min.x() < _min.x()) _min.x() = box._min.x();
                if (box._max.x() > _max.x()) _max.x() = box._max.x();
                if (box._min.y() < _min.y()) _min.y() = box._min.y();
                if (box._max.y() > _max.y()) _max.y() = box._max.y();
            }
            else
            {
                _min = box._min;
                _max = box._max;
            }
        }

        void contain(const std::vector<vector_type> &points)
        {
            for (const auto &v : points) contain(v);
        }

        self_type intersect(const self_type &box) const
        {
            self_type intersection(std::max(_min.x(), box._min.x()), 
                                   std::max(_min.y(), box._min.y()), 
                                   std::min(_max.x(), box._max.x()), 
                                   std::min(_max.y(), box._min.y()));
            if (intersection.valid()) return intersection;
            else return self_type::empty;
        }

        inline bool contains(const vector_type &v) const
        { return (_min.x() < v.x()) && (_min.y() < v.y()) && (_max.x() > v.x()) && (_max.y() > v.y()); }

        inline bool contains(const self_type &box) const
        { return contains(box._min) && contains(box._max); }

        inline bool intersects(const self_type &box)
        { return intersect(box).valid(); }

        value_type distance(const vector_type &v) const
        {
            value_type dx = std::abs(v.x() - center().x());
            value_type dy = std::abs(v.y() - center().y());
            value_type hw = width() * 0.5f;
            value_type hh = height() * 0.5f;
            if (dx < hw && dy < hh) return 0;
            else if (dx > hw && dy > hh)
                return std::sqrt((dx - fw) * (dx - fw) + (dy - hh) * (dy - hh));
            else if (dx > hw) return (dx - fw);
            else if (dy > hh) return (dy - hh);
            else return 0;
        }

        void translate(const vector_type &t)
        { _min.add(t); _max.add(t); }

        void scale(value_type s)
        { _min = _min * s; _max = _max * s; }

        void scale(value_type s, const vector_type &origin)
        {
            _min = (_min - origin) * s + origin;
            _max = (_max - origin) * s + origin;
        }

    private:
        vector_type _min, _max;
    };

    typedef AxisAlignedBox2<Vector2d> AxisAlignedBox2d;
    typedef AxisAlignedBox2<Vector2f> AxisAlignedBox2f;
    typedef AxisAlignedBox2<Vector2i> AxisAlignedBox2i;
}

#endif
