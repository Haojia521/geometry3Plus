#ifndef G3_MATH_BOX_3
#define G3_MATH_BOX_3

#include <array>
#include <vector>

#include <math/vectorTraits.h>
#include <math/AxisAlignedBox3.h>
#include <math/quaternion.h>
#include <math/matrix3.h>

namespace g3
{
    template <typename T>
    class Box3
    {
    public:
        using vector_type = Vector3Traits<T>::vector_type;
        using value_type = typename vector_type::value_type;
        using aab3_type = AxisAlignedBox3<T>;
        using self_type = Box3<T>;

        // static values
        static const self_type empty;
        static const self_type unitZeroCentered;
        static const self_type unitPositive;
        // static functions

        // ported from WildMagic5 Wm5ContBox3.cpp::MergeBoxes
        self_type merge(const self_type &box0, const self_type &box1)
        {
            // Construct a box that contains the input boxes.
            self_type box;
            // The first guess at the box center.  This value will be updated later
            // after the input box vertices are projected onto axes determined by an
            // average of box axes.
            box.center() = (box0.center() + box1.center()) * (value_type)0.5;

            // A box's axes, when viewed as the columns of a matrix, form a rotation
            // matrix.  The input box axes are converted to quaternions.  The average
            // quaternion is computed, then normalized to unit length.  The result is
            // the slerp of the two input quaternions with t-value of 1/2.  The result
            // is converted back to a rotation matrix and its columns are selected as
            // the merged box axes.
            using quat_type = Quaternion<T>;
            using matrix_type = Matrix3<T>;

            quat_type q0, q1;
            matrix_type rot0(box0.axisX(), box0.axisY(), box0.axisZ(), true);
            q0.setFromRotationMatrix(rot0);
            matrix_type rot1(box1.axisX(), box1.axisY(), box1.axisZ(), true);
            q1.setFromRotationMatrix(rot1);
            if (q0.dot(q1) < 0) q1 = -q1;

            quat_type q = q0 + q1;
            auto invLength = (value_type)1 / std::sqrt(q.dot(q));
            q = q * invLength;
            auto q_mat = q.toRotationMatrix();
            box.axisX() = q_mat.column(0);
            box.axisY() = q_mat.column(1);
            box.axisZ() = q_mat.column(2);

            // Project the input box vertices onto the merged-box axes.  Each axis
            // D[i] containing the current center C has a minimum projected value
            // min[i] and a maximum projected value max[i].  The corresponding end
            // points on the axes are C+min[i]*D[i] and C+max[i]*D[i].  The point C
            // is not necessarily the midpoint for any of the intervals.  The actual
            // box center will be adjusted from C to a point C' that is the midpoint
            // of each interval,
            //   C' = C + sum_{i=0}^2 0.5*(min[i]+max[i])*D[i]
            // The box extents are
            //   e[i] = 0.5*(max[i]-min[i])

            // TODO: may be optimized by using Lambda expression
            vector_type pmin, pmax;
            auto vertices0 = box0.computeVertices();
            for (const auto &v : vertices0)
            {
                auto diff = v - box.center();
                for (int i = 0; i < 3; ++i)
                {
                    auto dotValue = box.axis(i).dot(diff);
                    if (dotValue > pmax[i]) pmax[i] = dotValue;
                    else if (dotValue < pmin[i]) pmin[i] = dotValue;
                }
            }
            auto vertices1 = box1.computeVertices();
            for (const auto &v : vertices1)
            {
                auto diff = v - box.center();
                for (int i = 0; i < 3; ++i)
                {
                    auto dotValue = box.axis(i).dot(diff);
                    if (dotValue > pmax[i]) pmax[i] = dotValue;
                    else if (dotValue < pmin[i]) pmin[i] = dotValue;
                }
            }

            // [min,max] is the axis-aligned box in the coordinate system of the
            // merged box axes.  Update the current box center to be the center of
            // the new box.  Compute the extents based on the new center.
            for (int i = 0; i < 3; ++i)
            {
                box.center() = box.center() + ((pmax[i] + pmin[i]) * (value_type)0.5) * box.axis(i);
                box.extent()[i] = (pmax[i] - pmin[i]) * (value_type)0.5;
            }

            return box;
        }

        // constructors
        Box3(const vector_type &center) : _center(center),
            _axisX(vector_type::axisX), _axisY(vector_type::axisY), _axisZ(vector_type::axisZ)
            _extent(vector_type::zero) {}

        Box3(const vector_type &center, 
            const vector_type &x, const vector_type &y, const vector_type &z, 
            const vector_type &extent) : _center(center), _axisX(x), _axisY(y), _axisZ(z), _extent(extent) {}

