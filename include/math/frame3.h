#ifndef G3_MATH_FRAME_3
#define G3_MATH_FRAME_3

#include <math/quaternion.h>

namespace g3
{
    template<typename T>
    class Frame3
    {
    public:
        using vector_type = typename Vector3Traits<T>::vector_type;
        using vector2_type = typename Vector2Traits<T>::vector_type;
        using value_type = typename vector_type::value_type;
        using quat_type = Quaternion<value_type>;
        using matrix_type = Matrix3<value_type>;
        using self_type = Frame3<T>;

        // static values

        // static functions

        // Interpolate between two frames - Lerp for origin, Slerp for rotation
        static self_type interpolate(const self_type &f1, const self_type &f2, value_type t)
        {
            return self_type(vector_type::lerp(f1.origin(), f2.origin()),
                quat_type::slerp(f1.rotation(), f2.rotation(), t));
        }

        // finds minimal rotation that aligns source frame with axes of target frame.
        // considers all signs
        //   1) find smallest angle(axis_source, axis_target), considering all sign permutations
        //   2) rotate source to align axis_source with sign*axis_target
        //   3) now rotate around alined_axis_source to align second-best pair of axes
        static self_type sovleMinRotation(const self_type &source, const self_type &target)
        {
            int best_i = -1, best_j = -1;
            value_type maxAbsDot = 0, maxSign = 0;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                {
                    auto d = source.getAxis(i).dot(target.getAxis(j));
                    auto a = std::abs(d);
                    if (a > maxAbsDot)
                    {
                        maxAbsDot = a;
                        maxSign = std::signbit(d) ? -1 : 1;
                        best_i = i;
                        best_j = j;
                    }
                }

            self_type R1 = source.rotated(quat_type::fromTo(source.getAxis(best_i), target.getAxis(best_j) * maxSign));
            vector_type vAround = R1.getAxis(best_i);

            int second_i = -1, second_j = -1;
            value_type secondDot = 0, secondSign = 0;
            for (int i = 0; i < 3; ++i)
            {
                if (i == best_i) continue;
                for (int j = 0; j < 3; ++j)
                {
                    if (j == best_j) continue;
                    auto d = R1.getAxis(i).dot(target.getAxis(j));
                    auto a = std::abs(d);
                    if (a > secondDot)
                    {
                        secondDot = a;
                        secondSign = std::signbit(d) ? -1 : 1;
                        second_i = i;
                        second_j = j;
                    }
                }
            }

            R1.constrainedAlignAxis(second_i, target.getAxis(second_j) * secondSign, vAround);
            return R1;
        }

        // constructors
        Frame3(const vector_type &o) : _rotation(quat_type::indentity), _origin(o)
        {}

        Frame3(const vector_type &origin, const vector_type &setZ) :
            _origin(origin)
        {
            _rotation = quat_type::setFromTo(vector_type::axisZ, setZ);
        }

        Frame3(const vector_type &origin, const vector_type &setAxis, int nAxis) :
            _origin(origin)
        {
            vector_type originAxis;
            if (nAxis == 0) originAxis = vector_type::axisX;
            else if (nAxis == 1) originAxis = vector_type::axisY;
            else originAxis = vector_type::axisZ;
            _rotation = quat_type::setFromTo(originAxis, setAxis);
        }

        Frame3(const vector_type &origin, const quat_type &rotation) :
            _origin(origin), _rotation(rotation)
        {}

        Frame3(const vector_type &origin,
               const vector_type &x, const vector_type &y, const vector_type &z) : 
            _origin(oringin)
        {
            matrix_type mat(x, y, z, true);
            _rotation = quat_type(mat);
        }

        // type conversion
        template<typename U>
        operator Frame3<U>() const
        {
            return Frame3<U>(static_cast<typename Frame3::vector_type>(_origin),
                             static_cast<typename Frame3<U>::quat_type>(_rotation));
        }

        // functions
        const quat_type& rotation() const
        { return _rotation; }
        quat_type& rotation()
        { return _rotation; }

        const vector_type& origin() const
        { return _origin; }
        vector_type& origin()
        { return _origin; }

        vector_type x() const
        { return _rotation.axisX(); }

        vector_type y() const
        { return _rotation.axisY(); }

        vector_type z() const
        { return _rotation.axisZ(); }

        vector_type getAxis(int nAxis) const
        {
            if (nAxis == 0) return _rotation * vector_type::axisX;
            else if (nAxis == 1) return _rotation * vector_type::axisY;
            else return _rotation * vector_type::axisZ;
        }

        void translate(const vector_type &v)
        { _origin = _origin + v; }

        self_type translated(const vector_type &v) const
        { return self_type(_origin + v, _rotation); }

        self_type translated(value_type dis, int nAxis) const
        { return self_type(_origin + dis * getAxis(nAxis), _rotation); }

        void scale(value_type s)
        { _origin = _origin * s; }

        void scale(const vector_type &sv)
        { _origin = _origin * sv; }

        self_type scaled(value_type s) const
        { return self_type(_origin * s, _rotation); }

        self_type scaled(const vector_type &sv)
        { return self_type(_origin * sv, _rotation); }

        void rotate(const quat_type &q)
        { _rotation = q * _rotation; }

        self_type rotated(const quat_type &q) const
        { return self_type(_origin, q * _rotation); }

        self_type rotated(value_type angel, int nAxis, bool isDeg = true) const
        { return rotated(quat_type(getAxis(nAxis), nAxis, isDeg)); }

