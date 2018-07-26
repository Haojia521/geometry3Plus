#ifndef G3_TEST_MATH_TRANSFORM_SEQUENCE_2
#define G3_TEST_MATH_TRANSFORM_SEQUENCE_2

#include <math/transformSequence2.h>

#include "util.h"

using namespace g3;

namespace g3test
{
    void testTransformSequence2_typeConversion()
    {
        Vector2d v2d1(1, 2);
        Vector2f v2f1(3, 4);

        TransformSequence2d ts2d;
        ts2d.translation(v2d1).translation(v2f1);

        Vector2d v2d2(5, 5);
        auto transResult = ts2d.transformP(v2d2);
        printVector2(transResult, "trans result");

        Vector2f v2f2(1.3f, 3.2f);
        TransformSequence2f ts2f;
        ts2f.translation(v2f1).translation(v2f2).transformP(v2d1);
        auto transResult2 = ts2f.transformP(v2d2);
        printVector2(transResult2, "trans result 2");

        //ts2d = ts2f;
        //auto transResult3 = ts2d.transformP(v2d2);
        //printVector2(transResult3, "trans result 3");

        TransformSequence2d::XForm ts2dXF;
        ts2dXF.type = TransformSequence2d::XFormType::SCALE;
        TransformSequence2f::XForm ts2fXF;

        ts2fXF = ts2dXF;
    }
}

#endif
