#include "testAxisAlignedBox2.h"

using namespace g3test;

int main()
{
    // test axis aligned box 2
    // testAAB2_constructor();
    testAAB2_nonConstFunctions();
    std::cout << std::endl;
    testAAB2_nonConstFunctions2();
    std::cout << std::endl;
    testAAB2_constFunctions();

    system("pause");
    return 0;
}