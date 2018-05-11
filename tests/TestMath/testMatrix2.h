#ifndef G3_TEST_MATH_MATRIX_2
#define G3_TEST_MATH_MATRIX_2

#include <math/matrix2.h>

#include "util.h"

using namespace g3;

namespace g3test
{
    void testMatrix2_constructor()
    {
        Vector2d vd1(1, 2), vd2(3, 4);

        Matrix2d m2d1;
        Matrix2d m2d2(true);
        Matrix2d m2d3(1, 2, 2, 1);
        Matrix2d m2d4(4, double(5));
        Matrix2d m2d5(1.5, false);
        Matrix2d m2d6(vd1, vd2, false);
        Matrix2d m2d7(vd1, vd2, true);
        Matrix2d m2d8(vd1, vd2);
        Matrix2d m2d9(m2d3);
        printMatrix2(m2d1, "m2d1");
        printMatrix2(m2d2, "m2d2");
        printMatrix2(m2d3, "m2d3");
        printMatrix2(m2d4, "m2d4");
        printMatrix2(m2d5, "m2d5");
        printMatrix2(m2d6, "m2d6");
        printMatrix2(m2d7, "m2d7");
        printMatrix2(m2d8, "m2d8");
        printMatrix2(m2d9, "m2d9");

        Matrix2f m2f0(m2d5);
        Matrix2f m2f1 = m2d4;
        printMatrix2(m2f0, "m2f0");
        printMatrix2(m2f1, "m2f1");
    }

    void testMatrix2_constFunctions()
    {
        Vector2d vd1(1, 2), vd2(3, 4);

        Matrix2d m2d1(1, 3, 1, 4);
        auto r = m2d1.qForm(vd1, vd2);
        std::cout << "m2d1.qForm(vd1, vd2): " << r << std::endl;

        printMatrix2(m2d1.transpose(), "m2d1.transpose()");
        printMatrix2(m2d1.inverse(), "m2d1.inverse()");
        printMatrix2(m2d1.adjoint(), "m2d1.adjoint()");

        auto r2 = m2d1.determinant();
        std::cout << "m2d1.determinant(): " << r2 << std::endl;

        printVector2(m2d1.column(0), "m2d1.column(0)");
        printVector2(m2d1.column(1), "m2d1.column(1)");

        Matrix2d m2d2(1.5, false);
        auto r3 = m2d2.extractAngle();
        std::cout << "m2d2.extractAngle(): " << r3 << std::endl;

        Matrix2d m2d3(vd1, vd2);
        Matrix2d m2d4, m2d5;
        m2d3.eigenDecomposition(m2d4, m2d5);
        printMatrix2(m2d4, "m2d3.eigenDecomposition(m2d4, m2d5) rot");
        printMatrix2(m2d5, "m2d3.eigenDecomposition(m2d4, m2d5) diag");
    }

    void testMatrix2_nonConstFunctions()
    {
        Vector2d vd1(1, 2), vd2(3, 4);

        Matrix2d m2d1;
        m2d1.setToRow(vd1, vd2);
        printMatrix2(m2d1, "setToRow(vd1, vd2)");
        m2d1.setToRow(5, 6, 7, 8);
        printMatrix2(m2d1, "setToRow(5, 6, 7, 8)");
        m2d1.setToColumn(vd1, vd2);
        printMatrix2(m2d1, "setToColumn(vd1, vd2)");
        m2d1.setToColumn(5, 6, 7, 8);
        printMatrix2(m2d1, "setToColumn(5, 6, 7, 8)");
        m2d1.setToDiagonal(4, 6);
        printMatrix2(m2d1, "setToDiagonal(4, 6)");

        m2d1.setToRow(vd1, vd2);
        m2d1.orthonormalize();
        printMatrix2(m2d1, "orthonormalize()");
    }

    void testMatrix2_operatorFunctions()
    {
        Vector2d vd1(1, 2), vd2(3, 4);
        Matrix2d m2d1;
        m2d1.setToRow(vd1, vd2);

        std::cout << "Matrix2[0][0]: " << m2d1[0][0] << std::endl;
        std::cout << "Matrix2[0][1]: " << m2d1[0][1] << std::endl;
        std::cout << "Matrix2[1][0]: " << m2d1[1][0] << std::endl;
        std::cout << "Matrix2[1][1]: " << m2d1[1][1] << std::endl;

        auto r1 = -m2d1;
        printMatrix2(r1, "-m2d1");
        Matrix2d m2d2(6, 7, 8, 9);
        printMatrix2(m2d2 - m2d1, "m2d2 - m2d1");
        printMatrix2(m2d2 - 3, "m2d2 - 3");

        printMatrix2(m2d2 + m2d1, "m2d2 + m2d1");
        printMatrix2(m2d2 + 5, "m2d2 + 5");

        printMatrix2(m2d2 * 3, "m2d2 * 3");
        printMatrix2(4 * m2d2, "3 * m2d2");

        printMatrix2(m2d2 / 4, "m2d2 / 4");

        printVector2(m2d2 * vd1, "m2d2 * vd1");
        printVector2(vd2 * m2d2, "vd2 * m2d2");
    }
}

#endif