        Box3(const vector_type &center, const vector_type &extent) : _center(center), _extent(extent),
            _axisX(vector_type::axisX), _axisY(vector_type::axisY), _axisZ(vector_type::axisZ) {}

        Box3(const aab3_type &aab) : _axisX(vector_type::axisX), _axisY(vector_type::axisY), _axisZ(vector_type::axisZ)
        {
            _extent = aab.extents() * (value_type)0.5;
            _center = aab.center();
        }

        // TODO: add constructor that uses segment3 as parameter
        // type conversion
        template <typename U>
        operator Box3<U>() const
        {
            return Box3<U>(static_cast<typename Box3<U>::vector_type>(_center),
                           static_cast<typename Box3<U>::vector_type>(_axisX),
                           static_cast<typename Box3<U>::vector_type>(_axisY),
                           static_cast<typename Box3<U>::vector_type>(_axisZ),
                           static_cast<typename Box3<U>::vector_type>(_extent));
        }
        // functions
        vector_type  center() const { return _center; }
        vector_type  extent() const { return _extent; }
        vector_type  axisX() const { return _axisX; }
        vector_type  axisY() const { return _axisY; }
        vector_type  axisZ() const { return _axisZ; }
        vector_type& center() { return _center; }
        vector_type& extent() { return _extent; }
        vector_type& axisY() { return _axisY; }
        vector_type& axisX() { return _axisX; }
        vector_type& axisZ() { return _axisZ; }

        vector_type axis(int i) const
        { return ((i == 0) ? _axisX : (i == 1) ? _axisY : _axisZ); }

        std::array<vector_type, 8> computeVertices() const
        {
            std::array<vector_type, 8> verts;
            computeVertices(verts);
            return verts;
        }

        void computeVertices(std::array<vector_type, 8> &verts) const
        {
            auto extAxis0 = _axisX * _extent.x();
            auto extAxis1 = _axisY * _extent.y();
            auto extAxis2 = _axisZ * _extent.z();
            verts[0] = _center - extAxis0 - extAxis1 - extAxis2;
            verts[1] = _center + extAxis0 - extAxis1 - extAxis2;
            verts[2] = _center + extAxis0 + extAxis1 - extAxis2;
            verts[3] = _center - extAxis0 + extAxis1 - extAxis2;
            verts[4] = _center - extAxis0 - extAxis1 + extAxis2;
            verts[5] = _center + extAxis0 - extAxis1 + extAxis2;
            verts[6] = _center + extAxis0 + extAxis1 + extAxis2;
            verts[7] = _center - extAxis0 + extAxis1 + extAxis2;
        }

        aab3_type toAABB() const
        {
            auto verts = computeVertices();
            aab3_type result(verts[0]);
            for (int i = 1; i < 8; ++i) result.contain(verts[i]);
            return result;
        }

        // corners [ (-x,-y), (x,-y), (x,y), (-x,y) ], -z, then +z
        //
        //   7---6     +z       or        3---2     -z
        //   |\  |\                       |\  |\
        //   4-\-5 \                      0-\-1 \
        //    \ 3---2                      \ 7---6   
        //     \|   |                       \|   |
        //      0---1  -z                    4---5  +z
        //
        // Note that in RHS system (which is our default), +z is "forward" so -z in this diagram 
        // is actually the back of the box (!) This is odd but want to keep consistency w/ ComputeVertices(),
        // and the implementation there needs to stay consistent w/ C++ Wildmagic5
        vector_type corner(int i) const
        {
            auto c = _center;
            c = c + (((i & 1) != 0) ^ ((i & 2) != 0)) ? (_axisX * _extent.x()) : (_axisX * (-_extent.x()));
            c = c + ((i / 2) % 2 == 0) ? (_axisY * (-_extent.y())) : (_axisY * _extent.y());
            c = c + (i < 4) ? (_axisZ * (-_extent.z())) : (_axisZ * _extent.z());
            return c;
        }

        value_type maxExtent() const
        { return std::max(_extent.x(), std::max(_extent.y(), _extent.z())); }

        value_type minExtent() const
        { return std::min(_extent.x(), std::min(_extent.y(), _extent.z())); }

        vector_type diagonal() const
        {
            auto extAxis0 = _axisX * _extent.x();
            auto extAxis1 = _axisY * _extent.y();
            auto extAxis2 = _axisZ * _extent.z();
            return (extAxis0 + extAxis1 + extAxis2) - (-extAxis0 - extAxis1 - extAxis2);
        }

        value_type volume() const
        { return _extent.x() * _extent.y() * _extent.z() * 8; }

