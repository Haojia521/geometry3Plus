#define TEST_TRIANGLE_X 1

#ifdef TEST_VECTOR_X_D
#include "testVectorXd.h"
#endif

#ifdef TEST_TRIANGLE_X
#include "testTriangleX.h"
#endif

using namespace g3test;

int main()
{
#ifdef TEST_VECTOR_X_D
    // check vector operator functions
    testVector2d_operators();
    std::cout << std::endl;
    testVector3d_operators();
#endif

#ifdef TEST_TRIANGLE_X
    testTriangleX_constructor_typeConv();
    testTriangleX_functions();
#endif

    system("pause");
    return 0;
}
