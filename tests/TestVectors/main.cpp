#include "testVectorXd.h"

using namespace g3test;

int main()
{
    // check vector operator functions
    testVector2d_operators();
    std::cout << std::endl;
    testVector3d_operators();

    system("pause");
    return 0;
}