        // this rotates the frame around its own axes, rather than around the world axes,
        // which is what Rotate() does. So, RotateAroundAxis(AxisAngleD(Z,180)) is equivalent
        // to Rotate(AxisAngleD(My_AxisZ,180)). 
        void rotateAroundAxes(const quat_type &q)
        { _rotation = _rotation * q; }

        void rotateAround(const vector_type &point, const quat_type &q)
        {
            auto dv = q * (_origin - point);
            _rotation = q * _rotation;
            _origin = point + dv;
        }

        self_type rotatedAround(const vector_type &point, const quat_type &q) const
        {
            auto dv = q * (_origin - point);
            return self_type(point + dv, q * _rotation);
        }

        void alignAxis(int nAxis, const vector_type &vTo)
        {
            auto rot = quat_type::setFromTo(getAxis(nAxis), vTo);
            rotate(rot);
        }

        void constrainedAlignAxis(int nAxis, const vector_type &vTo, const vector_type &vAround)
        {
            auto axis = getAxis(nAxis);
            auto angleD = mathUtil::planeAngleSignedD(axis, vTo, vAround);
            auto rot = quat_type::axisAngleDeg(vAround, angleD);
            rotate(rot);
        }

        //3D projection of point p onto frame-axis plane orthogonal to normal axis
        vector_type projectToPlane(const vector_type &p, inr nNormal) const
        {
            auto d = p - _origin;
            auto n = getAxis(nNormal);
            return _origin + (d - d.dot(n) * n);
        }

        // map from 2D coordinates in frame-axes plane perpendicular to normal axis, to 3D
        // [TODO] check that mapping preserves orientation?
        vector_type fromPlaneUV(const vector2_type &v, int nPlaneNormalAxis) const
        {
            vector_type dv
            if (nPlaneNormalAxis == 0) dv.set(0, v[1], v[0]);
            else if (nPlaneNormalAxis == 1) dv.set(v[0], 0, v[1]);
            else dv.set(v[0], v[1], 0);
            return _rotation * dv + _origin;
        }

        // Project p onto plane axes
        // [TODO] check that mapping preserves orientation?
        vector2_type toPlaneUV(const vector_type &p, int nNormal) const
        {
            int nAxis[2];
            if (nNormal == 0) { nAxis[0] = 2; nAxis[1] = 1; }
            else if (nNormal == 1) { nAxis[0] = 0; nAxis[1] = 2; }
            else { nAxis[0] = 0; nAxis[1] = 1; }
            auto d = p - _origin;
            auto fu = d.dot(getAxis(nAxis[0]));
            auto fv = d.dot(getAxis(nAxis[1]));
            return vector2_type(fu, fv);
        }

        value_type distanceToPlaneSigned(const vector_type &p, int nNormal) const
        { return (p - _origin).dot(getAxis(nNormal)); }

        value_type distanceToPlane(const vector_type &p, int nNormal) const
        { return std::abs(distanceToPlaneSigned(p, nNormal)); }

        // Map point *into* local coordinates of Frame
        vector_type toFrameP(const vector_type &p) const
        {
            auto tem = p - _origin;
            return _rotation.inverseMultiply(tem);
        }

        // Map point *from* local frame coordinates into "world" coordinates
        vector_type fromFrameP(const vector_type &p) const
        { return _rotation * p + _origin; }

        // Map vector *into* local coordinates of Frame
        vector_type toFrameV(const vector_type &v) const
        { eturn _rotation.inverseMultiply(v); }

        // Map vector *from* local frame coordinates into "world" coordinates
        vector_type fromFrameV(const vector_type &v) const
        { return _rotation * v; }

        // Map quaternion *into* local coordinates of Frame
        quat_type toFrame(const quat_type &q) const
        { return quat_type::inverse(_rotation) * q; }

        // Map quaternion *from* local frame coordinates into "world" coordinates
        quat_type fromFrame(const quat_type &q) const
        { return _rotation * q; }

        // TODO: Ray3
        // 

        // TODO: Box3
        //

        // Map frame *into* local coordinates of Frame
        self_type toFrame(const self_type &f) const
        { return self_type(toFrameP(f.origin()), toFrame(f.rotation())); }

        // Map frame *from* local frame coordinates into "world" coordinates
        self_type fromFrame(const self_type &f) const
        { return self_type(fromFrameP(f.origin()), fromFrame(f.rotation())); }

        // Compute intersection of ray with plane passing through frame origin, normal
        // to the specified axis. 
        // If the ray is parallel to the plane, no intersection can be found, and
        // we return Vector3::invalid
        vector_type rayPlaneIntersection(const vector_type &rayOrigin, const vector_type &rayDirection, int nAxisAsNormal) const
        {
            auto N = getAxis(nAxisAsNormal);
            auto d = -vector_type::dot(_origin, N);
            auto div = vector_type::dot(rayDirection, N);
            if (std::abs(div) <= mathUtil::getZeroTolerance<value_type>())
                return vector_type::invalid;
            auto t = -(vector_type::dot(rayOrigin, N) + d) / div;
            return rayOrigin + rayDirection * t;
        }

        bool epsilonEqual(const self_type &f, value_type eps)
        { return _origin.epsilonEqual(f.origin(), eps) && _rotation.epsilonEqual(f.rotation(), eps); }



    private:
        vector_type _origin;
        quat_type _rotation;
    };
}

#endif
