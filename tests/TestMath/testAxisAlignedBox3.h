#ifndef G3_TEST_MATH_AXIS_ALIGNED_BOX_3
#define G3_TEST_MATH_AXIS_ALIGNED_BOX_3

#include <math/AxisAlignedBox3.h>

#include "util.h"

using namespace g3;

namespace g3test
{
    void testAAB3_constructor()
    {
        Vector3d vd1(-1.0, -2.0, -3.0), vd2(2.0, 3.0, 4.0);

        AxisAlignedBox3d aab3d1;
        AxisAlignedBox3d aab3d2(-0.5, -1.0, -0.5, 1.0, 0.5, 1.0);
        AxisAlignedBox3d aab3d3(2.5);
        AxisAlignedBox3d aab3d4(1.5, 2.5, 3.5);
        AxisAlignedBox3d aab3d5(vd1, vd2);
        AxisAlignedBox3d aab3d6(vd2, 1.0, 2.0, 1.0);
        AxisAlignedBox3d aab3d7(vd2, 2.0);
        AxisAlignedBox3d aab3d8(vd2);
        AxisAlignedBox3d aab3d9(aab3d2);
        printAAB3(aab3d1, "aab3d1");
        printAAB3(aab3d2, "aab3d2");
        printAAB3(aab3d3, "aab3d3");
        printAAB3(aab3d4, "aab3d4");
        printAAB3(aab3d5, "aab3d5");
        printAAB3(aab3d6, "aab3d6");
        printAAB3(aab3d7, "aab3d7");
        printAAB3(aab3d8, "aab3d8");
        printAAB3(aab3d9, "aab3d9");

        AxisAlignedBox3f aab3f(-1.0f, -2.0f, -1.0f, 2.0f, 1.0f, 2.0f);
        aab3d9 = aab3f;
        printAAB3(aab3d9, "aab3d9 = aab3f");
        aab3f = aab3d2;
        printAAB3(aab3f, "aab3f = aab3d2");
    }

    void testAAB3_constFunctions()
    {
        AxisAlignedBox3d aab3d(-0.5, -1.0, -0.5, 1.0, 0.5, 1.0);

        Vector3d v3d1(1.0, 1.0, 1.0), v3d2(0.25, 0.25, 0.25);

        std::cout << " -> contains(v3d1) : " << aab3d.contains(v3d1) << std::endl;
        std::cout << " -> contains(v3d2) : " << aab3d.contains(v3d2) << std::endl;

        std::cout << " -> distanceSquared(v3d1) : " << aab3d.distanceSquared(v3d1) << std::endl;
        std::cout << " -> distanceSquared(v3d2) : " << aab3d.distanceSquared(v3d2) << std::endl;

        std::cout << " -> distance(v3d1) : " << aab3d.distance(v3d1) << std::endl;
        std::cout << " -> distance(v3d2) : " << aab3d.distance(v3d2) << std::endl;

        std::cout << " -> signedDistance(v3d1) : " << aab3d.signedDistance(v3d1) << std::endl;
        std::cout << " -> signedDistance(v3d2) : " << aab3d.signedDistance(v3d2) << std::endl;

        AxisAlignedBox3d aab3d1(2.0, 2.0, 2.0, 4.0, 4.0, 4.0);
        std::cout << " -> intersects(aab3d1) : " << aab3d.intersects(aab3d1) << std::endl;

        std::cout << " -> distanceSquared(aab3d1) : " << aab3d.distanceSquared(aab3d1) << std::endl;

        aab3d1.contain(v3d2);
        std::cout << " -> intersects(aab3d1) : " << aab3d.intersects(aab3d1) << std::endl;

        AxisAlignedBox3d intersection = aab3d.intersect(aab3d1);
        printAAB3Simple(intersection, "intersection");
    }

    void testAAB3_nonConstFunctions()
    {
        AxisAlignedBox3d aab3d(-0.5, -1.0, -0.5, 1.0, 0.5, 1.0);

        printAAB3Simple(aab3d, "aabd3");
        aab3d.expand(2.0);
        printAAB3Simple(aab3d, "expand(2.0)");
        aab3d.contract(0.5);
        printAAB3Simple(aab3d, "contract(0.5)");
        aab3d.scale(2.0, 4.0, 6.0);
        printAAB3Simple(aab3d, "scale(2.0, 4.0, 6.0)");
        aab3d.contain(Vector3d(10.0, 15.0, 8.0));
        printAAB3Simple(aab3d, "contain(Vector3d(10.0, 15.0, 8.0))");
        aab3d.contain(AxisAlignedBox3d(Vector3d(25.0, -10.0, -5.0), Vector3d(28.0, 6.0, 30.0)));
        printAAB3Simple(aab3d, "contain(AxisAlignedBox3d(Vector3d(25.0, -10.0, -5.0), Vector3d(28.0, 6.0, 30.0)))");
        aab3d.translate(Vector3d(1.0, 2.0, 3.0));
        printAAB3Simple(aab3d, "translate(Vector3d(1.0, 2.0, 3.0))");
    }
}

#endif
