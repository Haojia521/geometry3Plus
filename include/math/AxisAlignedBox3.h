#ifndef G3_MATH_AXIS_ALIGNED_BOX_3
#define G3_MATH_AXIS_ALIGNED_BOX_3

#include <cstdlib>
#include <algorithm>

#include <math/vectorTraits.h>

namespace g3
{
    template<typename T>
    class AxisAlignedBox3
    {
    public:
        typedef typename Vector3Traits<T>::vector_type vector_type;
        typedef typename vector_type::value_type       value_type;
        typedef AxisAlignedBox3<T>                     self_type;

        // static values
        static const self_type empty;
        static const self_type zero;
        static const self_type unitPositive;
        static const self_type infinite;

        // constructors
        AxisAlignedBox3() : _min(vector_type::maxValue), _max(vector_type::minValue) {}
        AxisAlignedBox3(value_type xmin, value_type ymin, value_type zmin, 
                        value_type xmax, value_type ymax, value_type zmax) :
            _min(xmin, ymin, zmin), _max(xmax, ymax, zmax) {}
        AxisAlignedBox3(value_type cubeSize) :
            _min(0, 0, 0), _max(cubeSize, cubeSize, cubeSize) {}
        AxisAlignedBox3(value_type width, value_type height, value_type depth) :
            _min(0, 0, 0), _max(width, height, depth) {}
        AxisAlignedBox3(const vector_type &vmin, const vector_type &vmax) :
            _min(vmin), _max(vmax) {}
        AxisAlignedBox3(const vector_type &center, 
                        value_type halfWidth, value_type halfHeight, value_type halfDepth) :
            _min(center.x() - halfWidth, center.y() - halfHeight, center.z() - halfDepth),
            _max(center.x() + halfWidth, center.y() + halfHeight, center.z() + halfDepth) {}
        AxisAlignedBox3(const vector_type &center, value_type halfSize) :
            _min(center - halfSize), _max(center + halfSize) {}
        AxisAlignedBox3(const vector_type &center) :
            _min(center), _max(center) {}

        // type conversion
        template<typename U>
        operator AxisAlignedBox3<U>() const
        {
            return AxisAlignedBox3<U>(static_cast<typename AxisAlignedBox3<U>::vector_type>(_min),
                                      static_cast<typename AxisAlignedBox3<U>::vector_type>(_max));
        }

        // functions
        vector_type minCoordinate() const { return _min; }
        vector_type maxCoordinate() const { return _max; }

        bool valid() const { return (_max.x() >= _min.x() && 
                                            _max.y() >= _min.y() && 
                                            _max.z() >= _min.z()); }

        value_type width() const { if (valid()) return _max.x() - _min.x(); else return 0; }
        value_type height() const { if (valid()) return _max.y() - _min.y(); else return 0; }
        value_type depth() const { if (valid()) return _max.z() - _min.z(); else return 0; }

        value_type volume() const { return width() * height() * depth(); }

        value_type diagonalLength() const
        { return std::sqrt(width() * width() + height() * height() + depth() * depth()); }

        value_type maxDim() const { return std::max(width(), std::max(height(), depth())); }
        value_type minDim() const { return std::min(width(), std::min(height(), depth())); }

        vector_type diagonal() const { if (valid()) return (_max - _min); else return vector_type(); }
        vector_type center() const { if (valid()) return (_max + _min) * 0.5f; else return vector_type(); }
        vector_type extents() const { if (valid()) return (_max - _min) * 0.5f; else return vector_type(); }

        // See Box3.Corner for details on which corner is which
        //        7_________6(max)
        //       /|        /|          z
        //     4/_|______5/ |         |   y
        //      | |______|__|         | /
        //      | /3     | / 2        |/_____
        //      |/_______|/           O      x
        // (min)0        1
        vector_type corner(int i) const
        {
            value_type x = (((i & 1) != 0) ^ ((i & 2) != 0)) ? _max.x() : _min.x();
            value_type y = ((i / 2) % 2 == 0) ? _min.y() : _max.y();
            value_type z = (i < 4) ? _min.z() : _max.z();
            return vector_type(x, y, z);
        }

        //! value is subtracted from min and added to max
        void expand(value_type radius)
        {
            _min.x() -= radius; _min.y() -= radius; _min.z() -= radius;
            _max.x() += radius; _max.y() += radius; _max.z() += radius;
        }

        //! value is added to min and subtracted from max
        void contract(value_type radius) {
            _min.x() += radius; _min.y() += radius; _min.z() += radius;
            _max.x() -= radius; _max.y() -= radius; _max.z() -= radius;
        }

        void scale(value_type sx, value_type sy, value_type sz)
        {
            vector_type c = center();
            vector_type e = extents();
            e.x() *= sx; e.y() *= sy; e.z() *= sz;
            _min = c - e;
            _max = c + e;
        }

