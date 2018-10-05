#ifndef G3_MATH_TRANSFORM_SEQUENCE_2
#define G3_MATH_TRANSFORM_SEQUENCE_2

#include <memory>
#include <vector>
#include <math/vectorTraits.h>
#include <math/vectorTuple.h>
#include <math/matrix2.h>
#include <math/mathUtil.h>

namespace g3
{
    template<typename T>
    class ITransform2
    {
    public:
        using self_type   = ITransform2<T>;
        using vector_type = typename Vector2Traits<T>::vector_type;
        using value_type  = typename vector_type::value_type;

        // Apply transforms to point
        virtual vector_type transformP(const vector_type &p) const = 0;
        // Apply transforms to normalized vector
        virtual vector_type transformN(const vector_type &n) const = 0;
        // Apply transforms to scalar dimension
        virtual value_type transformScalar(value_type s) const = 0;
    };

    template<typename T>
    class TransformSequence2 : public ITransform2<T>
    {
    public:
        using base_type   = ITransform2<T>;
        using self_type   = TransformSequence2<T>;
        using vector_type = typename base_type::vector_type;
        using value_type  = typename base_type::value_type;

        enum class XFormType
        {
            TRANSLATION = 0,
            ROTATION = 1,
            ROTATE_AROUND_POINT = 2,
            SCALE = 3,
            SCALE_AROUND_POINT = 4,

            NESTED_ITRANSFORM2 = 10
        };

        struct XForm
        {
            using tuple_type  = typename VectorTupleTrait<vector_type, 2>::tuple_type;
            using matrix_type = Matrix2<value_type>;

            // public member values
            XFormType type;
            tuple_type data;
            std::shared_ptr<base_type> xform;

            // type conversion

            // functions
            // may need to update these to handle other types...
            vector_type translation() const
            { return std::get<0>(data); }

            vector_type scale() const
            { return std::get<0>(data); }

            matrix_type rotation() const
            { return matrix_type(std::get<0>(data).x(), false); }

            vector_type rotateOrigin() const
            { return std::get<1>(data); }

            bool scaleIsUniform() const
            {
                const auto &v0 = std::get<0>(data);
                const auto &v1 = std::get<1>(data);
                return v0.epsilonEqual(v1, mathUtil::getEpsilon<value_type>());
            }

            std::shared_ptr<base_type> nestedITransform2() const
            { return xform; }
        };

        TransformSequence2() {}

        // type conversion

        // functions
        self_type& translation(const vector_type &v)
        {
            XForm xform;
            xform.type = XFormType::TRANSLATION;
            xform.data = std::make_tuple(v, vector_type::zero);
            operations.push_back(xform);

            return *this;
        }

        self_type& translation(value_type dx, value_type dy)
        {
            XForm xform;
            xform.type = XFormType::TRANSLATION;
            xform.data = std::make_tuple(vector_type(dx, dy), vector_type::zero);
            operations.push_back(xform);

            return *this;
        }

        self_type& rotationRad(value_type angle)
        {
            XForm xform;
            xform.type = XFormType::ROTATION;
            xform.data = std::make_tuple(vector_type(angle, 0), vector_type::zero);
            operations.push_back(xform);

            return *this;
        }

        self_type& rotationDeg(value_type angle)
        {
            return rotationRad(angle * mathUtil::getDeg2Rad<value_type>());
        }

        self_type& rotationRad(value_type angle, const vector_type &aroundPt)
        {
            XForm xform;
            xform.type = XFormType::ROTATE_AROUND_POINT;
            xform.data = std::make_tuple(vector_type(angle, 0), aroundPt);
            operations.push_back(xform);

            return *this;
        }

        self_type& rotationDeg(value_type angle, const vector_type &aroundPt)
        {
            return rotationRad(angle * mathUtil::getDeg2Rad<value_type>(), aroundPt);
        }

        self_type& scale(const vector_type &s)
        {
            XForm xform;
            xform.type = XFormType::SCALE;
            xform.data = typename XForm::tuple_type(s, vector_type::zero);
            operations.push_back(xform);

            return *this;
        }

        self_type& scale(const vector_type &s, const vector_type &aroundPt)
        {
            XForm xform;
            xform.type = XFormType::SCALE_AROUND_POINT;
            xform.data = typename xform::tuple_type(s, aroundPt);
            operations.push_back(xform);

            return *this;
        }

        self_type& append(std::shared_ptr<base_type> t2)
        {
            XForm xform;
            xform.type = XFormType::NESTED_ITRANSFORM2;
            xform.xform = t2;
            operations.push_back(xform);

            return *this;
        }

        vector_type transformP(const vector_type &p) const override
        {
            auto r = p;
            for (const auto &op : operations)
            {
                switch (op.type)
                {
                case XFormType::TRANSLATION:
                    r = r + op.translation();
                    break;

                case XFormType::ROTATION:
                    r = op.rotation() * r;
                    break;

                case XFormType::ROTATE_AROUND_POINT:
                    r = r - op.rotateOrigin();
                    r = op.rotation() * r;
                    r = r + op.rotateOrigin();
                    break;

                case XFormType::SCALE:
                    r = r * op.scale();
                    break;

                case XFormType::SCALE_AROUND_POINT:
                    r = r - op.rotateOrigin();
                    r = r * op.scale();
                    r = r + op.rotateOrigin();
                    break;

                case XFormType::NESTED_ITRANSFORM2:
                    r = op.nestedITransform2()->transformP(r);
                    break;

                default:
                    // TO UPDATE: 是否需要报错（抛出异常）
                    break;
                }
            }

            return r;
        }

        vector_type transformN(const vector_type &n) const override
        {
            auto r = n;
            for (const auto &op : operations)
            {
                switch (op.type)
                {
                case XFormType::TRANSLATION:
                    break;

                case XFormType::ROTATION:
                case XFormType::ROTATE_AROUND_POINT:
                    r = op.rotation() * r;
                    break;

                case XFormType::SCALE:
                case XFormType::SCALE_AROUND_POINT:
                    // TO UPDATE: 当前没有判断 op.scaleUniform() 是否为真
                    r = r * op.scale();

                case XFormType::NESTED_ITRANSFORM2:
                    r = op.nestedITransform2()->transformN(r);
                    break;

                default:
                    // TO UPDATE: 是否需要报错（抛出异常）
                    break;
                }
            }

            return r;
        }

        value_type transformScalar(value_type s) const override
        {
            auto r = s;
            for (const auto &op : operations)
            {
                switch (op.type)
                {
                case XFormType::TRANSLATION:
                case XFormType::ROTATION:
                case XFormType::ROTATE_AROUND_POINT:
                    break;

                case XFormType::SCALE:
                case XFormType::SCALE_AROUND_POINT:
                    // TO UPDATE: 当前没有判断 op.scaleUniform() 是否为真
                    r = r * op.scale().x();
                    break;

                case XFormType::NESTED_ITRANSFORM2:
                    r = op.nestedITransform2()->transformScalar(r);
                    break;

                default:
                    // TO UPDATE: 是否需要报错（抛出异常）
                    break;
                }
            }

            return r;
        }

    private:

        std::vector<XForm> operations;
    };

    template<typename T>
    inline std::shared_ptr<ITransform2<T>> asITransform2(std::shared_ptr<TransformSequence2<T>> ts)
    {
        return std::dynamic_pointer_cast<ITransform2<T>>(ts);
    }

    using TransformSequence2d = TransformSequence2<double>;
    using TransformSequence2f = TransformSequence2<float>;
}

#endif