        void contain(const vector_type &v)
        {
            auto lv = v - _center;
            for (int i = 0; i < 3; ++i)
            {
                auto t - lv.dot(axis(i));
                if (std::abs(t) > _extent[i])
                {
                    auto min = -_extent[i], max = _extent[i];
                    if (t < min) min = t;
                    else if (t > max) max = t;
                    _extent[i] = (max - min) * (value_type)0.5;
                    _center = _center + ((max + min) * (value_type)0.5) * axis(i);
                }
            }
        }

        // update the box to contain set of input points.More efficient tha ncalling Contain() many times
        // code ported from GTEngine GteContOrientedBox3.h 
        void contain(const std::vector<vector_type> &points)
        {
            // Let C be the box center and let U0, U1, and U2 be the box axes.
            // Each input point is of the form X = C + y0*U0 + y1*U1 + y2*U2.
            // The following code computes min(y0), max(y0), min(y1), max(y1),
            // min(y2), and max(y2).  The box center is then adjusted to be
            //   C' = C + 0.5*(min(y0)+max(y0))*U0 + 0.5*(min(y1)+max(y1))*U1 + 0.5*(min(y2)+max(y2))*U2
            if (points.empty()) return;
            auto citr = points.cbegin();
            auto citr_end = points.cend();

            auto diff = (*citr) - _center;
            auto pmin = vector_type(diff.dot(_axisX), diff.dot(_axisY), diff.dot(_axisZ));
            auto pmax = pmin;
            ++citr;
            for (; citr != citr_end; ++citr)
            {
                diff = (*citr) - _center;

                auto dotx = diff.dot(_axisX);
                if (dotx < pmin[0]) pmin[0] = dotx;
                else if (dotx > pmax[0]) pmax[0] = dotx;

                auto doty = diff.dot(_axisY);
                if (doty < pmin[1]) pmin[1] = doty;
                else if (doty > pmax[1]) pmax[1] = doty;

                auto dotz = diff.dot(_axisZ);
                if (dotz < pmin[2]) pmin[2] = dotz;
                else if (dotz > pmax[2]) pmax[2] = dotz;
            }
            for (int i = 0; i < 3; ++i)
            {
                _center = _center + (((value_type)0.5) * (pmin[i] + pmax[i])) * axis(i);
                _extent[i] = ((value_type)0.5) * (pmax[i] - pmin[i]);
            }
        }

        void contain(const self_type &box)
        {
            auto verts = box.computeVertices();
            for (const auto &v : verts) contain(v);
        }

        bool contains(const vector_type &v) const
        {
            auto lv = v - _center;
            return (std::abs(lv.dot(_axisX)) <= _extent.x()) &&
                   (std::abs(lv.dot(_axisY)) <= _extent.y()) &&
                   (std::abs(lv.dot(_axisZ)) <= _extent.z());
        }

        void expand(value_type f)
        { _extent = _extent + f; }

        void translate(const vector_type &t)
        { _center = _center + t; }

        void scale(const vector_type &s)
        {
            _center = _center * s;
            _extent = _extent * s;
            _axisX = _axisX * s; _axisX.normalize();
            _axisY = _axisY * s; _axisY.normalize();
            _axisZ = _axisZ * s; _axisZ.normalize();
        }

        void scaleExtent(const vector_type &s)
        { _extent = _extent * s; }

        // Returns distance to box, or 0 if point is inside box.
        // Ported from WildMagic5 Wm5DistPoint3Box3.cpp
        value_type distanceSquared(const vector_type &v) const
        {
            // Work in the box's coordinate system.
            auto vv = v - _center;
            // Compute squared distance on box.
            auto sqrDistance = value_type(0);
            for (int i = 0; i < 3; ++i)
            {
                auto delta = value_type(0);
                auto closestValue = axis(i).dot(vv);
                if (closestValue < -_extent[i]) delta = closestValue + _extent[i];
                else if (closestValue > _extent[i]) delta = closestValue - _extent[i];
                sqrDistance += delta * delta;
            }
            return sqrDistance;
        }

        // Returns closest point to box, or center if point is inside box.
        // Ported from WildMagic5 Wm5DistPoint3Box3.cpp (GetSquared())
        vector_type closestPoint(const vector_type &v)
        {
            // Work in the box's coordinate system.
            auto vv = v - _center;
            // Compute closest point on box.
            vector_type closest;
            for (int i = 0; i < 3; ++i)
            {
                auto value = axis(i).dot(vv);
                if (value < -_extent[i]) closest[i] = -_extent[i];
                else if (value > _extent[i]) closest[i] = _extent[i];
            }
            return (_center + _axisX * closest.x() + _axisY * closest.y() + _axisZ * closest.z());
        }
        // operator functions

    private:
        vector_type _center;
        vector_type _axisX, _axisY, _axisZ;
        vector_type _extent;
    };
}

#endif
