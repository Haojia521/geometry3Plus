#ifndef G3_TEST_MATH_AXIS_ALIGNED_BOX_2
#define G3_TEST_MATH_AXIS_ALIGNED_BOX_2

#include <math/AxisAlignedBox2.h>

#include "util.h"

using namespace g3;
namespace g3test
{
    void testAAB2_constructor()
    {
        Vector2d vd1(-4.5, -6.5), vd2(10.5, 9.5);

        AxisAlignedBox2d aab2d1;
        AxisAlignedBox2d aab2d2(-1.0, -2.0, 2.0, 2.0);
        AxisAlignedBox2d aab2d3(5.0);
        AxisAlignedBox2d aab2d4(4.0, 5.5);
        AxisAlignedBox2d aab2d5(vd1, vd2);
        AxisAlignedBox2d aab2d6(vd2, 1.0, 1.5);
        AxisAlignedBox2d aab2d7(vd2, 2.0);
        AxisAlignedBox2d aab2d8(vd2);
        AxisAlignedBox2d aab2d9(aab2d2);
        printAAB2(aab2d1, "aab2d1");
        printAAB2(aab2d2, "aab2d2");
        printAAB2(aab2d3, "aab2d3");
        printAAB2(aab2d4, "aab2d4");
        printAAB2(aab2d5, "aab2d5");
        printAAB2(aab2d6, "aab2d6");
        printAAB2(aab2d7, "aab2d7");
        printAAB2(aab2d8, "aab2d8");
        printAAB2(aab2d9, "aab2d9");

        Vector2f vf1(-4.5, -6.5), vf2(10.5, 9.5);
        AxisAlignedBox2f aab2f1;
        AxisAlignedBox2f aab2f2(-1.0f, -2.0f, 2.0f, 2.0f);
        AxisAlignedBox2f aab2f3(5.0f);
        AxisAlignedBox2f aab2f4(4.0f, 5.5f);
        AxisAlignedBox2f aab2f5(vf1, vf2);
        AxisAlignedBox2f aab2f6(vf2, 1.0f, 1.5f);
        AxisAlignedBox2f aab2f7(vf2, 2.0f);
        AxisAlignedBox2f aab2f8(vf2);
        AxisAlignedBox2f aab2f9(aab2f2);
        printAAB2(aab2f1, "aab2f1");
        printAAB2(aab2f2, "aab2f2");
        printAAB2(aab2f3, "aab2f3");
        printAAB2(aab2f4, "aab2f4");
        printAAB2(aab2f5, "aab2f5");
        printAAB2(aab2f6, "aab2f6");
        printAAB2(aab2f7, "aab2f7");
        printAAB2(aab2f8, "aab2f8");
        printAAB2(aab2f9, "aab2f9");

        aab2d9 = aab2f9;
        printAAB2(aab2d9, "aab2d9 = aab2f9");
        aab2f9 = aab2d3;
        printAAB2(aab2f9, "aab2f9 = aab2d3");
    }

    void testAAB2_constFunctions()
    {
        AxisAlignedBox2d aab2d(-2.0, -2.0, 2.0, 2.0);

        Vector2d v2d1(1.0, 1.0), v2d2(3.0, 3.0), v2d3(3.0, 1.0), v2d4(1.0, 2.5);

        std::cout << " -> contains(v2d1) : " << aab2d.contains(v2d1) << std::endl;
        std::cout << " -> contains(v2d2) : " << aab2d.contains(v2d2) << std::endl;

        std::cout << " -> distance(v2d3) : " << aab2d.distance(v2d3) << std::endl;
        std::cout << " -> distance(v2d4) : " << aab2d.distance(v2d4) << std::endl;

        AxisAlignedBox2d aab2d1(4.0, 4.0, 6.0, 6.0);
        std::cout << " -> intersects(aab2d1) : " << aab2d.intersects(aab2d1) << std::endl;
        aab2d1.contain(Vector2d(1.0, 1.0));
        std::cout << " -> intersects(aab2d1) : " << aab2d.intersects(aab2d1) << std::endl;

        AxisAlignedBox2d intersection = aab2d.intersect(aab2d1);
        printAAB2Simple(intersection, "intersection");
    }

    void testAAB2_nonConstFunctions()
    {
        AxisAlignedBox2d aab2d(-1.0, -2.0, 2.0, 2.0);

        aab2d.expand(1.0);
        printAAB2Simple(aab2d, "expend(1.0)");
        aab2d.contract(1.0);
        printAAB2Simple(aab2d, "contract(1.0)");
        aab2d.add(0.5, 1.0, 2.0, 0.5);
        printAAB2Simple(aab2d, "add(0.5, 1.0, 2.0, 0.5)");
        aab2d.setWidth(5.5, AxisAlignedBox2d::ScaleLeft);
        printAAB2Simple(aab2d, "setWidth(5.5, AxisAlignedBox2d::ScaleLeft)");
        aab2d.setWidth(6.5, AxisAlignedBox2d::ScaleRight);
        printAAB2Simple(aab2d, "setWidth(6.5, AxisAlignedBox2d::ScaleRight)");
        aab2d.setWidth(4.0, AxisAlignedBox2d::ScaleCenter);
        printAAB2Simple(aab2d, "setWidth(4.0, AxisAlignedBox2d::ScaleCenter)");
        aab2d.setHeight(6.0, AxisAlignedBox2d::ScaleUp);
        printAAB2Simple(aab2d, "setHeight(6.0, AxisAlignedBox2d::ScaleUp)");
        aab2d.setHeight(4.0, AxisAlignedBox2d::ScaleDown);
        printAAB2Simple(aab2d, "setHeight(4.0, AxisAlignedBox2d::ScaleDown");
        aab2d.setHeight(8.0, AxisAlignedBox2d::ScaleCenter);
        printAAB2Simple(aab2d, "setHeight(4.0, AxisAlignedBox2d::ScaleDown");
    }

    void testAAB2_nonConstFunctions2()
    {
        AxisAlignedBox2d aab2d(-1.0, -2.0, 2.0, 2.0);
        Vector2d v2d1(3.0, 1.0), v2d2(2.5, 4.0);

        aab2d.contain(v2d1);
        printAAB2Simple(aab2d, "contain(v2d1)");
        aab2d.contain(v2d2);
        printAAB2Simple(aab2d, "contain(v2d2)");

        AxisAlignedBox2d aab2d2(6.0, 8.0, 10.0, 12.0);
        aab2d.contain(aab2d2);
        printAAB2Simple(aab2d, "contain(aab2d2)");

        aab2d.translate(v2d1);
        printAAB2Simple(aab2d, "translate(v2d1)");

        aab2d.scale(2.0);
        printAAB2Simple(aab2d, "scale(2.0)");
        aab2d.scale(2.0, Vector2d(1.0, 1.0));
        printAAB2Simple(aab2d, "scale(2.0, Vector2d(1.0, 1.0))");
    }
}

#endif
