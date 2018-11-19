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

        const vector_type& origion() const
        { return _origin; }
        vector_type& origion()
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



    private:
        vector_type _origin;
        quat_type _rotation;
    };
}

#endif
