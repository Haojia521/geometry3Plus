#ifndef G3_CURVE_ICURVE
#define G3_CURVE_ICURVE

#include <memory>
#include <vector>
#include <math/vectorTraits.h>

namespace g3
{
    template<typename T>
    class IParametricCurve3
    {
    public:
        typedef typename Vector3Traits<T>::vector_type vector_type;
        typedef typename vector_type::value_type       value_type;
        typedef IParametricCurve3<T>                   self_type;

        virtual bool isClosed() const = 0;

        virtual value_type paramLength() const = 0;
        virtual vector_type sampleT(value_type t) const = 0;
        virtual vector_type tangentT(value_type t) const = 0; // returns normalized vector

        virtual bool hasArcLength() const = 0;
        virtual value_type arcLength() const = 0;

        virtual void reverse() = 0;

        virtual std::shared_ptr<self_type> clone() const = 0;
    };

    // TODO: 需要 Segment3 类型
    template<typename T>
    class ISampledCurve3
    {
    public:
        typedef typename Vector3Traits<T>::vector_type vector_type;
        typedef typename vector_type::value_type       value_type;
        typedef ISampledCurve3<T>                      self_type;
    };

    template<typename T>
    class IParametricCurve2
    {
    public:
        typedef typename Vector2Traits<T>::vector_type vector_type;
        typedef typename vector_type::value_type       value_type;
        typedef IParametricCurve2<T>                   self_type;

        virtual bool isClosed() const = 0;

        virtual value_type paramLength() const = 0;
        virtual vector_type sampleT(vector_type t) const = 0;
        virtual vector_type tangentT(vector_type t) const = 0; // returns normalized vector

        virtual bool hasArcLength() const = 0;
        virtual value_type arcLength() const = 0;

        virtual bool isTransformable() const = 0;
        // TODO: 需要 ITransform2 类型
        //virtual void transform(const ITransform2<value_type> &trans) = 0;

        virtual std::shared_ptr<self_type> clone() const = 0;
    };

    template<typename T>
    class IMultiCurve2
    {
    public:
        typedef IMultiCurve2<T>                        self_type;
        typedef IParametricCurve2<T>                   curve_type;

        typedef std::vector<std::shared_ptr<curve_type>> curve_list;
        typedef std::vector<std::shared_ptr<const curve_type>> const_curve_list;

        virtual const const_curve_list& curves() const = 0;
    };
}

#endif
