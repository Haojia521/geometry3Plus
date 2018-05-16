#ifndef G3_TEST_MATH_MATRIX_3
#define G3_TEST_MATH_MATRIX_3

#include <math/matrix3.h>

#include "util.h"

using namespace g3;

namespace g3test
{
    double func1(int i)
    {
        return i * 4;
    }

    double func2(int i, int j)
    {
        return i + j * 2;
    }

    void testMatrix3_constructors()
    {
        Vector3d vd1(1, 2, 3), vd2(4, 5, 6), vd3(7, 8, 9);

        Matrix3d m3d1;
        Matrix3d m3d2(true);

        double dv1[] = {3, 2, 1, 5, 4, 6, 9, 7, 8};
        Matrix3d m3d3(dv1);
        double dv2[][3] = { { 1, 4, 7 }, { 8, 2, 5 }, {6, 9, 3} };
        Matrix3d m3d4(dv2);
        Matrix3d m3d5(std::function<double(int)>([](int i) -> double { return i * 3; }));
        std::function<double(int)> f1(func1);
        Matrix3d m3d6(f1);
        Matrix3d m3d7(std::function<double(int,int)>([](int i, int j) -> double { return i + j; }));
        std::function<double(int,int)> f2(func2);
        Matrix3d m3d8(f2);
        Matrix3d m3d9(4, 2, 9);
        Matrix3d m3d10(vd1, vd2, vd3, false);
        Matrix3d m3d11(vd1, vd2, vd3, true);
        Matrix3d m3d12(9, 5, 1, 7, 3, 8, 4, 2, 6);
        printMatrix3(m3d1, "m3d1");
        printMatrix3(m3d2, "m3d2");
        printMatrix3(m3d3, "m3d3");
        printMatrix3(m3d4, "m3d4");
        printMatrix3(m3d5, "m3d5");
        printMatrix3(m3d6, "m3d6");
        printMatrix3(m3d7, "m3d7");
        printMatrix3(m3d8, "m3d8");
        printMatrix3(m3d9, "m3d9");
        printMatrix3(m3d10, "m3d10");
        printMatrix3(m3d11, "m3d11");
        printMatrix3(m3d12, "m3d12");

        Matrix3f m3f1;
        m3f1 = m3d3;
        printMatrix3(m3f1, "m3f1 = m3d3");
    }

    void testMatrix3_constFunctions()
    {
        Vector3d vd1(1, 6, 4), vd2(7, 2, 3), vd3(9, 4, 1);

        Matrix3d m3d1(vd1, vd2, vd3, false);

        printVector3(m3d1.column(0), "m3d1.column(0)");
        printVector3(m3d1.column(1), "m3d1.column(1)");
        printVector3(m3d1.column(2), "m3d1.column(2)");

        auto r1 = m3d1.determinant();
        std::cout << "m3d1.determinant(): " << r1 << std::endl;

        printMatrix3(m3d1.transpose(), "m3d1.transpose()");
        printMatrix3(m3d1.inverse(), "m3d1.inverse()");

        Matrix3d m3d2(vd1 + mathUtil::epsilon, 
                      vd2 + mathUtil::epsilon,
                      vd3 + mathUtil::epsilon, false);
        auto r2 = m3d1.epsilonEqual(m3d2, 0.01);
        std::cout << "m3d1.epsilonEqual(m3d2, 0.01): " << r2 << std::endl;

        double r3[9];
        m3d2.toBuffer(r3);
        std::cout << "m3d2.toBuffer(r3): ";
        for (int i = 0; i < 9; ++i)
        {
            if (i % 3 == 0) std::cout << std::endl;
            std::cout << r3[i] << "  ";
        }
        std::cout << std::endl;
    }

    void testMatrix3_nonConstFunctions()
    {

    }

    void testMatrix3_operatorFunctions()
    {
        Vector3d vd1(1, 6, 4), vd2(7, 2, 3), vd3(9, 4, 1);

        Matrix3d m3d1(vd1, vd2, vd3, false);

        std::cout << "Matrix3[0][0]: " << m3d1[0][0] << std::endl;
        std::cout << "Matrix3[0][1]: " << m3d1[0][1] << std::endl;
        std::cout << "Matrix3[0][2]: " << m3d1[0][2] << std::endl;
        std::cout << "Matrix3[1][0]: " << m3d1[1][0] << std::endl;
        std::cout << "Matrix3[1][1]: " << m3d1[1][1] << std::endl;
        std::cout << "Matrix3[1][2]: " << m3d1[1][2] << std::endl;
        std::cout << "Matrix3[2][0]: " << m3d1[2][0] << std::endl;
        std::cout << "Matrix3[2][1]: " << m3d1[2][1] << std::endl;
        std::cout << "Matrix3[2][2]: " << m3d1[2][2] << std::endl;

        auto r1 = -m3d1;
        printMatrix3(r1, "-m3d1");

        Matrix3d m3d2(1, 2, 3, 4, 5, 6, 7, 8, 9);
        printMatrix3(m3d1 - m3d2, "m3d1 - m3d2");
        printMatrix3(m3d1 - 3, "m3d1 - 3");

        printMatrix3(m3d1 + m3d2, "m3d1 + m3d2");
        printMatrix3(m3d1 + 5, "m3d1 + 5");

        printMatrix3(m3d1 * m3d2, "m3d1 * m3d2");
        printMatrix3(m3d1 * 2, "m3d1 * 2");
        printMatrix3(3 * m3d1, "3 * m3d1");

        printMatrix3(m3d2 / 2, "m3d2 / 2");

        printVector3(m3d2 * vd1, "m3d2 * vd1");
        printVector3(vd1 * m3d2, "vd1 * m3d2");
    }
}

#endif