        void contain(const vector_type &v)
        {
            if (valid())
            {
                _min.x() = std::min(_min.x(), v.x());
                _min.y() = std::min(_min.y(), v.y());
                _min.z() = std::min(_min.z(), v.z());
                _max.x() = std::max(_max.x(), v.x());
                _max.y() = std::max(_max.y(), v.y());
                _max.z() = std::max(_max.z(), v.z());
            }
            else _min = _max = v;
        }

        void contain(const self_type &box)
        {
            if (!box.valid()) return;
            if (valid())
            {
                _min.x() = std::min(_min.x(), box._min.x());
                _min.y() = std::min(_min.y(), box._min.y());
                _min.z() = std::min(_min.z(), box._min.z());
                _max.x() = std::max(_max.x(), box._max.x());
                _max.y() = std::max(_max.y(), box._max.y());
                _max.z() = std::max(_max.z(), box._max.z());
            }
            else
            {
                _min = box._min;
                _max = box._max;
            }
        }

        self_type intersect(const self_type &box) const
        {
            self_type intersection(std::max(_min.x(), box._min.x()),
                                   std::max(_min.y(), box._min.y()),
                                   std::max(_min.z(), box._min.z()),
                                   std::min(_max.x(), box._max.x()),
                                   std::min(_max.y(), box._max.y()),
                                   std::min(_max.z(), box._max.z()));
            if (intersection.valid()) return intersection;
            else return self_type::empty;
        }

        bool contains(const vector_type &v) const
        {
            return (_min.x() <= v.x()) && (_min.y() <= v.y()) && (_min.z() <= v.z()) &&
                   (_max.x() >= v.x()) && (_max.y() >= v.y()) && (_max.z() >= v.z());
        }

        bool contains(const self_type &box) const
        { return contains(_min) && contains(_max); }

        bool intersects(const self_type &box) const { return intersect(box).valid(); }

        value_type distanceSquared(const vector_type &v) const
        {
            value_type dx = (v.x() < _min.x()) ? _min.x() - v.x() : (v.x() > _max.x() ? v.x() - _max.x() : 0);
            value_type dy = (v.y() < _min.y()) ? _min.y() - v.y() : (v.y() > _max.y() ? v.y() - _max.y() : 0);
            value_type dz = (v.z() < _min.z()) ? _min.z() - v.z() : (v.z() > _max.z() ? v.z() - _max.z() : 0);
            return dx * dx + dy * dy + dz * dz;
        } 

        value_type distance(const vector_type &v) const
        { return std::sqrt(distanceSquared(v)); }

        value_type signedDistance(const vector_type &v) const
        {
            if (!contains(v)) return distance(v);
            else
            {
                value_type dx = std::min(std::abs(v.x() - _min.x()), std::abs(v.x() - _max.x()));
                value_type dy = std::min(std::abs(v.y() - _min.y()), std::abs(v.y() - _max.y()));
                value_type dz = std::min(std::abs(v.z() - _min.z()), std::abs(v.z() - _max.z()));
                return -std::min(dx, std::min(dy, dz));
            }
        }

        value_type distanceSquared(const self_type &box) const
        {
            // compute lensqr( max(0, abs(center1-center2) - (extent1+extent2)) )
            value_type delta_x = std::abs((box._min.x() + box._max.x()) - (_min.x() + _max.x())) - 
                ((_max.x() - _min.x()) + (box._max.x() - box._min.x()));
            if (delta_x < 0) delta_x = 0;
            value_type delta_y = std::abs((box._min.y() + box._max.y()) - (_min.y() + _max.y())) -
                ((_max.y() - _min.y()) + (box._max.y() - box._min.y()));
            if (delta_y < 0) delta_y = 0;
            value_type delta_z = std::abs((box._min.z() + box._max.z()) - (_min.z() + _max.z())) -
                ((_max.z() - _min.z()) + (box._max.z() - box._min.z()));
            if (delta_z < 0) delta_z = 0;

            return (delta_x * delta_x + delta_y * delta_y + delta_z * delta_z) / 4;
        }

        void translate(const vector_type &t)
        { _min.add(t); _max.add(t); }

    private:
        vector_type _min, _max;
    };

    template<typename T>
    const AxisAlignedBox3<T> AxisAlignedBox3<T>::empty = AxisAlignedBox3<T>();
    template<typename T>
    const AxisAlignedBox3<T> AxisAlignedBox3<T>::zero = AxisAlignedBox3<T>(0);
    template<typename T>
    const AxisAlignedBox3<T> AxisAlignedBox3<T>::unitPositive = AxisAlignedBox3<T>(1);
    template<typename T>
    const AxisAlignedBox3<T> AxisAlignedBox3<T>::infinite = AxisAlignedBox3<T>(AxisAlignedBox3<T>::vector_type::minValue, AxisAlignedBox3<T>::vector_type::maxValue);

    typedef AxisAlignedBox3<double> AxisAlignedBox3d;
    typedef AxisAlignedBox3<float>  AxisAlignedBox3f;
    typedef AxisAlignedBox3<int>    AxisAlignedBox3i;
}

#endif
